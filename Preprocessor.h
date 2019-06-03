/**
 * @author  Timothy O'Rourke
 * @date    6 June 2019
 * @brief   CS 331 Spring 2019 Sentiment Analysis
 */
#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include "FeatureVector.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

struct PreprocessorData { std::vector<FeatureVector> training_vector; std::vector<FeatureVector> testing_vector; };

class Preprocessor {
private:
    std::string training_file;
    std::string test_file;

    
    bool ValidCharacter(const char& c);
    bool IsSpace(const char& c);
    bool WordsSeparatedByPunctuation(const std::string& line, int i);
public:
    Preprocessor(const std::string& training_file, const std::string& test_file);
    ~Preprocessor();

    PreprocessorData Process();
    std::set<std::string> GetVocabulary();
};

#endif