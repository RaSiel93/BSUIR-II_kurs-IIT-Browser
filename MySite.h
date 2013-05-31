#ifndef MYSITE_H
#define MYSITE_H

#include <QString>
#include <map>
#include "MyPage.h"
#include <QList>
#include "Tag.h";
#include <QList>
#include <QMap>
#include "Answer.h"

class MySite
{
public:
    MySite(QString);

    QString getPage(QString link);
    QString getAnswer(QString quest);
private:
    void createPage(QString link);
    QList<Tag> listTag;
    QMap<QString, MyPage*> mapPage;

    void generationFindArray();
    QString identificationQuest(QString quest);
    bool isContent(QRegExp regul, QString text);
    QList<Answer*> searchAnswer(QString type, QString quest);
    QString generateAnswer(QList<Answer*> answer);
    int isAnswer(Node* node, QString quest);



    QList<FindStruct*> findArray;
};

#endif // MYSITE_H
