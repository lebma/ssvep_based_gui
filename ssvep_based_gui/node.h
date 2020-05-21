#ifndef WORD_H
#define WORD_H

#include <string>
#include <vector>

const int letterCount = 26;

class Node
{
public:
    Node();
    ~Node();
    std::string getText() const;
    void setText(std::string text);
    Node* getChild(int i) const;
    void setChild(int i, Node *node);

private:
    std::string text;
    Node *children[letterCount];
};

#endif // WORD_H
