#include "SerialWidget.h"
#include <QApplication>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SerialWidget w;
    w.show();

    QString str = "1;1;4093;0;0;4064;152;4093;";
    quint16 value = str.section(';',5,5).toInt();

    qDebug()<<value;
    return a.exec();
}
