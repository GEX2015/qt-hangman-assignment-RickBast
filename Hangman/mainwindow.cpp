#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto vlMain = new QVBoxLayout(ui->centralWidget);
    auto glLetters = new QGridLayout();
    //letters

    for( char c = 'a'; c <= 'z'; ++c)
    {
        auto btn = new QPushButton();
        btn->setMinimumSize(20,20);
        btn->setMaximumSize(20,20);
        btn->setText(QString(c));
        int idx = c - 'a';
        glLetters->addWidget(btn, idx/6, idx%6);

        connect(btn,&QPushButton::clicked, this, &MainWindow::onLetterClicked);
    }
    vlMain->addLayout(glLetters);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onLetterClicked()
{
   QPushButton* btn = dynamic_cast<QPushButton*>(sender());



   btn->setEnabled(false);
   qWarning() << btn->text();
}
