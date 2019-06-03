/**
 * @author  Timothy O'Rourke
 * @date    2 June 2019
 * @brief   CS 331 Spring 2019 Sentiment Analysis
 */

#include <iostream>

#include "Preprocessor.h"
#include "FeatureVector.h"
#include "FeatureNode.h"

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

    FeatureNode node("nice");
    node.FillProbabilityTable(d.training_vector);
    double prob1 = node.GetProbability(false, false);
    double prob2 = node.GetProbability(false, true);
    double prob3 = node.GetProbability(true, false);
    double prob4 = node.GetProbability(true, true);

    std::cout.precision(17);
    std::cout << "P(\"nice\" = false | classlabel = false) = " << std::fixed << prob1 << std::endl;
    std::cout << "P(\"nice\" = false | classlabel = true) = " << std::fixed << prob2 << std::endl;
    std::cout << "P(\"nice\" = true | classlabel = false) = " << std::fixed << prob3 << std::endl;
    std::cout << "P(\"nice\" = true | classlabel = true) = " << std::fixed << prob4 << std::endl;

}