#include <QApplication>
#include <QTextCodec>
#include <QTime>
#include <QSplashScreen>

#include "myview.h"

int main(int argc, char* argv[]){
    QApplication app(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    myView view;

    QPixmap pix(":/images/background01.png");
    QSplashScreen splash(pix);
    splash.resize(pix.size());
    splash.show();
    app.processEvents();
    splash.finish(&view);
    view.show();
    return app.exec();
}
