/**
 * @author  Timothy O'Rourke
 * @date    2 June 2019
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
    PreprocessorData data;
    std::set<std::string> vocabulary = GetVocabulary();
    data.vocabulary = vocabulary;

    std::ofstream preprocessed_train("preprocessed_train.txt");
    std::ofstream preprocessed_test("preprocessed_test.txt");
    std::ifstream training_data(training_file);
    std::ifstream test_data(test_file);

    InsertVocabularyIntoFile(preprocessed_train, vocabulary);
    InsertVocabularyIntoFile(preprocessed_test, vocabulary);

    data.training_vector = GetFeatureVectors(training_data, vocabulary);
    data.test_vector = GetFeatureVectors(test_data, vocabulary);

    InsertFeatureVectorsIntoFile(preprocessed_train, data.training_vector, vocabulary);
    InsertFeatureVectorsIntoFile(preprocessed_test, data.test_vector, vocabulary);

    preprocessed_train.close();
    preprocessed_test.close();
    training_data.close();
    test_data.close();

    return data;
}

std::set<std::string> Preprocessor::GetVocabulary()
{
    std::ifstream training_data(training_file);
    std::set<std::string> vocabulary;
    std::string class_label = "";
    std::string line = "";
    std::string word = "";

    while (!training_data.eof())                    // For each line.
    {
        std::getline(training_data, line, '\t');    // Grab line up to tab character.
        training_data >> class_label;               // Grab the classlabel.
        std::getline(training_data, class_label);   // Grab the newline character.

        for (int i = 0; i < line.length(); i++)     // For each character in the line.
        {
            if (IsSpace(line[i]) || WordsSeparatedByPunctuation(line, i))
            {
                if (!word.empty())
                {
                    std::transform(word.begin(), word.end(), word.begin(), ::tolower);  // Convert word to lowercase.
                    vocabulary.insert(word);                                            // Insert the word into the set.
                    word = "";
                }
            }
            else if (ValidCharacter(line[i]))
            {
                word += line[i];    // Append the character to the current word being built.
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

void Preprocessor::InsertVocabularyIntoFile(std::ofstream& preprocessed_file, const std::set<std::string>& vocabulary)
{
    for (auto it = vocabulary.begin(); it != vocabulary.end(); )
    {
        preprocessed_file << *it;

        ++it;
        if (it != vocabulary.end())
        {
            preprocessed_file << ',';
        }
        else
        {
            preprocessed_file << ",classlabel";
        }
    }
    preprocessed_file << std::endl;
}

std::vector<FeatureVector> Preprocessor::GetFeatureVectors(std::ifstream& data, const std::set<std::string>& vocabulary)
{
    std::vector<FeatureVector> vector;

    std::string newline;
    int class_label;
    std::string word = "";
    std::string line = "";

    while (!data.eof())                    // For each line.
    {
        std::getline(data, line, '\t');    // Grab line up to tab character.
        data >> class_label;               // Grab the classlabel.
        std::getline(data, newline);       // Grab the newline character.

        if (data.eof())
        {
            break;
        }

        FeatureVector feature_vector(vocabulary);
        feature_vector.SetClassLabel(class_label);
        for (int i = 0; i < line.length(); i++)                                         // For each character in the line.
        {
            if (IsSpace(line[i]) || WordsSeparatedByPunctuation(line, i))
            {
                if (!word.empty())
                {
                    std::transform(word.begin(), word.end(), word.begin(), ::tolower);  // Convert word to lowercase.
                    feature_vector.SetExists(word);                                     // Set the word's existence in the feature vector.
                    word = "";
                }
            }
            else if (ValidCharacter(line[i]))
            {
                word += line[i];            // Append the character to the current word being built.
            }
        }
        vector.push_back(feature_vector);   // Add feature vector to the list of the entire file's feature vectors.
    }
    return vector;
}

void Preprocessor::InsertFeatureVectorsIntoFile(std::ofstream& preprocessed_file, std::vector<FeatureVector>& vectors, const std::set<std::string>& vocabulary)
{
    for (auto it = vectors.begin(); it != vectors.end(); ++it)
    {
        for (auto word = vocabulary.begin(); word != vocabulary.end(); ++word)
        {
            preprocessed_file << it->Exists(*word) << ',';
        }
        preprocessed_file << it->GetClassLabel();
        preprocessed_file << std::endl;
    }
}