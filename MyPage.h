#ifndef PAGE_H
#define PAGE_H

#include <QString>
#include <QMap>
#include <QList>
#include "Node.h"
#include "Tag.h";
#include "FindStruct.h";

class MyPage{
public:
    MyPage(QString text, QString link);//, std::list<Tag*> listTag);
    QString generate();
    QList<FindStruct*> getFindArray();
private:
    void getElements(QString elements);//, std::list<Tag*> listTag);
    void getShell(QString shell);
    void getFindStruct(QString text, QString link);
    FindStruct* constructionFind(QString text, QString link);



    QMap<QString, Node*> mapNode;
    QString shell;
    QList<FindStruct*> findArray;
};

#endif // PAGE_H
