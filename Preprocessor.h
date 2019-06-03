/**
 * @author  Timothy O'Rourke
 * @date    2 June 2019
 * @brief   CS 331 Spring 2019 Sentiment Analysis
 */
#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include "FeatureVector.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

struct PreprocessorData { std::vector<FeatureVector> training_vector; std::vector<FeatureVector> test_vector; std::set<std::string> vocabulary; };

class Preprocessor {
private:
    std::string training_file;
    std::string test_file;

    std::set<std::string> GetVocabulary();
    bool ValidCharacter(const char& c);
    bool IsSpace(const char& c);
    bool WordsSeparatedByPunctuation(const std::string& line, int i);
    void InsertVocabularyIntoFile(std::ofstream& preprocessed_file, const std::set<std::string>& vocabulary);
    std::vector<FeatureVector> GetFeatureVectors(std::ifstream& data, const std::set<std::string>& vocabulary);
    void InsertFeatureVectorsIntoFile(std::ofstream& preprocessed_file, std::vector<FeatureVector>& vectors, const std::set<std::string>& vocabulary);
public:
    Preprocessor(const std::string& training_file, const std::string& test_file);
    ~Preprocessor();

    PreprocessorData Process();
};

#endif