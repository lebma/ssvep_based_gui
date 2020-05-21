#include "node.h"

Node::Node()
{
    text = "";
    for(int i = 0; i < letterCount; ++i)
        children[i] = nullptr;
}

Node::~Node()
{
    for(int i = 0; i < letterCount; ++i)
        if(children[i] != nullptr)
            delete children[i];
}

std::string Node::getText() const
{
    return text;
}

void Node::setText(std::string text)
{
    this->text = text;
}

Node* Node::getChild(int i) const
{
    return children[i];
}

void Node::setChild(int i, Node *node)
{
    children[i] = node;
}
