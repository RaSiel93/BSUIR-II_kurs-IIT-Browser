#include "Tag.h"

Tag::Tag(QString name)
{
    this->name = name;
}

QString Tag::getName(){
    return this->name;
}

/*bool Tag::operator==( const Tag& right) {
    return left.name == right.name;
}*/
