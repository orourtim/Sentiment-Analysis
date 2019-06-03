/**
 * @author  Timothy O'Rourke
 * @date    2 June 2019
 * @brief   CS 331 Spring 2019 Sentiment Analysis
 */

#include "FeatureVector.h"
#include <iostream>

FeatureVector::FeatureVector(std::set<std::string> vocabulary)
{
    for (auto it = vocabulary.begin(); it != vocabulary.end(); it++)
    {
        AddWord(*it, false);
    }
}

FeatureVector::~FeatureVector()
{

}

void FeatureVector::AddWord(std::string word, bool exists)
{
    Word w = {word, exists};
    words.insert(w);
}

bool FeatureVector::Exists(std::string word) const
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

void FeatureVector::SetExists(std::string word)
{
    Key w = {word};

    auto search = words.find(w);
    if (search != words.end() && search->exists == false)
    {
        words.erase(search);
        AddWord(word, true);
    }
}