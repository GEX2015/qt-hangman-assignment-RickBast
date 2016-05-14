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
#include "Hangman.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
#include <ctime>

Images Hangman::show()
{
    switch (_wrongGuesses.size())
    {
    case 0:\
        return Images::imageOne;
        break;
    case 1:
        return Images::imageTwo;
        break;
    case 2:
        return Images::imageThree;
        break;
    case 3:
        return Images::imageFour;
        break;
    case 4:
        return Images::imageFive;
        break;
    case 5:
        return Images::imageSix;
        break;
    default:
        return Images::imageSeven;
        break;
    }
}

void Hangman::guess(char c)
{
    if(isWon() || isLost())
        return;
    if (std::string::npos == _phrase.find(c))
        _wrongGuesses.insert(c);
    else
        _rightGuesses.insert(c);
}

void Hangman::getNewPhrase()
{
    _rightGuesses.clear();
    _wrongGuesses.clear();
    srand(unsigned(time(0)));
    _phrase = _words[rand() % _words.size()];
    _rightGuesses.insert(' ');
}

std::string Hangman::phraseWithUnderscores() const
{
    std::stringstream ss;
    for (char c : _phrase)
        if (_rightGuesses.find(c) != _rightGuesses.end())
            ss << c << " ";
        else
            ss << "_ ";
    return ss.str();
}

bool Hangman::guessed(char c) const
{
    if (_rightGuesses.find(c) != _rightGuesses.end() || _wrongGuesses.find(c) != _wrongGuesses.end())
        return true;
    else
        return false;
}

bool Hangman::isWon() const
{
    for (char c : _phrase)
        if (_rightGuesses.find(c) == _rightGuesses.end())
            return false;
    return true;
}

bool Hangman::isLost() const
{
    if (_wrongGuesses.size() == 6)
        return true;
    else
        return false;
}

Hangman::Hangman()
{
    std::ifstream ifile;
    ifile.open("/words.txt");

    if (ifile.fail())
        exit(EXIT_FAILURE);
    else
        while (!ifile.eof())
        {
            getline(ifile, _phrase);
            _words.push_back(_phrase);
        }
    ifile.close();
}

std::string Hangman::getPhrase(){
    return _phrase;
}

Hangman::~Hangman()
{
}
