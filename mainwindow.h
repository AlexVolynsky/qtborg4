#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QDir>

QT_BEGIN_NAMESPACE
class QPushButton;
class QComboBox;
class QStackedWidget;
class QTabBar;
class GeneralTab;
class QDialogButtonBox;
class QLabel;
class QLineEdit;
QT_END_NAMESPACE


class TabDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TabDialog(const QString &fileName, QWidget *parent = 0);

private:
    QPushButton *createButton(const QString &text, const char *member);
    QComboBox   *createComboBox(const QString &text = QString());

private slots:
    void on_pushButton_clicked();

private:

    int m_NuberCounter;

    QStackedWidget *stackedWidget;
    QTabBar *bar;
    GeneralTab *tabWidget;
    QLabel *backupNameLabel;
    QLineEdit *backupNameEdit;
    QDialogButtonBox *buttonBox;

};

#endif // MAINWINDOW_H
