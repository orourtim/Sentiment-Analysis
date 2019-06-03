/**
 * @author  Timothy O'Rourke
 * @date    3 June 2019
 * @brief   CS 331 Spring 2019 Sentiment Analysis
 */
#ifndef FEATURENODE_H
#define FEATURENODE_H

#include "AbstractNode.h"

class FeatureNode : public AbstractNode {
private:
    const int NUM_OF_POSSIBLE_FEATURE_VALUES = 2;
    const int NUM_OF_POSSIBLE_CLASS_VALUES = 2;

    std::string word;
    double probability_table[2][2];

public:
    FeatureNode(std::string word);
    ~FeatureNode();

    void FillProbabilityTable(const std::vector<FeatureVector>& vectors);
    double GetProbability(bool feature, bool class_variable) const;
};

#endif