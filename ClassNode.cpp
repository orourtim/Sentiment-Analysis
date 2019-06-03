/**
 * @author  Timothy O'Rourke
 * @date    3 June 2019
 * @brief   CS 331 Spring 2019 Sentiment Analysis
 */

#include "ClassNode.h"

ClassNode::ClassNode()
{
    probability_table[0] = -1.0;
    probability_table[1] = -1.0;
}

ClassNode::~ClassNode()
{

}

void ClassNode::FillProbabilityTable(const std::vector<FeatureVector>& vectors)
{
    for (int c = 0; c < 2; c++)
    {
        int matching_records = 0;
        int total_records = 0;

        for (auto it = vectors.begin(); it != vectors.end(); ++it)
        {
            int class_label = it->GetClassLabel();

            if (class_label == c)
            {
                matching_records++;
            }
            total_records++;
        }

        double probability = (matching_records * 1.0) / total_records;
        probability_table[c] = probability;
    }
}

double ClassNode::GetProbability(bool class_variable) const
{
    int x = 0;

    if (class_variable == true)
    {
        x = 1;
    }

    return probability_table[x];
}