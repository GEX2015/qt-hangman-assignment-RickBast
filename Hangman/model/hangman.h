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
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <QPushButton>
#include <map>

enum class Images {imageOne, // enum class for the images of the gallows
                   imageTwo,
                   imageThree,
                   imageFour,
                   imageFive,
                   imageSix,
                   imageSeven};

class Hangman
{
public:
    Hangman();
    ~Hangman();    
    void guess(char); // gets a char as one guess
    void getNewPhrase(); // get a new phrase from file and resets guesses and keyboard
    Images show(); // displays the image to the user
    std::string getPhrase(); // show user the phrase after they lose
    std::string phraseWithUnderscores() const; // phrase with underscores
    bool guessed(char) const; // looks if the  letter has been guessed
    bool isWon() const; // looks if user has guessed the phrase
    bool isLost() const; // looks if user has made all his guesses and not won

private:
    std::vector<std::string> _words;
    std::string _phrase;
    std::set<char> _wrongGuesses; // set of wrong guesses
    std::set<char> _rightGuesses; // set of right guesses
    std::vector<QPushButton*> _letters; // letters the user can push to make a guess
    static const std::vector<Images> _img; // a vector for the images
};
