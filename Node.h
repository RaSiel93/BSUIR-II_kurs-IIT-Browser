#ifndef NODE_H
#define NODE_H

#include <QString>
#include <QList>
#include "Tag.h";

class Node
{
public:
    Node(){};
    virtual QString getNode() = 0;
    virtual QString getType() = 0;
    virtual QList<Tag*> getTags() = 0;
};

#endif // NODE_H
