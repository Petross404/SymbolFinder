#include "symbolfinder.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    SymbolFinder w;
    w.show();

    return app.exec();
}

