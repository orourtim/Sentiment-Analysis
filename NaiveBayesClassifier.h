/**
 * @author  Timothy O'Rourke
 * @date    3 June 2019
 * @brief   CS 331 Spring 2019 Sentiment Analysis
 */
#ifndef NAIVEBAYESCLASSIFIER_H
#define NAIVEBAYESCLASSIFIER_H

#include "FeatureVector.h"
#include "FeatureNode.h"
#include "ClassNode.h"

#include <algorithm>

class NaiveBayesClassifier {
private:
    std::vector<FeatureVector> training_vector;
    std::vector<FeatureVector> test_vector;
    std::set<std::string> vocabulary;
    std::vector<FeatureNode> feature_nodes;
    ClassNode class_node;
    std::vector<int> result_vector;

    void Train();
    void Test();
    double CalculateYValue(bool Y, const std::vector<FeatureVector>::iterator& it);
public:
    NaiveBayesClassifier(const std::vector<FeatureVector>& training_vector, const std::vector<FeatureVector>& test_vector, const std::set<std::string>& vocabulary);
    ~NaiveBayesClassifier();

    void Run();
    
    std::vector<int> GetResults() const { return result_vector; }
};

#endif