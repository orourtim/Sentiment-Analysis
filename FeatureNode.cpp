/**
 * @author  Timothy O'Rourke
 * @date    3 June 2019
 * @brief   CS 331 Spring 2019 Sentiment Analysis
 */

#include "FeatureNode.h"

FeatureNode::FeatureNode(std::string word)
    : word(word)
{
    for (int i = 0; i < NUM_OF_POSSIBLE_FEATURE_VALUES; i++)
    {
        for (int j = 0; j < NUM_OF_POSSIBLE_CLASS_VALUES; j++)
        {
            probability_table[i][j] = -1.0;
        }
    }
}

FeatureNode::~FeatureNode()
{

}

void FeatureNode::FillProbabilityTable(const std::vector<FeatureVector>& vectors)
{
    for (int feature = 0; feature < NUM_OF_POSSIBLE_FEATURE_VALUES; feature++)
    {
        for (int c = 0; c < NUM_OF_POSSIBLE_CLASS_VALUES; c++)
        {
            int x_and_y = 0;
            int y = 0;

            for (auto it = vectors.begin(); it != vectors.end(); ++it)
            {
                bool exists = it->Exists(word);
                int class_label = it->GetClassLabel();

                if ( (exists == false && feature == 0) && (class_label == c) )
                {
                    x_and_y++;
                }
                else if ( (exists == true && feature == 1) && (class_label == c) )
                {
                    x_and_y++;
                }

                if (class_label == c)
                {
                    y++;
                }
            }

            double conditional_probability = (x_and_y + 1.0) / (y + NUM_OF_POSSIBLE_FEATURE_VALUES);
            probability_table[feature][c] = conditional_probability;
        }
    }
}

double FeatureNode::GetProbability(bool feature, bool class_variable) const
{
    int x = 0; 
    int y = 0;
    if (feature == true)
    {
        x = 1;
    }

    if (class_variable == true)
    {
        y = 1;
    }

    return probability_table[x][y];
}