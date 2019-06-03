/**
 * @author  Timothy O'Rourke
 * @date    2 June 2019
 * @brief   CS 331 Spring 2019 Sentiment Analysis
 */

#include <iostream>

#include "Preprocessor.h"
#include "FeatureVector.h"
#include "FeatureNode.h"
#include "ClassNode.h"
#include "NaiveBayesClassifier.h"

int main(int argc, char* argv[])
{
    // std::set<std::string> vocab = {"tim", "cute", "good"};
    // FeatureVector f(vocab);

    // std::cout << "tim exists: " << f.Exists("tim") << std::endl
    //           << "cute exists: " << f.Exists("cute") << std::endl
    //           << "good exists: " << f.Exists("good") << std::endl;

    // std::cout << "SetExists on \"good\": ";

    // f.SetExists("good");

    // std::cout << f.Exists("good") << std::endl;

    Preprocessor p("trainingSet.txt", "testSet.txt");

    PreprocessorData d = p.Process();

    // FeatureNode node("nice");
    // node.FillProbabilityTable(d.training_vector);
    // double prob1 = node.GetProbability(false, false);
    // double prob2 = node.GetProbability(false, true);
    // double prob3 = node.GetProbability(true, false);
    // double prob4 = node.GetProbability(true, true);

    // std::cout.precision(2);
    // std::cout << "P(\"nice\" = false | classlabel = false) = " << std::fixed << prob1 << std::endl;
    // std::cout << "P(\"nice\" = false | classlabel = true) = " << std::fixed << prob2 << std::endl;
    // std::cout << "P(\"nice\" = true | classlabel = false) = " << std::fixed << prob3 << std::endl;
    // std::cout << "P(\"nice\" = true | classlabel = true) = " << std::fixed << prob4 << std::endl;

    // ClassNode cNode;
    // cNode.FillProbabilityTable(d.training_vector);
    // double prob5 = cNode.GetProbability(false);
    // double prob6 = cNode.GetProbability(true);

    std::cout.precision(2);
    // std::cout << "P(classlabel = false) = " << std::fixed << prob5 << std::endl;
    // std::cout << "P(classlabel = true) = " << std::fixed << prob6 << std::endl;

    NaiveBayesClassifier classifier(d.training_vector, d.test_vector, d.vocabulary);
    classifier.Run();

    std::vector<int> results = classifier.GetResults();

    int correct = 0;
    int total = 0;
    auto test = d.test_vector.begin();
    auto result = results.begin();
    for (test, result; result != results.end(); ++test, ++result)
    {
        if (*result == test->GetClassLabel())
        {
            correct++;
        }
        total++;
    }
    std::cout << "trainingSet.txt, testSet.txt --- Accuracy: " << std::fixed << ((correct * 1.0) / total) * 100 << "%"<< std::endl;

    NaiveBayesClassifier classifier2(d.training_vector, d.training_vector, d.vocabulary);
    classifier2.Run();

    std::vector<int> results2 = classifier2.GetResults();

    int correct2 = 0;
    int total2 = 0;
    auto test2 = d.training_vector.begin();
    auto result2 = results2.begin();
    for (test2, result2; result2 != results2.end(); ++test2, ++result2)
    {
        if (*result2 == test2->GetClassLabel())
        {
            correct2++;
        }
        total2++;
    }
    std::cout << "trainingSet.txt, trainingSet.txt --- Accuracy: " << std::fixed << ((correct2 * 1.0) / total2) * 100 << "%"<< std::endl;
}