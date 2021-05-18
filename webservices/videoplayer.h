#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QAbstractVideoSurface>
#include <QMediaPlayer>
#include <QWidget>
#include <QVideoSurfaceFormat>
#include <QPainter>

#include "ext/libda-release/abstractelement.h"

QT_BEGIN_NAMESPACE
class QAbstractButton;
class QSlider;
class QLabel;
class QUrl;
QT_END_NAMESPACE

class VideoSurface : public QAbstractVideoSurface
{
public:
    explicit VideoSurface(QWidget *target, QWidget *p = nullptr);

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType ht = QAbstractVideoBuffer::NoHandle) const;
    bool isFormatSupported(const QVideoSurfaceFormat &format) const;
    bool start(const QVideoSurfaceFormat &format);
    void updateVideoRect();
    void stop();
    bool present(const QVideoFrame &frame);
    QRect videoRect();
    void paint(QPainter &p);

private:
    QImage::Format currFormat;
    QSize currSize;
    QRect src;
    QWidget *tar;
    QRect tarRect;
    QVideoFrame currFrame;
    QTransform oldTr;
};

class VideoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VideoWidget(QWidget *p = nullptr);

    QAbstractVideoSurface *videoSurface();
    QSize sizeHint() const;
    void closeEvent(QCloseEvent *e);
    void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent *e);
    VideoSurface *surFace();

private:
    VideoSurface *surface;
};

class VideoPlayer : public QWidget, public Dtk::Addons::AbstractElement
{
    Q_OBJECT
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
public:
    VideoPlayer(QWidget *parent = nullptr);
    ~VideoPlayer() override;

    void setUrl(const QUrl &url);

    inline QObject *self() override {return this;}
    inline void addElement(AbstractElement *) override {}

    QString source();

Q_SIGNALS:
    void sourceChanged(QString updated);

public Q_SLOTS:
    void openFile();
    void play();
    void setSource(QString src);

private Q_SLOTS:
    void mediaStateChanged(QMediaPlayer::State state);
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);
    void setPosition(int position);
    void handleError();

private:
    QMediaPlayer* m_mediaPlayer;
    QAbstractButton *m_playButton;
    QSlider *m_positionSlider;
    QLabel *m_errorLabel;
};

#endif // VIDEOPLAYER_H
