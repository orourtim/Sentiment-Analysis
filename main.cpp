/**
 * @author  Timothy O'Rourke
 * @date    6 June 2019
 * @brief   CS 331 Spring 2019 Sentiment Analysis
 */

#include <iostream>

#include "Preprocessor.h"
#include "FeatureVector.h"

int main(int argc, char* argv[])
{
    std::set<std::string> vocab = {"tim", "cute", "good"};
    FeatureVector f(vocab);

    std::cout << "tim exists: " << f.Exists("tim") << std::endl
              << "cute exists: " << f.Exists("cute") << std::endl
              << "good exists: " << f.Exists("good") << std::endl;

    std::cout << "SetExists on \"good\": ";

    f.SetExists("good");

    std::cout << f.Exists("good") << std::endl;

    Preprocessor p("trainingSet.txt", "testSet.txt");

    PreprocessorData d = p.Process();
}