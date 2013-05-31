#include "Answer.h"

Answer::Answer(Node* node, int coincidence, QString link)
{
    this->node = node;
    this->coincidence = coincidence;
    this->link = "href=\"" + link + "\"";
}


QString Answer::getLink(){
    return "<a " + link + ">"+ link +"</a>";
}
