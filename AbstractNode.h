/**
 * @author  Timothy O'Rourke
 * @date    3 June 2019
 * @brief   CS 331 Spring 2019 Sentiment Analysis
 */
#ifndef ABSTRACTNODE_H
#define ABSTRACTNODE_H

#include "FeatureVector.h"

class AbstractNode {
public:
    AbstractNode() {};
    ~AbstractNode() {};

    virtual void FillProbabilityTable(const std::vector<FeatureVector>& vectors) = 0;
};

#endif