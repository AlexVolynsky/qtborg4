#include "generaltab.h"

#include <QtWidgets>

GeneralTab::GeneralTab(const QFileInfo &fileInfo, QWidget *parent)
    : QWidget(parent)
{
    BackupNameLabel = new QLabel(tr("Backup Name:"));

    BackupNameEdit = new QLineEdit ("Backup1");//(fileInfo.fileName());

    patSrcLabel = new QLabel(tr("Source directory:"));
    directorySrcComboBox = createComboBox(QDir::currentPath());
    browseSrcButton = createButton(tr("&Browse..."), SLOT(browseSrc()));

    patDstLabel = new QLabel(tr("Repository location:"));
    directoryDstComboBox = createComboBox();
    browseDstButton = createButton(tr("&Browse..."), SLOT(browseDst()));

    toDoBackupButton = createButton(tr("&Start Backup"), SLOT(backup()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(BackupNameLabel);
    mainLayout->addWidget(BackupNameEdit);

    mainLayout->addWidget(patSrcLabel);
    mainLayout->addWidget(directorySrcComboBox);
    mainLayout->addWidget(browseSrcButton);

    mainLayout->addWidget(patDstLabel);
    mainLayout->addWidget(directoryDstComboBox);
    mainLayout->addWidget(browseDstButton);


    mainLayout->addWidget(toDoBackupButton);

    mainLayout->addStretch(1);
    setLayout(mainLayout);
}


void GeneralTab::browseSrc()
{
    QString directory = QFileDialog::getExistingDirectory(this,
                               tr("Find Files"), QDir::currentPath());

        if (!directory.isEmpty()) {
            if (directorySrcComboBox->findText(directory) == -1)
                directorySrcComboBox->addItem(directory);
            directorySrcComboBox->setCurrentIndex(directorySrcComboBox->findText(directory));
        }
}

void GeneralTab::browseDst()
{
    QString directory = QFileDialog::getExistingDirectory(this,
                               tr("Find Files"), QDir::currentPath());

        if (!directory.isEmpty()) {
            if (directoryDstComboBox->findText(directory) == -1)
                directoryDstComboBox->addItem(directory);
            directoryDstComboBox->setCurrentIndex(directoryDstComboBox->findText(directory));
        }
}

void GeneralTab::backup()
{
    QProcess proc;

    //Let's create a repo on an external drive
    proc.start ("/bin/bash", QStringList() << "brog init --encryption=repokey " << directoryDstComboBox->currentText());
    proc.waitForStarted();
    proc.waitForBytesWritten();
    proc.waitForFinished();
    //qDebug() << proc.readAll();

    //So now, let's create our first (compressed) backup
    proc.start ("/bin/bash", QStringList() << "brog create --stats --progress --compression lz4 "
                                  << directoryDstComboBox->currentText()<<"::"
                                  << BackupNameEdit->text() << " "
                                  << directorySrcComboBox->currentText());
    proc.waitForBytesWritten();
    proc.waitForFinished();
    //qDebug() << proc.readAll();
    proc.close();

}

QPushButton *GeneralTab::createButton(const QString &text, const char *member)
{
    QPushButton *button = new QPushButton(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}

QComboBox *GeneralTab::createComboBox(const QString &text)
{
    QComboBox *comboBox = new QComboBox;
    comboBox->setEditable(true);
    comboBox->addItem(text);
    comboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    return comboBox;
}
