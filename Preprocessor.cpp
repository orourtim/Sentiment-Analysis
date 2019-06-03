/**
 * @author  Timothy O'Rourke
 * @date    6 June 2019
 * @brief   CS 331 Spring 2019 Sentiment Analysis
 */

#include "Preprocessor.h"

Preprocessor::Preprocessor(const std::string& training_file, const std::string& testing_file)
    : training_file(training_file), testing_file(testing_file)
{

}

Preprocessor::~Preprocessor()
{

}

PreprocessorData Preprocessor::Process()
{
    std::set<std::string> vocab = GetVocabulary();

    std::ofstream preprocessed_train("preprocessed_train.txt");

    for (auto it = vocab.begin(); it != vocab.end(); )
    {
        preprocessed_train << *it;

        ++it;
        if (it != vocab.end())
        {
            preprocessed_train << ',';
        }
    }
    preprocessed_train << std::endl;
    preprocessed_train.close();
}

std::set<std::string> Preprocessor::GetVocabulary()
{
    std::ifstream training_data(training_file);

    std::set<std::string> vocabulary;

    std::string trash;
    while (!training_data.eof())
    {
        std::string word = "";
        std::string line;

        std::getline(training_data, line, '\t');    // Grab line up to tab character.
        training_data >> trash;                     // Grab the classlabel.
        std::getline(training_data, trash);         // Grab the newline character.

        for (int i = 0; i < line.length(); i++)
        {
            if (IsSpace(line[i]) || WordsSeparatedByPunctuation(line, i))
            {
                if (!word.empty())
                {
                    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
                    vocabulary.insert(word);
                    word = "";
                }
            }
            else if (ValidCharacter(line[i]))
            {
                word += line[i];
            }
        }
    }
    training_data.close();
    return vocabulary;
}

bool Preprocessor::ValidCharacter(const char& c)
{
    std::string invalid_characters = ".,\'\"!?;:()-/*";

    std::size_t search = invalid_characters.find(c);
    if (search != std::string::npos)
    {
        return false;
    }
    return true;
}

bool Preprocessor::IsSpace(const char& c)
{
    return c == ' ';
}

bool Preprocessor::WordsSeparatedByPunctuation(const std::string& line, int i)
{
    return !ValidCharacter(line[i]) && ValidCharacter(line[i + 1]) && line[i] != '\'';
}