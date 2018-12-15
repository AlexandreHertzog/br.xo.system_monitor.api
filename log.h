#ifndef CLOG_H
#define CLOG_H

#include <QCoreApplication>
#include <QDateTime>
#include <QFileInfo>
#include <QString>
#include <QTextStream>
#include <iostream>

namespace API
{
inline void customLog(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    const QString appFileName = QFileInfo(QCoreApplication::applicationFilePath()).fileName();
    QString logFileName;
    if (appFileName.isEmpty())
    {
        logFileName += "sysinfo.log";
    }
    else
    {
        logFileName += appFileName + ".log";
    }

    QFile logFile(logFileName);
    if (logFile.exists())
    {
        logFile.open(QIODevice::Append | QIODevice::Text);
    }
    else
    {
        logFile.open(QIODevice::WriteOnly | QIODevice::Text);
    }

    const QString now = QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss:zzz");
    const QByteArray localMsg = msg.toLocal8Bit();

    QString message;
    const QString format = "%1 [%2 : %3] %4";
    switch (type)
    {
    case QtDebugMsg:
        message = format.arg(now, QString::fromStdString("DEBUG"), context.function, localMsg.constData());
        break;
    case QtInfoMsg:
        message = format.arg(now, QString::fromStdString("INFO"), context.function, localMsg.constData());
        break;
    case QtWarningMsg:
        message = format.arg(now, QString::fromStdString("WARN"), context.function, localMsg.constData());
        break;
    case QtCriticalMsg:
        message = format.arg(now, QString::fromStdString("ERROR"), context.function, localMsg.constData());
        break;
    case QtFatalMsg:
        message = format.arg(now, QString::fromStdString("FATAL"), context.function, localMsg.constData());
        break;
    }
    fprintf(stderr, "%s\n", message.toLocal8Bit().constData());
    if (logFile.isOpen())
    {
        QTextStream(&logFile) << message << "\n";
    }
}
} // namespace API

#endif // CLOG_H
