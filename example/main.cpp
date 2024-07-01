#include <QApplication>

#include "qaestestwgt.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qAesTestWgt *pWgt = new qAesTestWgt;
    pWgt->show();

    return a.exec();
}
