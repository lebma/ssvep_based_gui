#include "dictionary.h"
#include <queue>
#include <iostream>
#include <fstream>
#include <QDebug>

Dictionary::Dictionary()
{
    root = new Node();

    std::ifstream infile;
    infile.open("words_alpha.txt");
    if (infile.is_open())
    {
        std::string word;
        while (getline(infile, word))
        {
            //qDebug() << "New line: " << QString::fromStdString(word);
            insert(word);
        }
    }
    else
    {
        qDebug() << "Couldn't open dictionary.txt file.";
    }
    infile.close();


}

Dictionary::~Dictionary()
{
    delete root;
}

int Dictionary::charMap(char c) const
{
    if((c >= 'a') & (c <= 'z'))
        return c - 'a';
    if((c >= 'A') & (c <= 'Z'))
        return c - 'A';

    return -1;
}

char Dictionary::charUnMap(int ind) const
{
    return char('a' + ind);
}

Node* Dictionary::find(std::string word)
{
    if(word == "" || word.find(" ") != std::string::npos)
        return nullptr;

    Node* p = root;
    for(size_t i = 0; i < word.size(); ++i)
    {
        p = p->getChild(charMap(word[i]));

        if(p == nullptr)
            break;
    }

    return p;
}

void Dictionary::insert(std::string word)
{
    if((find(word) != nullptr && find(word)->getText() != "") || word.find(" ") != std::string::npos || word == "")
        return;

    Node* p = root;
    for(size_t i = 0; i < word.size(); ++i)
    {
        int index = charMap(word[i]);
        if(p->getChild(index) == nullptr)
            p->setChild(index, new Node());

        p = p->getChild(index);
    }
    p->setText(word);
}

void Dictionary::predict(QString word)
{
    predictedWords.clear();

    Node* p = find(word.toStdString());

    if(p != nullptr)
    {
        std::queue<Node*> visitedList;
        visitedList.push(p);
        while(predictedWords.size() < 3 && !visitedList.empty())
        {
            p = visitedList.front();
            visitedList.pop();

            if(p->getText() != "")
                predictedWords.push_back(QString::fromStdString(p->getText()));

            for(int i = 0; i < letterCount; ++i)
                if(p->getChild(i) != nullptr)
                    visitedList.push(p->getChild(i));
        }
    }
}

std::vector<QString> Dictionary::getPredictedWords() const
{
    return predictedWords;
}
