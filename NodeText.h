#ifndef NODETEXT_H
#define NODETEXT_H

#include "Node.h"
#include "Tag.h"
#include <Qlist>

class NodeText : public Node
{
public:
    NodeText(QString id, QString link, QString style, QList<Tag*> tags, QString content);
    QString getNode();
    QString getType();
    QList<Tag*> getTags();
private:
    QString id;
    QString link;
    QString style;
    QString content;
    QList<Tag*> tags;
};

#endif // NODETEXT_H
