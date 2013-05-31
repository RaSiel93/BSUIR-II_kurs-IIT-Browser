#ifndef FINDSTRUCT_H
#define FINDSTRUCT_H

#include "Node.h"
#include <QList>

class FindStruct
{
public:
    FindStruct(QString type, QString link, QList<Node*> nodes);
    QString getType();
    QString getLink();
    QList<Node*> getNodes();
private:
    QString type;
    QString link;
    QList<Node*> nodes;
};

#endif // FINDSTRUCT_H
