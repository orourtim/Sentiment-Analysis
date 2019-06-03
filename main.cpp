/**
 * @author  Timothy O'Rourke
 * @date    3 June 2019
 * @brief   CS 331 Spring 2019 Sentiment Analysis
 */

#include <iostream>
#include <iomanip>

#include "Preprocessor.h"
#include "FeatureVector.h"
#include "FeatureNode.h"
#include "ClassNode.h"
#include "NaiveBayesClassifier.h"

void OutputResults(const std::vector<int>& training_results, const std::vector<int>& test_results, PreprocessorData data);
double GetAccuracy(const std::vector<int>& results, const std::vector<FeatureVector>& vectors);

int main(int argc, char* argv[])
{
    Preprocessor preprocessor("trainingSet.txt", "testSet.txt");
    std::cout << "Preprocessing..." << std::endl;
    PreprocessorData data = preprocessor.Process();

    NaiveBayesClassifier training_classifier(data.training_vector, data.training_vector, data.vocabulary);
    NaiveBayesClassifier test_classifier(data.training_vector, data.test_vector, data.vocabulary);
    std::cout << "Classification..." << std::endl;
    training_classifier.Run();
    test_classifier.Run();

    std::vector<int> training_results = training_classifier.GetResults();
    std::vector<int> test_results = test_classifier.GetResults();

    std::cout << "Outputting to console and \"results.txt\"..." << std::endl;
    OutputResults(training_results, test_results, data);
}

void OutputResults(const std::vector<int>& training_results, const std::vector<int>& test_results, PreprocessorData data)
{
    double training_accuracy = GetAccuracy(training_results, data.training_vector);
    double test_accuracy = GetAccuracy(test_results, data.test_vector);

    std::ofstream result_file("results.txt");

    result_file << "Training File: \"trainingSet.txt\", Testing File: \"trainingSet.txt\" --- Accuracy: " << std::setprecision(4) << training_accuracy << "%" << std::endl;
    result_file << "Training File: \"trainingSet.txt\", Testing File: \"testSet.txt\" --- Accuracy: " << std::setprecision(4) << test_accuracy << "%" << std::endl;

    std::cout << "Training File: \"trainingSet.txt\", Testing File: \"trainingSet.txt\" --- Accuracy: " << std::setprecision(4) << training_accuracy << "%" << std::endl;
    std::cout << "Training File: \"trainingSet.txt\", Testing File: \"testSet.txt\" --- Accuracy: " << std::setprecision(4) << test_accuracy << "%" << std::endl;

    result_file.close();
}

double GetAccuracy(const std::vector<int>& results, const std::vector<FeatureVector>& vectors)
{
    int correct = 0;
    int total = 0;
    auto feature_vector = vectors.begin();
    auto result = results.begin();
    for (feature_vector, result; result != results.end(); ++feature_vector, ++result)
    {
        if (*result == feature_vector->GetClassLabel())
        {
            correct++;
        }
        total++;
    }
    return ((correct * 1.0) / total) * 100;
}