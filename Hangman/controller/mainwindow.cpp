/////////////////////////////////////////////////////////////////////
// File:  Source.cpp
//
// Author: Ricky Bastarache
// This assignment represents my own work and is in accordance with the College Academic Policy
//
// Copyright (c) 2016 All Right Reserved by Dave Burchill
// Contributors:
// Description:
//
// Date: May 2016
//
// Revisions:
//
/////////////////////////////////////////////////////////////////////
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../model/hangman.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QTime>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _image({ {Images::imageOne, "border-image:url(:/images/gallows0.png)"},
{Images::imageTwo, "border-image:url(:/images/gallows1.png)"},
{Images::imageThree, "border-image:url(:/images/gallows2.png)"},
{Images::imageFour, "border-image:url(:/images/gallows3.png)"},
{Images::imageFive, "border-image:url(:/images/gallows4.png)"},
{Images::imageSix, "border-image:url(:/images/gallows5.png)"},
{Images::imageSeven,"border-image:url(:/images/gallows6.png)"}})
{
    ui->setupUi(this);
    _game = std::unique_ptr<Hangman>(new Hangman());
    auto vl = new QVBoxLayout(ui->centralWidget);
    auto gl = new QGridLayout();
    auto hblTop = new QHBoxLayout();
    auto hblPhrase = new QHBoxLayout();
    auto hblBtn = new QHBoxLayout();
    _lblImg = new QLabel();
    _lblImg->setMaximumSize(300,300);
    _lblImg->setMinimumSize(300,300);
    // Creates letters a - z
    for (char c='a'; c <= 'z'; ++c)
    {
        auto btn = new QPushButton(); // creates button for every letter
        btn->setMinimumSize(20,20);
        btn->setMaximumSize(20,20);
        btn->setText(QString(c));
        gl->addWidget(btn, (c - 'a') / 13, (c - 'a') % 13); // c-a is a 0 based index
        connect(btn, &QPushButton::clicked, this,&MainWindow::onLetterClicked); // connects every letter button to the function
        _letters.push_back(btn);
    }

    hblTop->addWidget(_lblImg); // adds label to the layout
    QSpacerItem *spacer = new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Fixed);
    hblTop->addSpacerItem(spacer);
    hblTop->addLayout(gl);
    vl->addLayout(hblTop);
    QSpacerItem *spacer1 = new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Fixed);
    _lblPhrase = new QLabel;  // Label for the Phrase
    _lblPhrase->setMaximumSize(350,30);
    _lblPhrase->setMinimumSize(350,30);
    _lblPhrase->setFrameStyle(QFrame::NoFrame);
    hblPhrase->addWidget(_lblPhrase);
    hblPhrase->addSpacerItem(spacer1);
    vl->addLayout(hblPhrase);
    QSpacerItem *spacer2 = new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Fixed);
    auto btnNewPhrase= new QPushButton();
    btnNewPhrase->setMaximumSize(100,25);
    btnNewPhrase->setMaximumSize(100,25);
    btnNewPhrase->setText(QString("New phrase"));
    hblBtn->addSpacerItem(spacer2);
    hblBtn->addWidget(btnNewPhrase);
    connect(btnNewPhrase, &QPushButton::clicked, this, &MainWindow::onNewPhraseClicked);
    vl->addLayout(hblBtn);
    _game->getNewPhrase();
    QString word = QString::fromStdString(_game->phraseWithUnderscores());
    _lblPhrase->setText(word);
    draw();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::draw()
{
    QString word = QString::fromStdString(_game->phraseWithUnderscores());
    _lblPhrase->setText(word);
    _lblImg->setStyleSheet(_image.at(_game->show()));

    for (auto btn : _letters)
    {
        QString letter = btn->text();
        std::string letterGuessed = letter.toLocal8Bit().constData();
        char c = letterGuessed.at(0);
        if(_game->guessed(c))
            btn->setEnabled(false);
        else
            btn->setEnabled(true);
    }
    static bool over = false;
    if(_game->isWon() && !over)
    {
        over = true;
        QMessageBox overMsg;
        overMsg.setText("You win!!!");
        overMsg.show();
        pause();
    }
    if(!_game->isWon())
        over = false;
    if(_game->isLost())
    {
        QString word = QString::fromStdString(_game->getPhrase());
        _lblPhrase->setText(word);
        over = true;
        QMessageBox endMessage;
        endMessage.setText("You lose :(");
        endMessage.show();
        pause();
    }
}

void MainWindow::onLetterClicked()
{
    QPushButton* btn = dynamic_cast<QPushButton*>(sender());
    QString letter = btn->text();
    std::string lettrGuessed = letter.toLocal8Bit().constData();
    char c = lettrGuessed.at(0);
    _game->guess(c);
    draw();
}

void MainWindow::onNewPhraseClicked()
{
    _game->getNewPhrase();
    draw();
}

void MainWindow::pause() const
{
    QTime wait = QTime::currentTime().addSecs(5);
    while (QTime::currentTime() < wait)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
