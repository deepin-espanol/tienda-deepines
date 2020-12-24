#include "abstracthistoryhandler.h"

AbstractHistoryHandler::AbstractHistoryHandler() {}
AbstractHistoryHandler::~AbstractHistoryHandler() {}
void AbstractHistoryHandler::load(QString) {}
QWidget *AbstractHistoryHandler::widget() const {return new QWidget;}
