#ifndef SYMBOLFINDER_H
#define SYMBOLFINDER_H

#include <QMainWindow>
#include <QScopedPointer>

namespace Ui {
class SymbolFinder;
}

class SymbolFinder : public QMainWindow
{
    Q_OBJECT

public:
    explicit SymbolFinder(QWidget *parent = nullptr);
    ~SymbolFinder() override;

private:
    QScopedPointer<Ui::SymbolFinder> m_ui;
};

#endif // SYMBOLFINDER_H
