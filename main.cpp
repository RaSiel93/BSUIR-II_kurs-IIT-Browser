#include <QtGui>
#include "WebBrowser.h"
#include <QTextCodec>

int main(int argc, char** argv){
    QTextCodec *utfcodec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(utfcodec);
    QTextCodec::setCodecForCStrings(utfcodec);

    QApplication app(argc, argv);
    WebBrowser webBrowser;

    webBrowser.show();

    return app.exec();
}
