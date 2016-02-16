#include "glview.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GLView v;
    v.show();

    return a.exec();
}
