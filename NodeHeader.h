#ifndef NODEHEADER_H
#define NODEHEADER_H

#include "Node.h"
#include <QList>
#include "Tag.h"


class NodeHeader : public Node
{
public:
    NodeHeader(QString id, QString type, QString link, QString style, QList<Tag*> tags, QString content);
    QString getNode();
    QString getType();
    QList<Tag*> getTags();
private:
    QString id;
    QString type;
    QString link;
    QString style;
    QList<Tag*> tags;
    QString content;
};

#endif // NODEHEADER_H
