/**
 * @author  Timothy O'Rourke
 * @date    6 June 2019
 * @brief   CS 331 Spring 2019 Sentiment Analysis
 */
#ifndef FEATUREVECTOR_H
#define FEATUREVECTOR_H

#include <string>
#include <set>
#include <vector>

struct Word { std::string word; bool exists; };
struct Key { std::string key; };

inline bool operator<(const Word& w, const Key& k) { return w.word < k.key; };
inline bool operator<(const Key& k, const Word& w) { return k.key < w.word; };
inline bool operator<(const Word& w1, const Word& w2) { return w1.word < w2.word; };

class FeatureVector {
private:
        std::set<Word, std::less<>> words;
        int class_label;

public:

    FeatureVector(std::set<std::string> vocabulary);
    ~FeatureVector();

    void AddWord(std::string word, bool exists);
    bool Exists(std::string word);
    void SetExists(std::string word);
};

#endif