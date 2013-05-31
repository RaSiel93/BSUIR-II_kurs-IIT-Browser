#include "MySite.h"
#include <QFile>
//#include <QApplication>
#include <QString>
#include <QTextStream>
#include <QTextCodec>
#include <QMapIterator>
#include <QList>
#include <QMap>
#include <QRegExp>
#include "Answer.h"

//#define rus(char) QString::fromLocal8Bit(char)

MySite::MySite(QString link)
{
    createPage("pages2/bsuir.ok");
    createPage("pages2/bsuir1-photo.ok");
    createPage("pages2/bsuir2-photo.ok");
    createPage("pages2/bsuir3-photo.ok");
    createPage("pages2/fitu.ok");
    createPage("pages2/fitu-photo.ok");
    createPage("pages2/fkp.ok");
    createPage("pages2/fksis.ok");
    createPage("pages2/fre.ok");

    generationFindArray();
}

QString MySite::getPage(QString link)
{
    MyPage *page = mapPage[link];
    if(page == NULL){
        return NULL;
    }
    return page->generate();
}

void MySite::createPage(QString link)
{
    QFile file(link);
    if( !file.open(QIODevice::ReadOnly) ){
        return;
    }
    QTextStream in(&file);
    //in.setCodec(QTextCodec::codecForName("UTF-8"));

    mapPage.insert(link, new MyPage(link, in.readAll()));
    file.close();
}

void MySite::generationFindArray(){
    QMapIterator <QString, MyPage*> index(mapPage);
    while (index.hasNext()) {
        index.next();
        MyPage* page = index.value();
        QList<FindStruct*> tempArrayFind = page->getFindArray();
        foreach(FindStruct* find, tempArrayFind){
            this->findArray << find;
        }
    }
}

QString MySite::getAnswer(QString quest){
    QString type = identificationQuest(quest);
    QList<Answer*> answer = searchAnswer(type, quest);
    if(answer.size() == 0){
        return "<p>NO ANSWER!!!</p>";
    }
    return generateAnswer(answer);
}

QString MySite::generateAnswer(QList<Answer*> answer){

    QString html = "";
    //QStringList stackList;

    //stackList << node->getType();
    int maxCoincidence = 0;
    foreach(Answer* node, answer){
        if( maxCoincidence < node->coincidence ){
            maxCoincidence = node->coincidence;
        }
    }
    QString link = "";
    foreach(Answer* node, answer){
        if(node->coincidence == maxCoincidence){
            html += node->node->getNode() + node->node->getType();
            if(link != node->getLink() && link != ""){
                html += node->getLink();
            }
            link = node->getLink();
        }
    }
    html += link;
    return html;
}

QList<Answer*> MySite::searchAnswer(QString type, QString quest){
    QList<Answer*> answerArray;
    foreach(FindStruct* find, this->findArray){
        if(find->getType()==type){
            foreach(Node* node, find->getNodes()){
                int coincidence = isAnswer(node, quest);
                if(coincidence > 0){
                    answerArray << new Answer(node, coincidence, find->getLink());
                }
            }
        }
    }
    return answerArray;
}
int MySite::isAnswer(Node* node, QString quest){
    int coincidence = 0;
    foreach(Tag* tag, node->getTags()){
        QRegExp regul(tag->getName().mid(0,3));
        if(isContent(regul, quest)){
            coincidence++;
        }
    }
    //if(coincidence < 2) return 0;
    return coincidence;
}

QString MySite::identificationQuest(QString quest){
    QRegExp rHow(QString::fromLocal8Bit("как выглядит"));
    QRegExp rHowMany(QString::fromLocal8Bit("сколько|как много|какое количество"));
    QRegExp rTime(QString::fromLocal8Bit("когда|в каком году|как давно"));
    QRegExp rWhich(QString::fromLocal8Bit("какие|какая"));
    QRegExp rWho(QString::fromLocal8Bit("кто"));
    QRegExp rThat(QString::fromLocal8Bit("что необходимо|что нужно"));
    QRegExp rWhat(QString::fromLocal8Bit("что такое|какое определение у"));
    QRegExp rWhere(QString::fromLocal8Bit("в каком месте|где"));

    if(isContent(rHow, quest)) return "how";
    if(isContent(rHowMany, quest)) return "how_many";
    if(isContent(rTime, quest)) return "time";
    if(isContent(rWhich, quest)) return "which";
    if(isContent(rWho, quest)) return "who";
    if(isContent(rThat, quest)) return "that";
    if(isContent(rWhat, quest)) return "what";
    if(isContent(rWhere, quest)) return "where";
    return "";
}

bool MySite::isContent(QRegExp regul, QString text){
    QString neText = text;
    regul.setMinimal(true);
    if( regul.indexIn(neText) != -1 ){
        return true;
    }
    return false;
}
