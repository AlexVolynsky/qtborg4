#include "mainwindow.h"
#include "generaltab.h"
#include <QtWidgets>


TabDialog::TabDialog(const QString &fileName, QWidget *parent)
    : QDialog(parent),m_NuberCounter(0)
{

    QFileInfo fileInfo(fileName);

    QRegularExpression regex("^[a-zA-Z0-9_//.-@]*$");
    QValidator *validator = new QRegularExpressionValidator(regex, this);

    backupNameLabel = new QLabel(tr("Name:"));
    backupNameEdit = new QLineEdit (fileInfo.fileName());
    backupNameEdit->setValidator(validator);

    QPushButton *addTabButton = new QPushButton(tr("Create new backup session"));
    connect(addTabButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));

    buttonBox = new QDialogButtonBox(Qt::Horizontal);
    buttonBox->addButton(addTabButton, QDialogButtonBox::ActionRole);

    setWindowTitle(tr("QtBorg"));


    bar = new QTabBar();


    QVBoxLayout *mainLayout = new QVBoxLayout;

    QHBoxLayout *horizLayout = new QHBoxLayout;
    stackedWidget = new QStackedWidget;


    horizLayout->addWidget(backupNameLabel);
    horizLayout->addWidget(backupNameEdit);
    horizLayout->addWidget(buttonBox);

    mainLayout->addWidget(bar);
    mainLayout->addWidget(stackedWidget);
    mainLayout->addLayout(horizLayout);

    mainLayout->setAlignment(Qt::AlignTop);


    // Some simple connect with lambda for navigation
    connect(bar, &QTabBar::currentChanged, [=] (int index) {
                 emit stackedWidget->setCurrentIndex(index);

    });


    setLayout(mainLayout);

    setWindowTitle(tr("QtBorg"));

    setGeometry(geometry().x(),geometry().y(), 1200, 900);

}


void TabDialog::on_pushButton_clicked()
{
    QString tabName("");
    ++m_NuberCounter;
    if(backupNameEdit->text().trimmed().isEmpty() ||
       backupNameEdit->text().trimmed().length() > 16)
    {
       tabName =  QString("Backup") + QString::number(m_NuberCounter);
    }
    else
    {
        tabName = backupNameEdit->text().trimmed();
    }

    bar->addTab(tabName);

    stackedWidget->addWidget(new GeneralTab(tabName));
}


QPushButton *TabDialog::createButton(const QString &text, const char *member)
{
    QPushButton *button = new QPushButton(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}

QComboBox *TabDialog::createComboBox(const QString &text)
{
    QComboBox *comboBox = new QComboBox;
    comboBox->setEditable(true);
    comboBox->addItem(text);
    comboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    return comboBox;
}

