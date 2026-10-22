#pragma once

#include <QFile>
#include <QMutex>
#include <QString>

namespace construction {

class Logger
{
public:
    static Logger& instance();

    void info(const QString& message);
    void warning(const QString& message);
    void error(const QString& message);

private:
    Logger();

    void write(
        const QString& level,
        const QString& message
    );

    QFile logFile_;
    QMutex mutex_;
};

}
