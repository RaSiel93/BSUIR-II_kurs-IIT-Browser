#include "NodeText.h"
#include "Tag.h"
NodeText::NodeText(QString id, QString link, QString style, QList<Tag*> tags, QString content)
    : Node(){
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

QString NodeText::getNode(){
    if( link != "" ) return "<p" + id + style + "><a" + link + ">" + content;
    return "<p" + id + style + ">" + content;
}

QString NodeText::getType(){
    if( link != "" ) return "</a></p>";
    return "</p>";
}

QList<Tag*> NodeText::getTags(){
    return this->tags;
}
