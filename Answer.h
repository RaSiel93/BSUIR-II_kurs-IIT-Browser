#ifndef ANSWER_H
#define ANSWER_H

#include "Node.h"
#include "QString.h"

class Answer
{
public:
    Answer(Node* node, int coincidence, QString link);
    Node* node;
    int coincidence;
    QString link;

    QString getLink();
};

#endif // ANSWER_H
