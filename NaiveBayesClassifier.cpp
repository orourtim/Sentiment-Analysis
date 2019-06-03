/**
 * @author  Timothy O'Rourke
 * @date    3 June 2019
 * @brief   CS 331 Spring 2019 Sentiment Analysis
 */

#include "NaiveBayesClassifier.h"

NaiveBayesClassifier::NaiveBayesClassifier(const std::vector<FeatureVector>& training_vector, const std::vector<FeatureVector>& test_vector, const std::set<std::string>& vocabulary)
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
    Test();
}

void NaiveBayesClassifier::Train()
{
    for (auto each_node = feature_nodes.begin(); each_node != feature_nodes.end(); ++each_node)
    {
        each_node->FillProbabilityTable(training_vector);
    }
    class_node.FillProbabilityTable(training_vector);
}

void NaiveBayesClassifier::Test()
{
    for (auto each_vector = test_vector.begin(); each_vector != test_vector.end(); ++each_vector)
    {
        double Y_false_value = CalculateYValue(false, each_vector);
        double Y_true_value = CalculateYValue(true, each_vector);

        // Max of Y_false_value and Y_true_value is our prediction.
        if (Y_true_value > Y_false_value)
        {
            result_vector.push_back(1);
        }
        else
        {
            result_vector.push_back(0);
        }
    }
}

double NaiveBayesClassifier::CalculateYValue(bool Y, const std::vector<FeatureVector>::iterator& it)
{
    double Y_value = 0.0;
    auto word = vocabulary.begin();
    auto node = feature_nodes.begin();
    for (word, node; word != vocabulary.end(); ++word, ++node)
    {
        bool exists = it->Exists(*word);
        double probability = node->GetProbability(exists, Y);
        probability = log(probability);
        Y_value += probability;
    }
    Y_value += log(class_node.GetProbability(Y));

    return Y_value;
}