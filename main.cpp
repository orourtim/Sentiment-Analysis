/**
 * @author  Timothy O'Rourke
 * @date    6 June 2019
 * @brief   CS 331 Spring 2019 Sentiment Analysis
 */

#include <iostream>

#include "FeatureVector.h"

int main(int argc, char* argv[])
{
    FeatureVector f;

    f.AddWord("tim", true);
    f.AddWord("cute", true);
    f.AddWord("good", false);

    std::cout << "tim exists: " << f.Exists("tim") << std::endl
              << "cute exists: " << f.Exists("cute") << std::endl
              << "good exists: " << f.Exists("good") << std::endl;

}