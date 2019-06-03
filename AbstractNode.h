/**
 * @author  Timothy O'Rourke
 * @date    3 June 2019
 * @brief   CS 331 Spring 2019 Sentiment Analysis
 */

#include "FeatureVector.h"

class AbstractNode {
public:
    AbstractNode() {};
    ~AbstractNode() {};

    virtual void FillProbabilityTable(std::vector<FeatureVector> vectors) = 0;
};