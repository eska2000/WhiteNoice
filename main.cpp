#include <QCoreApplication>
#include <QDebug>
#include "audioout.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int tone=0;
    double vol=0;

    if (argc>1) {
        tone = QString(argv[1]).toInt();
    }
    if (argc>2) {
        vol = QString(argv[2]).toDouble();
    }

    AudioOut out(tone,vol);

    return a.exec();
}
