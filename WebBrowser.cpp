#include "WebBrowser.h"
#include "MyPage.h"
#include "MySite.h"
#include <QString>
#include <QApplication>

WebBrowser::WebBrowser(QWidget* wgt) : QWidget(wgt)
{
    site = new MySite("pages2");
    m_ptxt          = new QLineEdit("pages2/bsuir.ok");
    m_pwv           = new QWebView;
    m_pcmdBack      = new QPushButton;
    m_pcmdForward   = new QPushButton;
    m_quest         = new QLineEdit;
    m_find_answer   = new QPushButton("ANSWER");

    m_pcmdBack->setIcon(QIcon(":/button/images/button_back.png"));
    m_pcmdBack->setIconSize(QSize(32,32));
    m_pcmdForward->setIcon(QIcon(":/button/images/button_forward.png"));
    m_pcmdForward->setIconSize(QSize(32,32));

    m_pcmdBack->setEnabled(false);
    m_pcmdForward->setEnabled(false);

    his = history.end()-1;

    QProgressBar* pprb    = new QProgressBar;
    QPushButton* pcmdStop   = new QPushButton;
    QPushButton* pcmdRefresh = new QPushButton;

    pcmdStop->setIcon(QIcon(":/button/images/button_stop.png"));
    pcmdStop->setIconSize(QSize(32,32));
    pcmdRefresh->setIcon(QIcon(":/button/images/button_refresh.png"));
    pcmdRefresh->setIconSize(QSize(32,32));

    m_pwv->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);

    //Подключение слотов к сигналам
    connect(m_ptxt, SIGNAL(returnPressed()), SLOT(slotGo()));
    connect(m_pcmdBack, SIGNAL(clicked()), SLOT(slotBack()));
    connect(m_pcmdForward, SIGNAL(clicked()), SLOT(slotForward()));
    connect(pcmdRefresh, SIGNAL(clicked()), SLOT(slotReload()));
    connect(pcmdStop, SIGNAL(clicked()), m_pwv, SLOT(stop()));
    connect(m_pwv, SIGNAL(loadProgress(int)), pprb, SLOT(setValue(int)));
    connect(m_pwv, SIGNAL(linkClicked(QUrl)), this, SLOT(clickHyperlink(QUrl)));
    connect(m_pwv, SIGNAL(loadFinished(bool)), SLOT(slotFinished(bool)));
    connect(m_find_answer, SIGNAL(clicked()), SLOT(clickFindAnswer()));


    QHBoxLayout* phbx = new QHBoxLayout;
    phbx->addWidget(m_pcmdBack);
    phbx->addWidget(m_pcmdForward);
    phbx->addWidget(pcmdStop);
    phbx->addWidget(pcmdRefresh);
    phbx->addWidget(m_ptxt);
    phbx->addWidget(m_quest);
    phbx->addWidget(m_find_answer);

    QVBoxLayout* playout = new QVBoxLayout;
    playout->addLayout(phbx);
    playout->addWidget(m_pwv);
   // playout->addWidget(pprb);
    setLayout(playout);

    slotGo();
}


//Определение слотов
void WebBrowser::slotGo(){
    //if(!m_ptxt->text().endsWith(".ok")){
        //m_ptxt->setText(m_ptxt->text() + ".ok");
    //}
    for(QLinkedList<QString>::iterator i = history.end()-1; i != his; --i){
        history.pop_back();
    }
    history.push_back(m_ptxt->text());
    his = history.end()-1;
    m_pwv->setHtml(GetPage(m_ptxt->text()));
}

QString WebBrowser::GetPage(QString link){
    if(link.mid(0,7) == "file://"){
        link = link.mid(7,-1);
    }
    return site->getPage(link);
}

/*
QString WebBrowser::NewHtmlToHtml( QString ok ){
    ok = ok.simplified();
    QLinkedList<QString> list;
    QString htm = "<html><body>";
    QString html_body = "";
    for(int i = 0, j = 0, l = 0; i < ok.size(); i++){
        if ( i != 0 && ( ok[i] == '!' || ok[i] == ')')) {
            html_body += ok.mid(j,i-j);
            if(ok[i] == ')'){
                html_body += "</" + list.back() + ">";
                list.pop_back();
            }
            j = i + 1;
        }
        //идентификация тэга
        if (ok[i] == '!') {
            QString attr = " ";
            for(j = 0; ok[j+i] != '('; j++ ){
                //идентификация атрибута
                if(ok[j+i] == '{'){
                    for(l = 0; ok[l+j+i] != '}'; l++ );
                    attr += ok.mid(i+j+1,l-1);
                    j += l;
                    l++;
                }
            }
            QString tag = ok.mid(i+1,j-l-1);
            html_body += "<" + tag + attr + ">";
            list.push_back(tag);
            i += j;
            j = i + 1;
            l = 0;
        }
    }
    htm += html_body + "</body></html>";
    qDebug() << htm;
    return htm;
}*/

void WebBrowser::slotFinished(bool bOk){
    if(!bOk) {
        m_pwv->setHtml("<CENTER>An error has occurred "
                       "while loading the web page</CENTER>"
                       );
    }
    //QWebElementCollection elements = m_pwv->page()->mainFrame()->findAllElements("a");
    //foreach (QWebElement e, elements) {
    //    int x;
    //}
    m_pcmdBack->setEnabled(his != history.begin());
    m_pcmdForward->setEnabled(his+1 != history.end());
}

void WebBrowser::slotBack(){
    m_ptxt->setText(*(--his));
    m_pwv->setHtml(GetPage(m_ptxt->text()));
}
void WebBrowser::slotForward(){
    m_ptxt->setText(*(++his));
    m_pwv->setHtml(GetPage(m_ptxt->text()));
}
void WebBrowser::slotReload(){
    m_ptxt->setText(*his);
    m_pwv->setHtml(GetPage(*his));
}
void WebBrowser::clickHyperlink(const QUrl& link){
    m_ptxt->setText(link.path());

    for(QLinkedList<QString>::iterator i = history.end()-1; i != his; --i){
        history.pop_back();
    }
    //for(QLinkedList<QString>::iterator i = history.begin(); i != history.end(); ++i){
        //if(*i == m_ptxt->text()){
          //      history.erase(i);
            //    i--;
        //}
    //}
    history.push_back(link.path());
    his = history.end()-1;
    m_pwv->setHtml(GetPage(link.path()));
}
void WebBrowser::clickFindAnswer(){
    //if(m_quest->text() != ""){
        m_pwv->setHtml(site->getAnswer(m_quest->text()));
    //}
}
