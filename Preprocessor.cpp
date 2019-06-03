/**
 * @author  Timothy O'Rourke
 * @date    6 June 2019
 * @brief   CS 331 Spring 2019 Sentiment Analysis
 */

#include "Preprocessor.h"

Preprocessor::Preprocessor(const std::string& training_file, const std::string& test_file)
    : training_file(training_file), test_file(test_file)
{

}

Preprocessor::~Preprocessor()
{

}

PreprocessorData Preprocessor::Process()
{
    std::set<std::string> vocabulary = GetVocabulary();
    PreprocessorData vectors;

    std::ofstream preprocessed_train("preprocessed_train.txt");
    std::ofstream preprocessed_test("preprocessed_test.txt");
    std::ifstream training_data(training_file);
    std::ifstream test_data(test_file);

    // Insert the vocabulary upon the first line of each file.
    for (auto it = vocabulary.begin(); it != vocabulary.end(); )
    {
        preprocessed_train << *it;
        preprocessed_test << *it;

        ++it;
        if (it != vocabulary.end())
        {
            preprocessed_train << ',';
            preprocessed_test << ',';
        }
        else
        {
            preprocessed_train << ",classlabel";
            preprocessed_test << ",classlabel";
        }
    }
    preprocessed_train << std::endl;
    preprocessed_test << std::endl;

    // Create training and test feature vectors.
    std::string trash;
    int class_label;
    while (!training_data.eof())
    {
        std::string word = "";
        std::string line;

        std::getline(training_data, line, '\t');    // Grab line up to tab character.
        training_data >> class_label;               // Grab the classlabel.
        std::getline(training_data, trash);         // Grab the newline character.

        if (training_data.eof())
        {
            break;
        }

        FeatureVector feature_vector(vocabulary);
        feature_vector.SetClassLabel(class_label);
        for (int i = 0; i < line.length(); i++)
        {
            if (IsSpace(line[i]) || WordsSeparatedByPunctuation(line, i))
            {
                if (!word.empty())
                {
                    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
                    feature_vector.SetExists(word);
                    word = "";
                }
            }
            else if (ValidCharacter(line[i]))
            {
                word += line[i];
            }
        }
        vectors.training_vector.push_back(feature_vector);
    }

    while (!test_data.eof())
    {
        std::string word = "";
        std::string line;

        std::getline(test_data, line, '\t');    // Grab line up to tab character.
        test_data >> class_label;               // Grab the classlabel.
        std::getline(test_data, trash);         // Grab the newline character.

        if (test_data.eof())
        {
            break;
        }

        FeatureVector feature_vector(vocabulary);
        feature_vector.SetClassLabel(class_label);
        for (int i = 0; i < line.length(); i++)
        {
            if (IsSpace(line[i]) || WordsSeparatedByPunctuation(line, i))
            {
                if (!word.empty())
                {
                    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
                    feature_vector.SetExists(word);
                    word = "";
                }
            }
            else if (ValidCharacter(line[i]))
            {
                word += line[i];
            }
        }
        vectors.testing_vector.push_back(feature_vector);
    }

    // Input the feature vectors into the files.
    for (auto it = vectors.training_vector.begin(); it != vectors.training_vector.end(); ++it)
    {
        for (auto word = vocabulary.begin(); word != vocabulary.end(); ++word)
        {
            preprocessed_train << it->Exists(*word) << ',';
        }
        preprocessed_train << it->GetClassLabel();
        preprocessed_train << std::endl;
    }

    for (auto it = vectors.testing_vector.begin(); it != vectors.testing_vector.end(); ++it)
    {
        for (auto word = vocabulary.begin(); word != vocabulary.end(); ++word)
        {
            preprocessed_test << it->Exists(*word) << ',';
        }
        preprocessed_test << it->GetClassLabel();
        preprocessed_test << std::endl;
    }

    preprocessed_train.close();
    preprocessed_test.close();
    training_data.close();
    test_data.close();

    return vectors;
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