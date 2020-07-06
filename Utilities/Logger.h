#ifndef LOGGER_H
#define LOGGER_H

#include "QListWidget"
#include "QDebug"

class Logger
{

public:
    Logger(QListWidget* logWidget = 0);
    ~Logger();

    void Log(QString logText);

    QListWidget *logPanel;
};

#endif // LOGGER_H
