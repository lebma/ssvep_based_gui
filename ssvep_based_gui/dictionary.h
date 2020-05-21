#ifndef WORDPREDICTOR_H
#define WORDPREDICTOR_H

#include <QString>
#include <vector>
#include "node.h"

class Dictionary
{
public:
    int NodeCounter;

    Dictionary();
    ~Dictionary();
    void predict(QString word);
    std::vector<QString> getPredictedWords() const;

private:
    Node *root;
    int charMap(char c) const;
    char charUnMap(int ind) const;
    Node* find(std::string word);
    void insert(std::string word);
    std::vector<QString> predictedWords;
};

#endif // WORDPREDICTOR_H
