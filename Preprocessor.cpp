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

}

std::set<std::string> Preprocessor::GetVocabulary()
{

}

bool Preprocessor::ValidCharacter(const char& c)
{
    std::string invalid_characters = ".,'\"!?;:()-";

    std::size_t search = invalid_characters.find(c);
    if (search != std::string::npos)
    {
        return false;
    }
    return true;
}