/**
 * @author  Timothy O'Rourke
 * @date    6 June 2019
 * @brief   CS 331 Spring 2019 Sentiment Analysis
 */

#include "FeatureVector.h"
#include <iostream>

FeatureVector::FeatureVector()
{

}

FeatureVector::~FeatureVector()
{

}

void FeatureVector::AddWord(std::string word, bool exists)
{
    Word w = {word, exists};
    words.insert(w);
}

bool FeatureVector::Exists(std::string word)
{
    Key w = {word};

    auto search = words.find(w);
    if (search != words.end() && search->exists == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}