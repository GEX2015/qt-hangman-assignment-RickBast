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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <map>
#include <memory>
#include <vector>
namespace Ui {
class MainWindow;
}
class Hangman;
enum class Images;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    void draw(); // displays the view to the user
    void pause() const; // lets the user see won or lost message
    ~MainWindow();
public slots:
    void onLetterClicked(); // event handler for when a letter button is clicked on
    void onNewPhraseClicked(); // event when the new phrase button is clicked
private:
    Ui::MainWindow *ui;
    std::unique_ptr<Hangman> _game; // creates game of hangman
    const std::map<Images,QString> _image; // get image of current gallows
    std::vector<QPushButton*> _letters; // vector of letters guessed
    QLabel* _lblImg;
    QLabel* _lblPhrase;
};
#endif // MAINWINDOW_H
