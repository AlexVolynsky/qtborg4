#include "generaltab.h"
#include "loggingcategories.h"
#include <QtWidgets>

GeneralTab::GeneralTab(const QFileInfo &fileInfo, QWidget *parent)
    : QWidget(parent)
{
    backupNameLabel = new QLabel(tr("Backup Name:"));

    backupNameEdit = new QLineEdit (fileInfo.fileName());
    backupNameEdit->setEnabled(false);

    patSrcLabel = new QLabel(tr("Source directory:"));
    directorySrcComboBox = createComboBox(QDir::currentPath());
    browseSrcButton = createButton(tr("&Browse source directory..."), SLOT(browseSrc()));

    patDstLabel = new QLabel(tr("Repository location:"));
    directoryDstComboBox = createComboBox();
    browseDstButton = createButton(tr("&Browse repository location..."), SLOT(browseDst()));

    optionalArgumentsTab = new OptionalArgumentsTab();
    commonOptionsTab = new CommonOptionsTab();
    exclusionOptionsTab = new ExclusionOptionsTab();
    filesystemOptionsTab = new FilesystemOptionsTab();
    archiveOptionsTab = new ArchiveOptionsTab();

    optionsTabWidget = new QTabWidget(this);
    optionsTabWidget->addTab(optionalArgumentsTab, tr("Optional Arguments"));
    optionsTabWidget->addTab(commonOptionsTab,     tr("Common Options"));
    optionsTabWidget->addTab(exclusionOptionsTab,  tr("Exclusion Options"));
    optionsTabWidget->addTab(filesystemOptionsTab, tr("Filesystem Options"));
    optionsTabWidget->addTab(archiveOptionsTab,    tr("Archive Options"));

    toDoBackupButton = createButton(tr("&START BACKUP"), SLOT(backup()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(backupNameLabel);
    mainLayout->addWidget(backupNameEdit);

    mainLayout->addWidget(patSrcLabel);
    mainLayout->addWidget(directorySrcComboBox);
    mainLayout->addWidget(browseSrcButton);

    mainLayout->addWidget(patDstLabel);
    mainLayout->addWidget(directoryDstComboBox);
    mainLayout->addWidget(browseDstButton);


    mainLayout->addWidget(optionsTabWidget);
    optionsTabWidget->setCornerWidget(0);

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
    qInfo(logInfo()) << "GeneralTab::backup()";

    QStringList  arguments;

    createArgumentsStringOfBorgBackup (arguments);



    /*  Now we have something like that:
     *
        borg create --one-file-system --compression zstd,15 \
        $server:borg::$(date +%Y-%m-%dT%H-%M-%S)-home $HOME \
        --exclude-caches --exclude-if-present CMakeCache.txt \
        --verbose --progress
    */

    qDebug() <<"The command" << arguments;
    qInfo(logInfo()) <<"The command" << arguments;;

    #ifndef W_OS_LINUX

//        QProcess process;
//        process.setProgram("/bin/bash");
//        process.setArguments(arguments);
//        //process.setWorkingDirectory(DirPath);
//        process.setStandardOutputFile(QProcess::nullDevice());
//        process.setStandardErrorFile(QProcess::nullDevice());
//        qint64 pid;
//        bool result_of_Buckup = process.startDetached(&pid);
//        qDebug() <<"Result of the buckup :" << result_of_Buckup;

    #else
        QMessageBox msgBox;
        msgBox.setText("The OS is not supported");
        msgBox.setInformativeText("This OS is not supported in this version. At the moment, we only support the Ubuntu(linux) OS for backup.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    #endif

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

void GeneralTab::createArgumentsStringOfBorgBackup(QStringList& arguments)
{
    qInfo(logInfo()) << "GeneralTab::createArgumentsStringOfBorgBackup";

    QDateTime now = QDateTime::currentDateTime();
    int offset = now.offsetFromUtc();
    now.setOffsetFromUtc(offset);

    //Let's prepare string repository like this: $server:borg::$(date +%Y-%m-%dT%H-%M-%S)-home $HOME
    QString strRepository = directoryDstComboBox->currentText() + now.toString(Qt::ISODate);

    QString strSourceDirs = directorySrcComboBox->currentText();

    arguments << "borg create";
    arguments << strRepository;
    arguments << strSourceDirs;


    //Try to check the 'Optional arguments' tab
    if(optionalArgumentsTab->doNotCreateBackupArchiveCheckBox->isChecked())
    {
        arguments << "-n";
    }

    if(optionalArgumentsTab->printStatisticsForTheCreatedArchiveCheckBox->isChecked())
    {
        arguments << "-s";
    }

    if(optionalArgumentsTab->outputVerboseListOfItemsCheckBox->isChecked())
    {
        arguments << "--list";
    }

    if(optionalArgumentsTab->outputStatsAsJSONCheckBox->isChecked())
    {
        arguments << "--json";
    }

    if(optionalArgumentsTab->doNotSynchronizeTheCacheUsedToDetectCheckBox->isChecked())
    {
        arguments << "--no-cache-sync";
    }

    if(optionalArgumentsTab->doNotLoadUpdateTheFilesMetadataCacheUsedToDetectUnchangedFilesCheckBox->isChecked())
    {
        arguments << "--no-files-cache";
    }

    //Try to check the 'Exclusion options' tab
    if(!exclusionOptionsTab->excludePathsMatchingPATTERNEdit->text().trimmed().isEmpty())
    {
        QString dataFromLineEdit1 = exclusionOptionsTab->excludePathsMatchingPATTERNEdit->text().trimmed();
        QStringList subListArguments1 = dataFromLineEdit1.split(",",QString::SkipEmptyParts);

        for(int i=0; i < subListArguments1.size(); ++i)
        {
            arguments << "--exclude" << subListArguments1.at(i);
        }
    }

    if(!exclusionOptionsTab->readExcludePatternsFromEXCLUDEFILEEdit->text().trimmed().isEmpty())
    {
        QString dataFromLineEdit2 = exclusionOptionsTab->excludePathsMatchingPATTERNEdit->text().trimmed();
        QStringList subListArguments2 = dataFromLineEdit2.split(",",QString::SkipEmptyParts);

        for(int i=0; i < subListArguments2.size(); ++i)
        {
            arguments << "--exclude-from" << subListArguments2.at(i);
        }
    }

    if(!exclusionOptionsTab->include_excludePathsMatchingPATTERNEdit->text().trimmed().isEmpty())
    {
        QString dataFromLineEdit3 = exclusionOptionsTab->include_excludePathsMatchingPATTERNEdit->text().trimmed();
        QStringList subListArguments3 = dataFromLineEdit3.split(",",QString::SkipEmptyParts);

        for(int i=0; i < subListArguments3.size(); ++i)
        {
            arguments << "--pattern" << subListArguments3.at(i);
        }
    }

    if(!exclusionOptionsTab->readIncludeEexcludePatternsFromPATTERNFILEEdit->text().trimmed().isEmpty())
    {
        QString dataFromLineEdit4 = exclusionOptionsTab->readIncludeEexcludePatternsFromPATTERNFILEEdit->text().trimmed();
        QStringList subListArguments4 = dataFromLineEdit4.split(",",QString::SkipEmptyParts);

        for(int i=0; i < subListArguments4.size(); ++i)
        {
            arguments << "--patterns-from" << subListArguments4.at(i);
        }
    }

    if(exclusionOptionsTab->excludeDirectoriesThatContainCACHEDIRfileCheckBox->isChecked())
    {
        arguments << "--exclude-caches";
    }

    if(!exclusionOptionsTab->excludeDirsThatAreTaggedByContainingFilesystemObjectWithTheGivenNAMEEdit->text().trimmed().isEmpty())
    {
        QString dataFromLineEdit5 = exclusionOptionsTab->excludeDirsThatAreTaggedByContainingFilesystemObjectWithTheGivenNAMEEdit->text().trimmed();
        QStringList subListArguments5 = dataFromLineEdit5.split(",",QString::SkipEmptyParts);

        for(int i=0; i < subListArguments5.size(); ++i)
        {
            arguments << "--exclude-if-present" << subListArguments5.at(i);
        }
    }

    if(exclusionOptionsTab->ifTagObjectsSpecifiedWithExcludeifpresentCheckBox->isChecked())
    {
        arguments << "--keep-exclude-tags";
    }

    if(exclusionOptionsTab->excludeFilesFlaggedNODUMPCheckBox->isChecked())
    {
        arguments << "--exclude-nodump";
    }


    //Try to check the 'Filesystem options' tab
    if(filesystemOptionsTab->stayInSameFileSystemAndDoNotStoreMountPointsOfOtherFileSystemsCheckBox->isChecked())
    {
        arguments << "--one-file-system";
    }

    if(filesystemOptionsTab->onlyStoreNumericUserAndGroupIdentifiersCheckBox->isChecked())
    {
        arguments << "--numeric-owner";
    }

    if(filesystemOptionsTab->doNotStoreAtimeIntoArchiveCheckBox->isChecked())
    {
        arguments << "--noatime";
    }

    if(filesystemOptionsTab->doNotStoreCtimeIntoArchiveCheckBox->isChecked())
    {
        arguments << "--noctime";
    }

    if(filesystemOptionsTab->doNotStoreBirthtimeIntoArchiveCheckBox->isChecked())
    {
        arguments << "--nobirthtime";
    }

    if(filesystemOptionsTab->doNotReadAndStoreBsdflagsIntoArchiveCheckBox->isChecked())
    {
        arguments << "--nobsdflags";
    }

    if(filesystemOptionsTab->ignoreInodeDataInTheFileMetadataCacheUsedToDetectUnchangedFilesCheckBox->isChecked())
    {
        arguments << "--ignore-inode";
    }

    if(filesystemOptionsTab->openAndReadBlockAndCharDeviceFilesAsWellAsFIFOsCheckBox->isChecked())
    {
        arguments << "--read-special";
    }

    //Try to check the 'Archive options' tab
    if(!archiveOptionsTab->addCommentTextToTheArchiveEdit->text().trimmed().isEmpty())
    {
        arguments << "--comment" << archiveOptionsTab->addCommentTextToTheArchiveEdit->text().trimmed();
    }

    if(archiveOptionsTab->writeCheckpointEverySecondsSpinBox->value()!= archiveOptionsTab->defaultSecondsForCheckpoint)
    {
        arguments << "-c" << QString::number(archiveOptionsTab->writeCheckpointEverySecondsSpinBox->value());
    }

    if(!archiveOptionsTab->specifyTheChunkerParametersEdit->text().trimmed().isEmpty())
    {
        arguments << "--chunker-params" << archiveOptionsTab->specifyTheChunkerParametersEdit->text().trimmed();
    }

    if(!archiveOptionsTab->selectCompressionAlgorithmEdit->text().trimmed().isEmpty())
    {
        arguments << "-C" << archiveOptionsTab->selectCompressionAlgorithmEdit->text().trimmed();
    }

}

//////////////////////////// Optional arguments of "borg create" /////////////////////////////////////

OptionalArgumentsTab::OptionalArgumentsTab(QWidget *parent)
    : QWidget(parent)
{
    doNotCreateBackupArchiveCheckBox = new QCheckBox(tr("do not create backup archive"));
    printStatisticsForTheCreatedArchiveCheckBox = new QCheckBox(tr("print statistics for the created archive"));
    outputVerboseListOfItemsCheckBox = new QCheckBox(tr("output verbose list of items (files,dirs,...)"));
    onlyDisplayItemsWithTheGivenStatusCharactersCheckBox = new QCheckBox(tr("only display items with the given status characters"));
    outputStatsAsJSONCheckBox = new QCheckBox(tr("output stats as JSON"));
    doNotSynchronizeTheCacheUsedToDetectCheckBox = new QCheckBox(tr("do not synchronize the cache used to detect"));
    doNotLoadUpdateTheFilesMetadataCacheUsedToDetectUnchangedFilesCheckBox = new QCheckBox(tr("do not load update the files metadata cache used to detect unchanged files"));
    useNameInArchiveForSTDINDataCheckBox = new QCheckBox(tr("use NAME in archive for stdin data (default: “stdin”)"));

    QVBoxLayout *checkboxLayout = new QVBoxLayout;
    checkboxLayout->addWidget(doNotCreateBackupArchiveCheckBox);
    checkboxLayout->addWidget(printStatisticsForTheCreatedArchiveCheckBox);
    checkboxLayout->addWidget(outputVerboseListOfItemsCheckBox);
    checkboxLayout->addWidget(onlyDisplayItemsWithTheGivenStatusCharactersCheckBox);
    checkboxLayout->addWidget(outputStatsAsJSONCheckBox);
    checkboxLayout->addWidget(doNotSynchronizeTheCacheUsedToDetectCheckBox);
    checkboxLayout->addWidget(doNotLoadUpdateTheFilesMetadataCacheUsedToDetectUnchangedFilesCheckBox);
    checkboxLayout->addWidget(useNameInArchiveForSTDINDataCheckBox);
    checkboxLayout->addStretch(1);

    setLayout(checkboxLayout);
}


CommonOptionsTab::CommonOptionsTab(QWidget *parent)
    : QWidget(parent)
{

}

ExclusionOptionsTab::ExclusionOptionsTab(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QHBoxLayout* horizonLayout1 = new QHBoxLayout;
    QHBoxLayout* horizonLayout2 = new QHBoxLayout;
    QHBoxLayout* horizonLayout3 = new QHBoxLayout;
    QHBoxLayout* horizonLayout4 = new QHBoxLayout;
    QHBoxLayout* horizonLayout5 = new QHBoxLayout;

    excludePathsMatchingPATTERNLabel = new QLabel(tr("exclude paths matching PATTERN"));
    excludePathsMatchingPATTERNEdit  = new QLineEdit ();
    horizonLayout1->addWidget(excludePathsMatchingPATTERNLabel);
    horizonLayout1->addWidget(excludePathsMatchingPATTERNEdit);

    readExcludePatternsFromEXCLUDEFILELabel = new QLabel(tr("read exclude patterns from EXCLUDEFILE, one per line"));
    readExcludePatternsFromEXCLUDEFILEEdit  = new QLineEdit ();
    horizonLayout2->addWidget(readExcludePatternsFromEXCLUDEFILELabel);
    horizonLayout2->addWidget(readExcludePatternsFromEXCLUDEFILEEdit);

    include_excludePathsMatchingPATTERNLabel = new QLabel(tr("experimental: include/exclude paths matching PATTERN"));
    include_excludePathsMatchingPATTERNEdit  = new QLineEdit ();
    horizonLayout3->addWidget(include_excludePathsMatchingPATTERNLabel);
    horizonLayout3->addWidget(include_excludePathsMatchingPATTERNEdit);

    readIncludeEexcludePatternsFromPATTERNFILELabel = new QLabel(tr("experimental: read include/exclude patterns from PATTERNFILE, one per line"));
    readIncludeEexcludePatternsFromPATTERNFILEEdit  = new QLineEdit ();
    horizonLayout4->addWidget(readIncludeEexcludePatternsFromPATTERNFILELabel);
    horizonLayout4->addWidget(readIncludeEexcludePatternsFromPATTERNFILEEdit);

    excludeDirectoriesThatContainCACHEDIRfileCheckBox = new QCheckBox(tr("exclude directories that contain a CACHEDIR.TAG file"));

    excludeDirsThatAreTaggedByContainingFilesystemObjectWithTheGivenNAMELabel = new QLabel(tr("exclude directories that are tagged by containing a filesystem object with the given NAME"));
    excludeDirsThatAreTaggedByContainingFilesystemObjectWithTheGivenNAMEEdit  = new QLineEdit ();
    horizonLayout5->addWidget(excludeDirsThatAreTaggedByContainingFilesystemObjectWithTheGivenNAMELabel);
    horizonLayout5->addWidget(excludeDirsThatAreTaggedByContainingFilesystemObjectWithTheGivenNAMEEdit);

    ifTagObjectsSpecifiedWithExcludeifpresentCheckBox = new QCheckBox(tr("if tag objects are specified with the previous item, don’t omit the tag objects themselves from the backup archive"));

    excludeFilesFlaggedNODUMPCheckBox = new QCheckBox(tr("exclude files flagged NODUMP"));

    mainLayout->addLayout(horizonLayout1);
    mainLayout->addLayout(horizonLayout2);
    mainLayout->addLayout(horizonLayout3);
    mainLayout->addLayout(horizonLayout4);
    mainLayout->addWidget(excludeDirectoriesThatContainCACHEDIRfileCheckBox);
    mainLayout->addLayout(horizonLayout5);
    mainLayout->addWidget(ifTagObjectsSpecifiedWithExcludeifpresentCheckBox);
    mainLayout->addWidget(excludeFilesFlaggedNODUMPCheckBox);

    mainLayout->addStretch(1);

    setLayout(mainLayout);
}

FilesystemOptionsTab::FilesystemOptionsTab(QWidget *parent)
    : QWidget(parent)
{
    stayInSameFileSystemAndDoNotStoreMountPointsOfOtherFileSystemsCheckBox = new QCheckBox(tr("stay in the same file system and do not store mount points of other file systems"));
    onlyStoreNumericUserAndGroupIdentifiersCheckBox = new QCheckBox(tr("only store numeric user and group identifiers"));
    doNotStoreAtimeIntoArchiveCheckBox = new QCheckBox(tr("do not store atime into archive"));
    doNotStoreCtimeIntoArchiveCheckBox = new QCheckBox(tr("do not store ctime into archive"));
    doNotStoreBirthtimeIntoArchiveCheckBox = new QCheckBox(tr("do not store birthtime (creation date) into archive"));
    doNotReadAndStoreBsdflagsIntoArchiveCheckBox = new QCheckBox(tr("do not read and store bsdflags (e.g. NODUMP, IMMUTABLE) into archive"));
    ignoreInodeDataInTheFileMetadataCacheUsedToDetectUnchangedFilesCheckBox = new QCheckBox(tr("ignore inode data in the file metadata cache used to detect unchanged files"));;
    operateFilesCacheInMODECheckBox = new QCheckBox(tr("operate files cache in MODE. default: ctime,size,inode"));
    openAndReadBlockAndCharDeviceFilesAsWellAsFIFOsCheckBox = new QCheckBox(tr("open and read block and char device files as well as FIFOs as if they were regular files. Also follows symlinks pointing to these kinds of files"));

    QVBoxLayout *checkboxLayout = new QVBoxLayout;
    checkboxLayout->addWidget(stayInSameFileSystemAndDoNotStoreMountPointsOfOtherFileSystemsCheckBox);
    checkboxLayout->addWidget(onlyStoreNumericUserAndGroupIdentifiersCheckBox);
    checkboxLayout->addWidget(doNotStoreAtimeIntoArchiveCheckBox);
    checkboxLayout->addWidget(doNotStoreCtimeIntoArchiveCheckBox);
    checkboxLayout->addWidget(doNotStoreBirthtimeIntoArchiveCheckBox);
    checkboxLayout->addWidget(doNotReadAndStoreBsdflagsIntoArchiveCheckBox);
    checkboxLayout->addWidget(ignoreInodeDataInTheFileMetadataCacheUsedToDetectUnchangedFilesCheckBox);
    checkboxLayout->addWidget(operateFilesCacheInMODECheckBox);
    checkboxLayout->addWidget(openAndReadBlockAndCharDeviceFilesAsWellAsFIFOsCheckBox);
    checkboxLayout->addStretch(1);

    setLayout(checkboxLayout);
}

ArchiveOptionsTab::ArchiveOptionsTab(QWidget *parent)
    : QWidget(parent),defaultSecondsForCheckpoint(1800)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QHBoxLayout* horizonLayout1 = new QHBoxLayout;
    QHBoxLayout* horizonLayout2 = new QHBoxLayout;
    QHBoxLayout* horizonLayout3 = new QHBoxLayout;
    QHBoxLayout* horizonLayout4 = new QHBoxLayout;
    QHBoxLayout* horizonLayout5 = new QHBoxLayout;

    addCommentTextToTheArchiveLabel = new QLabel(tr("add a comment text to the archive"));
    addCommentTextToTheArchiveEdit  = new QLineEdit ();
    horizonLayout1->addWidget(addCommentTextToTheArchiveLabel);
    horizonLayout1->addWidget(addCommentTextToTheArchiveEdit);

    manuallySpecifyTheArchiveCreationDateTimeLabel = new QLabel(tr("manually specify the archive creation date/time (UTC, yyyy-mm-ddThh:mm:ss format). Alternatively, give a reference file/directory"));
    dateEdit = new QDateTimeEdit(QDate::currentDate());
    dateEdit->setMinimumDate(QDate::currentDate().addDays(-365));
    dateEdit->setMaximumDate(QDate::currentDate().addDays(365));
    dateEdit->setDisplayFormat("yyyy-mm-ddThh:mm:ss");
    dateEdit->setDate(QDate::currentDate().addDays(-365));
    horizonLayout2->addWidget(manuallySpecifyTheArchiveCreationDateTimeLabel);
    horizonLayout2->addWidget(dateEdit);

    writeCheckpointEverySecondsLabel = new QLabel(tr("write checkpoint every SECONDS seconds (Default: 1800)"));
    writeCheckpointEverySecondsSpinBox  = new QSpinBox ();
    writeCheckpointEverySecondsSpinBox->setMinimum(0);
    writeCheckpointEverySecondsSpinBox->setMaximum(10000000);
    writeCheckpointEverySecondsSpinBox->setSingleStep(1);
    writeCheckpointEverySecondsSpinBox->setValue(defaultSecondsForCheckpoint);
    horizonLayout3->addWidget(writeCheckpointEverySecondsLabel);
    horizonLayout3->addWidget(writeCheckpointEverySecondsSpinBox);

    specifyTheChunkerParametersLabel = new QLabel(tr("specify the chunker parameters (CHUNK_MIN_EXP, CHUNK_MAX_EXP, HASH_MASK_BITS, HASH_WINDOW_SIZE). default: 19,23,21,4095"));
    specifyTheChunkerParametersEdit  = new QLineEdit ();
    horizonLayout4->addWidget(specifyTheChunkerParametersLabel);
    horizonLayout4->addWidget(specifyTheChunkerParametersEdit);

    selectCompressionAlgorithmLabel = new QLabel(tr("select compression algorithm, see the output of the “borg help compression” command for details"));
    selectCompressionAlgorithmEdit  = new QLineEdit ();
    horizonLayout5->addWidget(selectCompressionAlgorithmLabel);
    horizonLayout5->addWidget(selectCompressionAlgorithmEdit);

    mainLayout->addLayout(horizonLayout1);
    mainLayout->addLayout(horizonLayout2);
    mainLayout->addLayout(horizonLayout3);
    mainLayout->addLayout(horizonLayout4);
    mainLayout->addLayout(horizonLayout5);

    mainLayout->addStretch(1);

    setLayout(mainLayout);
}
