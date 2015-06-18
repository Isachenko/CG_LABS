#include "mainwindow.h"
#include <QApplication>
#include "letter.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if (!QGLFormat::hasOpenGL()){
        return 1;
    }

    MainWindow letter;
    letter.show();


    return a.exec();
}
