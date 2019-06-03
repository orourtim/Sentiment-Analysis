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
    Test();
}

void NaiveBayesClassifier::Train()
{
    for (auto it = feature_nodes.begin(); it != feature_nodes.end(); ++it)
    {
        it->FillProbabilityTable(training_vector);
    }
    class_node.FillProbabilityTable(training_vector);
}

void NaiveBayesClassifier::Test()
{
    for (auto it = test_vector.begin(); it != test_vector.end(); ++it)
    {
        bool class_label_value = false;
        double class_label_false = 0.0;
        double class_label_true = 0.0;

        // With class label false.
        auto word = vocabulary.begin();
        auto node = feature_nodes.begin();
        for (word, node; word != vocabulary.end(); ++word, ++node)
        {
            bool exists = it->Exists(*word);
            double probability = node->GetProbability(exists, class_label_value);
            probability = log(probability);
            class_label_false += probability;
        }
        class_label_false += log(class_node.GetProbability(class_label_value));

        // With class label true.
        class_label_value = true;
        word = vocabulary.begin();
        node = feature_nodes.begin();
        for (word, node; word != vocabulary.end(); ++word, ++node)
        {
            bool exists = it->Exists(*word);
            double probability = node->GetProbability(exists, class_label_value);
            probability = log(probability);
            class_label_true += probability;
        }
        class_label_true += log(class_node.GetProbability(class_label_value));

        // Argmax
        double max = std::max(class_label_false, class_label_true);

        if (max == class_label_false)
        {
            result_vector.push_back(0);
        }
        else
        {
            result_vector.push_back(1);
        }
    }
}