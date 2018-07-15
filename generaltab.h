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
    QPushButton *toDoBackupButton;
};



/////////////////////////Optional Tabs///////////////

class OptionalArgumentsTab : public QWidget
{
    Q_OBJECT

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

public:
    explicit CommonOptionsTab(QWidget *parent = 0);


};

/*! The ExclusionOptionsTab class that contains all the fields for working with exclusion options.
*/
class ExclusionOptionsTab : public QWidget
{
    Q_OBJECT

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
    QLabel    *excludeDirectoriesThatContainCACHEDIRfileLabel;
    QLineEdit *excludeDirectoriesThatContainCACHEDIRfileEdit;
    QLabel    *excludeDirsThatAreTaggedByContainingFilesystemObjectWithTheGivenNAMELabel;
    QLineEdit *excludeDirsThatAreTaggedByContainingFilesystemObjectWithTheGivenNAMEEdit;
    QLabel    *ifTagObjectsSpecifiedWithExcludeifpresentLabel;
    QLineEdit *ifTagObjectsSpecifiedWithExcludeifpresentEdit;
    QLabel    *excludeFilesFlaggedNODUMPLabel;
    QLineEdit *excludeFilesFlaggedNODUMPEdit;

};


/*! The FilesystemOptionsTab class that contains all the fields for working with filesystem options.
*/
class FilesystemOptionsTab : public QWidget
{
    Q_OBJECT

public:
    explicit FilesystemOptionsTab(QWidget *parent = 0);

private:
    QLabel    *stayInSameFileSystemAndDoNotStoreMountPointsOfOtherFileSystemsLabel;
    QLineEdit *stayInSameFileSystemAndDoNotStoreMountPointsOfOtherFileSystemsEdit;
    QLabel    *onlyStoreNumericUserAndGroupIdentifiersLabel;
    QLineEdit *onlyStoreNumericUserAndGroupIdentifiersEdit;
    QLabel    *doNotStoreAtimeIntoArchiveLabel;
    QLineEdit *doNotStoreAtimeIntoArchiveEdit;
    QLabel    *doNotStoreCtimeIntoArchiveLabel;
    QLineEdit *doNotStoreCtimeIntoArchiveEdit;
    QLabel    *doNotStoreBirthtimeIntoArchiveLabel;
    QLineEdit *doNotStoreBirthtimeIntoArchiveEdit;
    QLabel    *doNotReadAndStoreBsdflagsIntoArchiveLabel;
    QLineEdit *doNotReadAndStoreBsdflagsIntoArchiveEdit;
    QLabel    *ignoreInodeDataInTheFileMetadataCacheUsedToDetectUnchangedFilesLabel;
    QLineEdit *ignoreInodeDataInTheFileMetadataCacheUsedToDetectUnchangedFilesEdit;
    QLabel    *operateFilesCacheInMODELabel;
    QLineEdit *operateFilesCacheInMODEEdit;
    QLabel    *openAndReadBlockAndCharDeviceFilesAsWellAsFIFOsLabel;
    QLineEdit *openAndReadBlockAndCharDeviceFilesAsWellAsFIFOsEdit;
};

/*! The ArchiveOptionsTab class that contains all the fields for working with archive options.
*/
class ArchiveOptionsTab : public QWidget
{
    Q_OBJECT

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
};


#endif // GENERALTAB_H
