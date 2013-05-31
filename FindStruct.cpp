#include "FindStruct.h"

FindStruct::FindStruct(QString type, QString link, QList<Node*> nodes)
{
    this->type = type;
    this->link = link;
    this->nodes = nodes;
}

QString FindStruct::getType(){
    return this->type;
}

QString FindStruct::getLink(){
    return this->link;
}

QList<Node*> FindStruct::getNodes(){
    return this->nodes;
}
