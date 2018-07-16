#include "mainwindow.h"
#include <QApplication>
#include <QLoggingCategory>
#include <QDateTime>


// Smart pointer to the log file
QScopedPointer<QFile>   m_logFile;

// Declaring a handler
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QString fileName;

    //Create absolut path to the logfile
    QDateTime now = QDateTime::currentDateTime();
    int offset = now.offsetFromUtc();
    now.setOffsetFromUtc(offset);

    QString  strPathToLogFile = QDir::homePath()+
             QString("/logFile") +
             now.toString(Qt::ISODate) +
             QString(".txt");
    qDebug() << "The logfile : " << strPathToLogFile;

    // Set the log file, and check carefully what path is used for the file
    m_logFile.reset(new QFile(strPathToLogFile));

    // Open the log file
    m_logFile.data()->open(QFile::Append | QFile::Text);

    // Let's set the handler
    qInstallMessageHandler(messageHandler);

    if (argc >= 2)
        fileName = argv[1];
    else
        fileName = ".";

    TabDialog tabdialog(fileName);
    tabdialog.show();

    return app.exec();
}

// Implementing the handler
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
     // Open the write stream to the file
    QTextStream out(m_logFile.data());

    // Write the recording date
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");

    // By type, we determine to what level the message belongs
    switch (type)
    {
        case QtInfoMsg:     out << "INF "; break;
        case QtDebugMsg:    out << "DBG "; break;
        case QtWarningMsg:  out << "WRN "; break;
        case QtCriticalMsg: out << "CRT "; break;
        case QtFatalMsg:    out << "FTL "; break;
    }

    // Write to the output the category of the message and the message itself
    out << context.category << ": "
        << msg << endl;

    // Clear the buffered data
    out.flush();
}
