#ifndef _WebBrowser_h_
#define _WebBrowser_h_
#include <QtGui>
#include <QWidget>
#include <QtWebKit/QtWebKit>

#include "MySite.h"

class QLineEdit;
class QWebView;
class QPushButton;

//=====================================
class WebBrowser : public QWidget{
Q_OBJECT
private:
    MySite* site;

    QLineEdit*      m_ptxt;
    QWebView*       m_pwv;
    QPushButton*    m_pcmdBack;
    QPushButton*    m_pcmdForward;

    QLineEdit*      m_quest;
    QPushButton*    m_find_answer;

public:
    WebBrowser(QWidget* wgt = 0);
    QString GetPage(QString);
    QLinkedList<QString> history;
    QLinkedList<QString>::iterator his;
private slots:
    void slotGo         (    );
    void slotFinished   (bool);
    void slotForward    (    );
    void slotBack       (    );
    void slotReload     (    );
    void clickFindAnswer(    );
    void clickHyperlink (const QUrl&);
};

#endif // WEBBROWSER_H
