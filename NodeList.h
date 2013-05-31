#ifndef NODELIST_H
#define NODELIST_H

#include "Node.h"
#include "Tag.h"
#include <QList>

class NodeList : public Node
{
public:
    NodeList(QString id, QString link, QString style, QList<Tag*> tags, QString content);
    QString getNode();
    QString getType();
    QList<Tag*> getTags();
private:
    QString id;
    QString link;
    QString style;
    QList<Tag*> tags;
    QString content;
};


#endif // NODELIST_H
