#include "mainwindow.h"
#include "generaltab.h"
#include <QtWidgets>


TabDialog::TabDialog(const QString &fileName, QWidget *parent)
    : QDialog(parent),m_NuberCounter(0)
{

    QFileInfo fileInfo(fileName);


    QPushButton *addTabButton = new QPushButton(tr("Create new backup session"));
    connect(addTabButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));

    buttonBox = new QDialogButtonBox(Qt::Horizontal);
    buttonBox->addButton(addTabButton, QDialogButtonBox::ActionRole);

    setWindowTitle(tr("QtBorg"));


    bar = new QTabBar();


    QVBoxLayout *mainLayout = new QVBoxLayout;

    stackedWidget = new QStackedWidget;

    mainLayout->addWidget(bar);
    mainLayout->addWidget(stackedWidget);
    mainLayout->addWidget(buttonBox);

    mainLayout->setAlignment(Qt::AlignTop);


    // Some simple connect with lambda for navigation
    connect(bar, &QTabBar::currentChanged, [=] (int index) {
                 emit stackedWidget->setCurrentIndex(index);

    });


    setLayout(mainLayout);

    setWindowTitle(tr("QtBorg"));

    setGeometry(geometry().x(),geometry().y(), 600, 400);

}


void TabDialog::on_pushButton_clicked()
{
    bar->addTab("One");
    QFileInfo fileInfo("");
    stackedWidget->addWidget(new GeneralTab(fileInfo));
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
