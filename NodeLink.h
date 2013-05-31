#ifndef NODELINK_H
#define NODELINK_H

#include "Node.h"
class NodeLink : public Node
{
public:
    NodeLink(QString id, QString type, QString style, QString content);
    QString getNode();
    QString getType();
private:
    QString id;
    QString type;
    QString style;
    QString content;
};

#endif // NODELINK_H
