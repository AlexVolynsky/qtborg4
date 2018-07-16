#ifndef GENERALTAB_H
#define GENERALTAB_H

#include <QWidget>
#include <QDir>

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QFileInfo;
class QComboBox;
class QPushButton;
class QStackedWidget;
class QCheckBox;
class QTabWidget;
class QDateTimeEdit;
class QSpinBox;
class OptionalArgumentsTab;
class CommonOptionsTab;
class ExclusionOptionsTab;
class FilesystemOptionsTab;
class ArchiveOptionsTab;
QT_END_NAMESPACE


/*! The GeneralTab class that contains all the fields for working with the BorgBackup for a specific backup.
A object of this type should be dynamically created.
*/
class GeneralTab : public QWidget
{
    Q_OBJECT

public:
    explicit GeneralTab(const QFileInfo &fileInfo, QWidget *parent = 0);

private:
    QPushButton *createButton(const QString &text, const char *member);
    QComboBox *createComboBox(const QString &text = QString());
    void createArgumentsStringOfBorgBackup (QStringList& arguments);

private slots:
    void browseSrc();
    void browseDst();
    void backup();

private:
    QDir currentDir;
    QLabel *backupNameLabel;
    QLineEdit *backupNameEdit;
    QLabel *patSrcLabel;
    QPushButton *browseSrcButton;
    QLabel *patDstLabel;
    QPushButton *browseDstButton;
    QComboBox *directorySrcComboBox;
    QComboBox *directoryDstComboBox;
    QTabWidget *optionsTabWidget;

    OptionalArgumentsTab* optionalArgumentsTab;
    CommonOptionsTab*     commonOptionsTab;
    ExclusionOptionsTab*  exclusionOptionsTab;
    FilesystemOptionsTab* filesystemOptionsTab;
    ArchiveOptionsTab*    archiveOptionsTab;

    QPushButton *toDoBackupButton;
};



/////////////////////////Optional Tabs///////////////

class OptionalArgumentsTab : public QWidget
{
    Q_OBJECT

    friend class GeneralTab;

public:
    explicit OptionalArgumentsTab(QWidget *parent = 0);

private:
    QCheckBox *doNotCreateBackupArchiveCheckBox;
    QCheckBox *printStatisticsForTheCreatedArchiveCheckBox;
    QCheckBox *outputVerboseListOfItemsCheckBox;
    QCheckBox *onlyDisplayItemsWithTheGivenStatusCharactersCheckBox;
    QCheckBox *outputStatsAsJSONCheckBox;
    QCheckBox *doNotSynchronizeTheCacheUsedToDetectCheckBox;
    QCheckBox *doNotLoadUpdateTheFilesMetadataCacheUsedToDetectUnchangedFilesCheckBox;
    QCheckBox *useNameInArchiveForSTDINDataCheckBox;
};

/*! The CommonOptionsTab class that contains all the fields for working with common options.
*/
class CommonOptionsTab : public QWidget
{
    Q_OBJECT

    friend class GeneralTab;

public:
    explicit CommonOptionsTab(QWidget *parent = 0);


};

/*! The ExclusionOptionsTab class that contains all the fields for working with exclusion options.
*/
class ExclusionOptionsTab : public QWidget
{
    Q_OBJECT

    friend class GeneralTab;

public:
    explicit ExclusionOptionsTab(QWidget *parent = 0);

private:
    QLabel    *excludePathsMatchingPATTERNLabel;
    QLineEdit *excludePathsMatchingPATTERNEdit;
    QLabel    *readExcludePatternsFromEXCLUDEFILELabel;
    QLineEdit *readExcludePatternsFromEXCLUDEFILEEdit;
    QLabel    *include_excludePathsMatchingPATTERNLabel;
    QLineEdit *include_excludePathsMatchingPATTERNEdit;
    QLabel    *readIncludeEexcludePatternsFromPATTERNFILELabel;
    QLineEdit *readIncludeEexcludePatternsFromPATTERNFILEEdit;
    QCheckBox *excludeDirectoriesThatContainCACHEDIRfileCheckBox ;
    QLabel    *excludeDirsThatAreTaggedByContainingFilesystemObjectWithTheGivenNAMELabel;
    QLineEdit *excludeDirsThatAreTaggedByContainingFilesystemObjectWithTheGivenNAMEEdit;
    QCheckBox *ifTagObjectsSpecifiedWithExcludeifpresentCheckBox;
    QCheckBox *excludeFilesFlaggedNODUMPCheckBox;
};


/*! The FilesystemOptionsTab class that contains all the fields for working with filesystem options.
*/
class FilesystemOptionsTab : public QWidget
{
    Q_OBJECT

    friend class GeneralTab;

public:
    explicit FilesystemOptionsTab(QWidget *parent = 0);

private:
    QCheckBox *stayInSameFileSystemAndDoNotStoreMountPointsOfOtherFileSystemsCheckBox;
    QCheckBox *onlyStoreNumericUserAndGroupIdentifiersCheckBox;
    QCheckBox *doNotStoreAtimeIntoArchiveCheckBox;
    QCheckBox *doNotStoreCtimeIntoArchiveCheckBox;
    QCheckBox *doNotStoreBirthtimeIntoArchiveCheckBox;
    QCheckBox *doNotReadAndStoreBsdflagsIntoArchiveCheckBox;
    QCheckBox *ignoreInodeDataInTheFileMetadataCacheUsedToDetectUnchangedFilesCheckBox;
    QCheckBox *operateFilesCacheInMODECheckBox;
    QCheckBox *openAndReadBlockAndCharDeviceFilesAsWellAsFIFOsCheckBox;
};

/*! The ArchiveOptionsTab class that contains all the fields for working with archive options.
*/
class ArchiveOptionsTab : public QWidget
{
    Q_OBJECT

    friend class GeneralTab;

public:
    explicit ArchiveOptionsTab(QWidget *parent = 0);

private:
    QLabel    *addCommentTextToTheArchiveLabel;
    QLineEdit *addCommentTextToTheArchiveEdit;
    QLabel    *manuallySpecifyTheArchiveCreationDateTimeLabel;
    QDateTimeEdit *dateEdit;
    QLabel    *writeCheckpointEverySecondsLabel;
    QSpinBox  *writeCheckpointEverySecondsSpinBox;
    QLabel    *specifyTheChunkerParametersLabel;
    QLineEdit *specifyTheChunkerParametersEdit;
    QLabel    *selectCompressionAlgorithmLabel;
    QLineEdit *selectCompressionAlgorithmEdit;
    int       defaultSecondsForCheckpoint;
};


#endif // GENERALTAB_H
