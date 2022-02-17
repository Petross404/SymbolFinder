#include "symbolfinder.h"
#include "ui_symbolfinder.h"

SymbolFinder::SymbolFinder(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::SymbolFinder)
{
    m_ui->setupUi(this);
}

SymbolFinder::~SymbolFinder() = default;
