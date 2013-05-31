#include "NodeList.h"

NodeList::NodeList(QString id, QString link, QString style, QList<Tag*> tags, QString content)
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
    if( content != ""){
        this->content = content;
    }
    this->tags = tags;
}

QString NodeList::getNode(){
    if( link != "" ) return "<li" + id + style + "><a" + link + ">" + content;
    return "<li" + id + style + ">" + content;
}

QString NodeList::getType(){
    if( link != "" ) return "</a></li>";
    return "</li>";
}

QList<Tag*> NodeList::getTags(){
    return this->tags;
}
