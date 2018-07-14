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
    QLabel *BackupNameLabel;
    QLineEdit *BackupNameEdit;
    QLabel *patSrcLabel;
    QPushButton *browseSrcButton;
    QLabel *patDstLabel;
    QPushButton *browseDstButton;
    QLabel *filesFoundLabel;
    QComboBox *directorySrcComboBox;
    QComboBox *directoryDstComboBox;
    QPushButton *toDoBackupButton;
};

#endif // GENERALTAB_H
