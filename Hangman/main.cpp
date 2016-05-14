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
#include "controller/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainW;
    mainW.show();
    return a.exec();
}
