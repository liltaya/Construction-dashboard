#include "construction/utils/Logger.h"

#include <QDateTime>
#include <QDir>
#include <QMutexLocker>
#include <QStandardPaths>
#include <QTextStream>
#include <QDebug>

namespace construction {

Logger& Logger::instance()
{
    static Logger logger;
    return logger;
}

Logger::Logger()
{
    QString directory =
        QStandardPaths::writableLocation(
            QStandardPaths::AppLocalDataLocation
        );

    if (directory.isEmpty())
    {
        directory = QDir::tempPath()
                    + "/ConstructionDashboard";
    }

    QDir().mkpath(directory);

    logFile_.setFileName(
        directory + "/application.log"
    );

    if (!logFile_.open(
            QIODevice::WriteOnly |
            QIODevice::Append |
            QIODevice::Text))
    {
        qWarning() << "Cannot open log file:"
                   << logFile_.errorString();
    }
}

void Logger::write(
    const QString& level,
    const QString& message)
{
    QMutexLocker lock(&mutex_);

    const QString timestamp =
        QDateTime::currentDateTimeUtc()
            .toString(Qt::ISODate);

    const QString entry =
        QString("[%1] [%2] %3\n")
            .arg(timestamp, level, message);

    if (logFile_.isOpen())
    {
        QTextStream stream(&logFile_);
        stream << entry;
        stream.flush();
    }

    qInfo().noquote() << entry.trimmed();
}

void Logger::info(const QString& message)
{
    write("INFO", message);
}

void Logger::warning(const QString& message)
{
    write("WARNING", message);
}

void Logger::error(const QString& message)
{
    write("ERROR", message);
}

}
