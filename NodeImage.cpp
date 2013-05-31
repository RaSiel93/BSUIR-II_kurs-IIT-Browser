#include "NodeImage.h"

NodeImage::NodeImage(QString id, QString link, QString style, QList<Tag*> tags, QString content)
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
        this->content = " src=\"" + content + "\" ";
    }
    this->tags = tags;
}

QString NodeImage::getNode(){
    if( link != "" ) return "<a"+ link + "><img"+ id + style + content + ">";
    return "<img"+ id + style + content + ">";
}

QString NodeImage::getType(){
    if( link != "" ) return "</img></a>";
    return "</img>";
}

QList<Tag*> NodeImage::getTags(){
    return this->tags;
}
