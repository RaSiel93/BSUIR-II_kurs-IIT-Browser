#ifndef NODEIMAGE_H
#define NODEIMAGE_H

#include "Node.h"
#include "Tag.h"
#include <QStringList>

class NodeImage : public Node
{
public:
    NodeImage(QString id, QString link, QString style, QList<Tag*> tags, QString content);
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

#endif // NODEIMAGE_H
