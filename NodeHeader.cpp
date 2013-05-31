#include "NodeHeader.h"

NodeHeader::NodeHeader(QString id, QString type, QString link, QString style, QList<Tag*> tags, QString content)
    : Node(){
    this->type = "h" + type;

    if( id != "" ){
        this->id = " id=\"" + id + "\" ";
    }
    if( link != "" ){
        this->link = " href=\"" + link + "\" ";
    }
    if( style != "" ){
        this->style = " style=\"" + style + "\" ";
    }
    this->tags = tags;
    this->content = content;
}

QString NodeHeader::getNode(){
    if( link != "" ) return "<a" + link + "><" + type + id + style + ">" + content;
    return "<" + type + id + style + ">" + content;
}

QString NodeHeader::getType(){
    if( link != "" ) return "</" + type + "></a>";
    return "</" + type + ">";
}

QList<Tag*> NodeHeader::getTags(){
    return this->tags;
}
