#include "luckyrabbit.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LuckyRabbit w;
    w.showMaximized();

    return a.exec();
}
