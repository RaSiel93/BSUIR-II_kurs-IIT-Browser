#include "MyPage.h";
#include "NodeHeader.h";
#include "NodeLink.h";
#include "NodeImage.h";
#include "NodeText.h";
#include "NodeList.h";
#include "Tag.h";
#include "FindStruct.h";
#include <QString>
#include <QRegExp>
#include <QStringList>
#include <list>

MyPage::MyPage(QString link, QString text){//, std::list<Tag*> listTag){
    getElements(text);
    getShell(text);
    getFindStruct(text, link);
}

void MyPage::getElements(QString text){//, std::list<Tag*> listTag){
    QRegExp rNode("<\\[.*\\]>");
    QRegExp rId("id=\".*\"&");
    QRegExp rType("type=\".*\"&");
    QRegExp rLink("link=\".*\"&");
    QRegExp rStyle("style=\".*\"&");
    QRegExp rTag("tag=\".*\"&");
    QRegExp rContent("content=\".*\"&");

    rNode.setMinimal(true);
    rId.setMinimal(true);
    rType.setMinimal(true);
    rLink.setMinimal(true);
    rStyle.setMinimal(true);
    rTag.setMinimal(true);
    rContent.setMinimal(true);

    int pos = 0;
    while ((pos = rNode.indexIn(text, pos)) != -1){
        QString node = rNode.cap(0).mid(1,rNode.cap(0).size() - 2);

        rId.indexIn(node, 0);
        rType.indexIn(node, 0);
        rLink.indexIn(node, 0);
        rStyle.indexIn(node, 0);
        rTag.indexIn(node, 0);
        rContent.indexIn(node, 0);

        QString id = rId.cap(0).mid(4,rId.cap(0).size() - 6);
        QString type = rType.cap(0).mid(6,rType.cap(0).size() - 8);
        QString link = rLink.cap(0).mid(6,rLink.cap(0).size() - 8);
        QString style = rStyle.cap(0).mid(7,rStyle.cap(0).size() - 9);
        QString content = rContent.cap(0).mid(9,rContent.cap(0).size() - 11);

        QList<Tag*> tagArray;
        int tagPosition = 0;
        while(tagPosition >= 0){
            tagPosition = rTag.indexIn(node, tagPosition);
            if(tagPosition != -1){
                QString tag = rTag.cap(0).mid(5,rTag.cap(0).size() - 7);
                tagArray << new Tag(tag);
            }
            int lenght = rTag.matchedLength();
            tagPosition += lenght;
        }

        if(type.mid(0, type.size() - 1) == "header"){
            this->mapNode.insert(id, new NodeHeader(id, type.mid(type.size() - 1), link, style, tagArray, content));
        } else if(type == "image"){
            this->mapNode.insert(id, new NodeImage(id, link, style, tagArray, content));
        } else if(type == "text"){
            this->mapNode.insert(id, new NodeText(id, link, style, tagArray, content));
        } else if(type == "list"){
            this->mapNode.insert(id, new NodeList(id, link, style, tagArray, content));
        }

        pos += rNode.matchedLength();
    }
}

void MyPage::getShell(QString text){
    QRegExp rShell("\\%\\[.*\\]\\%");
    rShell.setMinimal(true);
    rShell.indexIn(text, 0);
    this->shell = rShell.cap(0).mid(2, rShell.cap(0).size() - 4);
}

void MyPage::getFindStruct(QString text, QString link){
    QRegExp rFind("\\?\\[.*\\]\\?");
    rFind.setMinimal(true);

    //QList<FindStruct*> findArray;

    int pos = 0;
    while ((pos = rFind.indexIn(text, pos)) != -1){
        pos = rFind.indexIn(text, pos);
        if(pos != -1){
            QString find = rFind.cap(0).mid(2,rFind.cap(0).size() - 4);
            findArray << constructionFind(find, link);
        }
        /*QList<Tag*> tagArray;
        int position = 0;
        while(position >= 0){
            position = rFind.indexIn(node, position);
            if(position != -1){
                QString tag = rFind.cap(0).mid(5,rFind.cap(0).size() - 7);
                findArray << new FindStruct(type, link, nodes, questions);
            }
            int lenght = rFind.matchedLength();
            position += lenght;
        }

        rFind.indexIn(text, 0);
        this->shell = rShell.cap(0).mid(2, rShell.cap(0).size() - 4);*/

        pos += rFind.matchedLength();
    }
}

FindStruct* MyPage::constructionFind(QString find, QString link){
    QRegExp rType(".*\\=\\!\\>");
    //QRegExp rQuestion("\\=\\?\\>.*\\=\\!\\>");
    QRegExp rAnswer("\\=\\!\\>.*");

    rType.indexIn(find, 0);
    rAnswer.indexIn(find, 0);
    //rQuestion.indexIn(find, 0);
    //rType.setMinimal(true);
    //rQuest.setMinimal(true);
    //rQuestion.setMinimal(true);
    //rAnswer.setMinimal(true);

    QString type = rType.cap(0).mid(0,rType.cap(0).size() - 3);
    QString strAnswer = rAnswer.cap(0).mid(3,rAnswer.cap(0).size() - 0);
    //QString strQuestion = rQuestion.cap(0).mid(3,rQuestion.cap(0).size() - 6);
    //QString n = "";

    //QList<Node*> answers = getNodeFind(strAnswers);

    QRegExp rTag("(.+\\b)");
    rTag.setMinimal(true);

    QList<Node*> answers;
    int tagPosition = 0;
    while(tagPosition >= 0){
        tagPosition = rTag.indexIn(strAnswer, tagPosition);
        if(tagPosition != -1){
            QString tag = rTag.cap(0).mid(0, rTag.cap(0).size() - 0);
            if(tag != "+"){
                answers << this->mapNode[tag];
            }
        }
        int lenght = rTag.matchedLength();
        tagPosition += lenght;
    }

    /*QRegExp rQuest("\".*\"");
    rQuest.setMinimal(true);

    QList<QString> questions;
    int questPosition = 0;
    while(questPosition >= 0){
        questPosition = rQuest.indexIn(strQuestion, questPosition);
        if(questPosition != -1){
            QString quest = rQuest.cap(0).mid(1, rQuest.cap(0).size() - 2);
            questions << quest;
        }
        int lenght = rQuest.matchedLength();
        questPosition += lenght;
    }*/
    return new FindStruct(type, link, answers);
}

QString MyPage::generate(){
    if(this->shell == ""){
        return "";
    }

    QString html = "";
    QStringList stackList;

    QRegExp rShellElement("(.+\\b)|([+|>|(|)])");
    rShellElement.setMinimal(true);
    int pos = 0;
    while ((pos = rShellElement.indexIn(this->shell, pos)) != -1){
        QString nodeName = rShellElement.cap(0);//.mid(1,rNode.cap(0).size() - 2);

        if(nodeName == "+"){
            if(!stackList.isEmpty()){
                html += stackList.back();
                stackList.pop_back();
            }
        } else {
            Node *node = mapNode[nodeName];
            if(node != 0){
                if(!stackList.isEmpty()){
                    if(stackList.back() == "</ul>" && (node->getType() != "</li>"&&node->getType() != "</a></li>")){
                        html += stackList.back();
                        stackList.pop_back();
                    } else if (stackList.back() != "</ul>" && (node->getType() == "</li>" || node->getType() == "</a></li>")){
                        html += "<ul>";
                        stackList << "</ul>";
                    }
                }
                stackList << node->getType();
                html += node->getNode();
            }
        }
        pos += rShellElement.matchedLength();
    }
    while(stackList.size() != 0){
        html += stackList.back();
        stackList.pop_back();
    }
    return html;
}

QList<FindStruct*> MyPage::getFindArray(){
    return this->findArray;
}
