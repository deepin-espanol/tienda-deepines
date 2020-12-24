#include "abstracthistoryhandler.h"

AbstractHistoryHandler::AbstractHistoryHandler() {}
AbstractHistoryHandler::~AbstractHistoryHandler() {}
void AbstractHistoryHandler::load(QString) {}
QWidget *AbstractHistoryHandler::self() const {return new QWidget;}
