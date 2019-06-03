/**
 * @author  Timothy O'Rourke
 * @date    3 June 2019
 * @brief   CS 331 Spring 2019 Sentiment Analysis
 */

#include "NaiveBayesClassifier.h"

NaiveBayesClassifier::NaiveBayesClassifier(std::vector<FeatureVector> training_vector, std::vector<FeatureVector> test_vector, std::set<std::string> vocabulary)
    : training_vector(training_vector), test_vector(test_vector), vocabulary(vocabulary)
{
    for (auto it = vocabulary.begin(); it != vocabulary.end(); ++it)
    {
        FeatureNode temp(*it);
        feature_nodes.push_back(temp);
    }
    ClassNode temp;
    class_node = temp;
}

NaiveBayesClassifier::~NaiveBayesClassifier()
{

}

void NaiveBayesClassifier::Run()
{
    Train();
}

void NaiveBayesClassifier::Train()
{
    for (auto it = feature_nodes.begin(); it != feature_nodes.end(); ++it)
    {
        it->FillProbabilityTable(training_vector);
    }
    class_node.FillProbabilityTable(training_vector);
}