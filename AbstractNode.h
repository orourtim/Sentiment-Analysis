/**
 * @author  Timothy O'Rourke
 * @date    3 June 2019
 * @brief   CS 331 Spring 2019 Sentiment Analysis
 */

class AbstractNode {
public:
    AbstractNode() {};
    ~AbstractNode() {};

    virtual void FillProbabilityTable() = 0;
};