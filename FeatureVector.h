/**
 * @author  Timothy O'Rourke
 * @date    2 June 2019
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

    void AddWord(std::string word, bool exists);
public:
    FeatureVector(std::set<std::string> vocabulary);
    ~FeatureVector();

    bool Exists(std::string word) const;
    void SetExists(std::string word);
    void SetClassLabel(int l) { class_label = l; }
    int GetClassLabel() const { return class_label; }
};

#endif