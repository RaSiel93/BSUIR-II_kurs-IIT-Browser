#include "NodeLink.h"

NodeLink::NodeLink(QString id, QString type, QString style, QString content)
    : Node(id, type, style, content){
    this->type = "a";
    if( style != "" ){
        this->style = "style=\"" + style + "\"";
    }
    this->content = content;

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
}

QString NodeLink::getNode(){
    return "<" + type + " id=\"" + id + "\" " + style + +"href=\"" + content + "\"" + ">";
}

QString NodeLink::getType(){
    return type;
}
