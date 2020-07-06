#include "Logger.h"
#include "QDateTime"


Logger::Logger(QListWidget* logWidget)
{
    logPanel = logWidget;
    qDebug() << "Spawned Logger";

}
Logger::~Logger()
{

}


void Logger::Log(QString logText)
{
    qDebug() << logText;
    QString finalLogString = QDateTime::currentDateTime().time().toString() + ": " + logText;
    logPanel->addItem(finalLogString);

}
