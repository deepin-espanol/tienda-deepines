#include "videoplayer.h"

#include <QtWidgets>
#include <QVideoWidget>

LDA_USE_NAMESPACE

VideoPlayer::VideoPlayer(QWidget *parent)
    : QWidget(parent),
      AbstractElement()
{
    m_mediaPlayer = new QMediaPlayer(this, QMediaPlayer::VideoSurface);
    QVideoWidget *videoWidget = new QVideoWidget;

    QAbstractButton *openButton = new QPushButton(tr("Open..."));
    connect(openButton, &QAbstractButton::clicked, this, &VideoPlayer::openFile);

    m_playButton = new QPushButton;
    m_playButton->setEnabled(false);
    m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

    connect(m_playButton, &QAbstractButton::clicked,
            this, &VideoPlayer::play);

    m_positionSlider = new QSlider(Qt::Horizontal);
    m_positionSlider->setRange(0, 0);

    connect(m_positionSlider, &QAbstractSlider::sliderMoved,
            this, &VideoPlayer::setPosition);

    m_errorLabel = new QLabel;
    m_errorLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

    QBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->setContentsMargins(0, 0, 0, 0);
    controlLayout->addWidget(openButton);
    controlLayout->addWidget(m_playButton);
    controlLayout->addWidget(m_positionSlider);

    QBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(videoWidget);
    layout->addLayout(controlLayout);
    layout->addWidget(m_errorLabel);

    setLayout(layout);

    m_mediaPlayer->setVideoOutput(videoWidget);
    connect(m_mediaPlayer, &QMediaPlayer::stateChanged,
            this, &VideoPlayer::mediaStateChanged);
    connect(m_mediaPlayer, &QMediaPlayer::positionChanged, this, &VideoPlayer::positionChanged);
    connect(m_mediaPlayer, &QMediaPlayer::durationChanged, this, &VideoPlayer::durationChanged);
    connect(m_mediaPlayer, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error),
            this, &VideoPlayer::handleError);

    QAction *act = new QAction;
    act->setShortcut(QKeySequence(QKeySequence::StandardKey::Open));
    addAction(act);
    connect(act, &QAction::triggered, this, &VideoPlayer::openFile);
    //setMinimumHeight(200);
}


VideoPlayer::~VideoPlayer()
{
}

void VideoPlayer::setSource(QString s)
{
    setUrl(QUrl(s));
    std::cout << "Source changed!" << std::endl;
    Q_EMIT sourceChanged(s);
}

QString VideoPlayer::source()
{
    return m_mediaPlayer->media().request().url().toString();
}

void VideoPlayer::openFile()
{
    QFileDialog fileDialog(this);
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setWindowTitle(tr("Open Movie"));
    QStringList supportedMimeTypes = m_mediaPlayer->supportedMimeTypes();
    if (!supportedMimeTypes.isEmpty())
        fileDialog.setMimeTypeFilters(supportedMimeTypes);
    fileDialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::MoviesLocation).value(0, QDir::homePath()));
    if (fileDialog.exec() == QDialog::Accepted)
        setUrl(fileDialog.selectedUrls().constFirst());
}

void VideoPlayer::setUrl(const QUrl &url)
{
    m_errorLabel->setText(QString());
    setWindowFilePath(url.isLocalFile() ? url.toLocalFile() : QString());
    m_mediaPlayer->setMedia(url);
    m_playButton->setEnabled(true);
}

void VideoPlayer::play()
{
    switch (m_mediaPlayer->state()) {
    case QMediaPlayer::PlayingState:
        m_mediaPlayer->pause();
        break;
    default:
        m_mediaPlayer->play();
        break;
    }
}

void VideoPlayer::mediaStateChanged(QMediaPlayer::State state)
{
    switch(state) {
    case QMediaPlayer::PlayingState:
        m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        break;
    default:
        m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        break;
    }
}

void VideoPlayer::positionChanged(qint64 position)
{
    m_positionSlider->setValue((int)position);
}

void VideoPlayer::durationChanged(qint64 duration)
{
    m_positionSlider->setRange(0, (int)duration);
}

void VideoPlayer::setPosition(int position)
{
    m_mediaPlayer->setPosition(position);
}

void VideoPlayer::handleError()
{
    m_playButton->setEnabled(false);
    const QString errorString = m_mediaPlayer->errorString();
    QString message = "Error: ";
    if (errorString.isEmpty())
        message += " #" + QString::number(int(m_mediaPlayer->error()));
    else
        message += errorString;
    m_errorLabel->setText(message);
}

VideoSurface::VideoSurface(QWidget *target, QWidget *p) : QAbstractVideoSurface(p)
{
    tar = target;
    currFormat = QImage::Format_Invalid;
}

QList<QVideoFrame::PixelFormat> VideoSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType ht) const
{
    Q_UNUSED(ht);
    return QList<QVideoFrame::PixelFormat>() << QVideoFrame::PixelFormat::Format_RGB32
                                             << QVideoFrame::PixelFormat::Format_ARGB32
                                             << QVideoFrame::PixelFormat::Format_ARGB32_Premultiplied
                                             << QVideoFrame::PixelFormat::Format_RGB555
                                             << QVideoFrame::PixelFormat::Format_RGB565;
}

bool VideoSurface::isFormatSupported(const QVideoSurfaceFormat &format) const {
    QImage::Format frmt = QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());
    return ((frmt != QImage::Format::Format_Invalid) && (format.frameSize().isEmpty() == false) && (format.handleType() == QAbstractVideoBuffer::NoHandle));
}

bool VideoSurface::start(const QVideoSurfaceFormat &format) {
    QImage::Format frmt = QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());
    if ((frmt != QImage::Format::Format_Invalid) && (format.frameSize().isEmpty() == false)) {
        currSize = format.frameSize();
        currFormat = frmt;
        src = format.viewport();
        QAbstractVideoSurface::start(format);
        tar->updateGeometry();
        updateVideoRect();
    }
}

void VideoSurface::updateVideoRect() {
    QSize s = surfaceFormat().sizeHint();
    s.scale(tar->size().boundedTo(s), Qt::KeepAspectRatio);
    tarRect = QRect(QPoint(0, 0), s);
    tarRect.moveCenter(tar->rect().center());
}

void VideoSurface::stop() {
    currFrame = QVideoFrame();
    tarRect = QRect();
    QAbstractVideoSurface::stop();
    tar->update();
}

bool VideoSurface::present(const QVideoFrame &frame) {
    if ((surfaceFormat().pixelFormat() != frame.pixelFormat()) || (surfaceFormat().frameSize() != frame.size())) {
        setError(QAbstractVideoSurface::IncorrectFormatError);
        stop();
        return false;
    } else {
        currFrame = frame;
        tar->repaint(tarRect);
    }
}

QRect VideoSurface::videoRect() {return tarRect;}

void VideoSurface::paint(QPainter &p) {
    if (currFrame.map(QAbstractVideoBuffer::ReadOnly)) {
        oldTr = p.transform();
        if (surfaceFormat().scanLineDirection() == QVideoSurfaceFormat::BottomToTop) {
            p.scale(1, -1);
            p.translate(0, -tar->height());
        }

        p.drawImage(tarRect, QImage(currFrame.bits(), currFrame.width(), currFrame.height(), currFrame.bytesPerLine(), currFormat));
        p.setTransform(oldTr);
        currFrame.unmap();
    }
}


VideoWidget::VideoWidget(QWidget *p) : QWidget(p) {
    setAutoFillBackground(false);
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_PaintOnScreen);
    QPalette pal = palette();
    pal.setColor(QPalette::ColorRole::Background, Qt::black);
    setPalette(pal);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    surface = new VideoSurface(this);
}


QAbstractVideoSurface *VideoWidget::videoSurface()
{
    return surface;
}

QSize VideoWidget::sizeHint() const
{
    return surface->surfaceFormat().sizeHint();
}

void VideoWidget::closeEvent(QCloseEvent *e)
{
    delete surface;
}

void VideoWidget::paintEvent(QPaintEvent *e)
{
    QPainter p;
    if (surface->isActive()) {
        QRect vr = surface->videoRect();
        if (vr.contains(e->rect()) == false) {
            QRegion r = e->region();
            r.subtracted(vr);
            QBrush b = palette().background();
            Q_FOREACH(QRect rectangle, r.rects()) {
                p.fillRect(rectangle, b);
            }
        }
        surface->paint(p);
    } else {
        p.fillRect(e->rect(), palette().window());
    }
}

void VideoWidget::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
    surface->updateVideoRect();
}

VideoSurface *VideoWidget::surFace()
{
    return surface;
}
