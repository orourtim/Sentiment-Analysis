/**
 * @author  Timothy O'Rourke
 * @date    3 June 2019
 * @brief   CS 331 Spring 2019 Sentiment Analysis
 */
#ifndef CLASSNODE_H
#define CLASSNODE_H

#include "AbstractNode.h"

class ClassNode : public AbstractNode {
private:
    double probability_table[2];

public:
    ClassNode();
    ~ClassNode();

    void FillProbabilityTable(const std::vector<FeatureVector>& vectors);
    double GetProbability(bool class_variable) const;
};

#endif