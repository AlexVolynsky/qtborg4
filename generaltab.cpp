#include "generaltab.h"

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


    optionsTabWidget = new QTabWidget(this);
    optionsTabWidget->addTab(new OptionalArgumentsTab(optionsTabWidget), tr("Optional Arguments"));
    optionsTabWidget->addTab(new CommonOptionsTab(optionsTabWidget), tr("Common Options"));
    optionsTabWidget->addTab(new ExclusionOptionsTab(optionsTabWidget), tr("Exclusion Options"));
    optionsTabWidget->addTab(new FilesystemOptionsTab(optionsTabWidget), tr("Filesystem Options"));
    optionsTabWidget->addTab(new ArchiveOptionsTab(optionsTabWidget), tr("Filesystem Options"));

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
    #ifndef __linux__

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

/////////////////////////////////////////////////////////////////
OptionalArgumentsTab::OptionalArgumentsTab(QWidget *parent)
    : QWidget(parent)
{
    doNotCreateBackupArchiveCheckBox = new QCheckBox(tr("Do not create backup archive"));
    printStatisticsForTheCreatedArchiveCheckBox = new QCheckBox(tr("Print statistics for the created archive"));
    outputVerboseListOfItemsCheckBox = new QCheckBox(tr("Output verbose list of items (files,dirs,...)"));
    onlyDisplayItemsWithTheGivenStatusCharactersCheckBox = new QCheckBox(tr("Only display items with the given status characters"));
    outputStatsAsJSONCheckBox = new QCheckBox(tr("Output stats as JSON"));
    doNotSynchronizeTheCacheUsedToDetectCheckBox = new QCheckBox(tr("Do not synchronize the cache used to detect"));
    doNotLoadUpdateTheFilesMetadataCacheUsedToDetectUnchangedFilesCheckBox = new QCheckBox(tr("Do not load update the files metadata cache used to detect unchanged files"));
    useNameInArchiveForSTDINDataCheckBox = new QCheckBox(tr("use NAME in archive for stdin data"));

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
    QHBoxLayout* horizonLayout6 = new QHBoxLayout;
    QHBoxLayout* horizonLayout7 = new QHBoxLayout;
    QHBoxLayout* horizonLayout8 = new QHBoxLayout;

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

    excludeDirectoriesThatContainCACHEDIRfileLabel = new QLabel(tr("exclude directories that contain a CACHEDIR.TAG file"));
    excludeDirectoriesThatContainCACHEDIRfileEdit  = new QLineEdit ();
    horizonLayout5->addWidget(excludeDirectoriesThatContainCACHEDIRfileLabel);
    horizonLayout5->addWidget(excludeDirectoriesThatContainCACHEDIRfileEdit);

    excludeDirsThatAreTaggedByContainingFilesystemObjectWithTheGivenNAMELabel = new QLabel(tr("exclude directories that are tagged by containing a filesystem object with the given NAME"));
    excludeDirsThatAreTaggedByContainingFilesystemObjectWithTheGivenNAMEEdit  = new QLineEdit ();
    horizonLayout6->addWidget(excludeDirsThatAreTaggedByContainingFilesystemObjectWithTheGivenNAMELabel);
    horizonLayout6->addWidget(excludeDirsThatAreTaggedByContainingFilesystemObjectWithTheGivenNAMEEdit);

    ifTagObjectsSpecifiedWithExcludeifpresentLabel = new QLabel(tr("if tag objects are specified with --exclude-if-present, don’t omit the tag objects themselves from the backup archive"));
    ifTagObjectsSpecifiedWithExcludeifpresentEdit  = new QLineEdit ();
    horizonLayout7->addWidget(ifTagObjectsSpecifiedWithExcludeifpresentLabel);
    horizonLayout7->addWidget(ifTagObjectsSpecifiedWithExcludeifpresentEdit);

    excludeFilesFlaggedNODUMPLabel = new QLabel(tr("exclude files flagged NODUMP"));
    excludeFilesFlaggedNODUMPEdit  = new QLineEdit ();
    horizonLayout8->addWidget(excludeFilesFlaggedNODUMPLabel);
    horizonLayout8->addWidget(excludeFilesFlaggedNODUMPEdit);

    mainLayout->addLayout(horizonLayout1);
    mainLayout->addLayout(horizonLayout2);
    mainLayout->addLayout(horizonLayout3);
    mainLayout->addLayout(horizonLayout4);
    mainLayout->addLayout(horizonLayout5);
    mainLayout->addLayout(horizonLayout6);
    mainLayout->addLayout(horizonLayout7);
    mainLayout->addLayout(horizonLayout8);

    mainLayout->addStretch(1);

    setLayout(mainLayout);
}

FilesystemOptionsTab::FilesystemOptionsTab(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QHBoxLayout* horizonLayout1 = new QHBoxLayout;
    QHBoxLayout* horizonLayout2 = new QHBoxLayout;
    QHBoxLayout* horizonLayout3 = new QHBoxLayout;
    QHBoxLayout* horizonLayout4 = new QHBoxLayout;
    QHBoxLayout* horizonLayout5 = new QHBoxLayout;
    QHBoxLayout* horizonLayout6 = new QHBoxLayout;
    QHBoxLayout* horizonLayout7 = new QHBoxLayout;
    QHBoxLayout* horizonLayout8 = new QHBoxLayout;
    QHBoxLayout* horizonLayout9 = new QHBoxLayout;

    stayInSameFileSystemAndDoNotStoreMountPointsOfOtherFileSystemsLabel = new QLabel(tr("stay in the same file system and do not store mount points of other file systems"));
    stayInSameFileSystemAndDoNotStoreMountPointsOfOtherFileSystemsEdit  = new QLineEdit ();
    horizonLayout1->addWidget(stayInSameFileSystemAndDoNotStoreMountPointsOfOtherFileSystemsLabel);
    horizonLayout1->addWidget(stayInSameFileSystemAndDoNotStoreMountPointsOfOtherFileSystemsEdit);

    onlyStoreNumericUserAndGroupIdentifiersLabel = new QLabel(tr("only store numeric user and group identifiers"));
    onlyStoreNumericUserAndGroupIdentifiersEdit  = new QLineEdit ();
    horizonLayout2->addWidget(onlyStoreNumericUserAndGroupIdentifiersLabel);
    horizonLayout2->addWidget(onlyStoreNumericUserAndGroupIdentifiersEdit);

    doNotStoreAtimeIntoArchiveLabel = new QLabel(tr("do not store atime into archive"));
    doNotStoreAtimeIntoArchiveEdit  = new QLineEdit ();
    horizonLayout3->addWidget(doNotStoreAtimeIntoArchiveLabel);
    horizonLayout3->addWidget(doNotStoreAtimeIntoArchiveEdit);

    doNotStoreCtimeIntoArchiveLabel = new QLabel(tr("do not store ctime into archive"));
    doNotStoreCtimeIntoArchiveEdit  = new QLineEdit ();
    horizonLayout4->addWidget(doNotStoreCtimeIntoArchiveLabel);
    horizonLayout4->addWidget(doNotStoreCtimeIntoArchiveEdit);

    doNotStoreBirthtimeIntoArchiveLabel = new QLabel(tr("do not store birthtime (creation date) into archive"));
    doNotStoreBirthtimeIntoArchiveEdit  = new QLineEdit ();
    horizonLayout5->addWidget(doNotStoreBirthtimeIntoArchiveLabel);
    horizonLayout5->addWidget(doNotStoreBirthtimeIntoArchiveEdit);

    doNotReadAndStoreBsdflagsIntoArchiveLabel = new QLabel(tr("do not read and store bsdflags (e.g. NODUMP, IMMUTABLE) into archive"));
    doNotReadAndStoreBsdflagsIntoArchiveEdit  = new QLineEdit ();
    horizonLayout6->addWidget(doNotReadAndStoreBsdflagsIntoArchiveLabel);
    horizonLayout6->addWidget(doNotReadAndStoreBsdflagsIntoArchiveEdit);

    ignoreInodeDataInTheFileMetadataCacheUsedToDetectUnchangedFilesLabel = new QLabel(tr("ignore inode data in the file metadata cache used to detect unchanged files"));
    ignoreInodeDataInTheFileMetadataCacheUsedToDetectUnchangedFilesEdit  = new QLineEdit ();
    horizonLayout7->addWidget(ignoreInodeDataInTheFileMetadataCacheUsedToDetectUnchangedFilesLabel);
    horizonLayout7->addWidget(ignoreInodeDataInTheFileMetadataCacheUsedToDetectUnchangedFilesEdit);

    operateFilesCacheInMODELabel = new QLabel(tr("operate files cache in MODE. default: ctime,size,inode"));
    operateFilesCacheInMODEEdit  = new QLineEdit ();
    horizonLayout8->addWidget(operateFilesCacheInMODELabel);
    horizonLayout8->addWidget(operateFilesCacheInMODEEdit);

    openAndReadBlockAndCharDeviceFilesAsWellAsFIFOsLabel = new QLabel(tr("open and read block and char device files as well as FIFOs as if they were regular files. Also follows symlinks pointing to these kinds of files"));
    openAndReadBlockAndCharDeviceFilesAsWellAsFIFOsEdit  = new QLineEdit ();
    horizonLayout9->addWidget(openAndReadBlockAndCharDeviceFilesAsWellAsFIFOsLabel);
    horizonLayout9->addWidget(openAndReadBlockAndCharDeviceFilesAsWellAsFIFOsEdit);

    mainLayout->addLayout(horizonLayout1);
    mainLayout->addLayout(horizonLayout2);
    mainLayout->addLayout(horizonLayout3);
    mainLayout->addLayout(horizonLayout4);
    mainLayout->addLayout(horizonLayout5);
    mainLayout->addLayout(horizonLayout6);
    mainLayout->addLayout(horizonLayout7);
    mainLayout->addLayout(horizonLayout8);
    mainLayout->addLayout(horizonLayout9);

    mainLayout->addStretch(1);

    setLayout(mainLayout);

}

ArchiveOptionsTab::ArchiveOptionsTab(QWidget *parent)
    : QWidget(parent)
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
    writeCheckpointEverySecondsSpinBox->setValue(1800);
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
