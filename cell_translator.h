#ifndef CELL_TRANSLATOR_H
#define CELL_TRANSLATOR_H

#include <QMainWindow>

namespace Ui {
class cell_translator;
}

class cell_translator : public QMainWindow
{
    Q_OBJECT

public:
    explicit cell_translator(QWidget *parent = nullptr);
    ~cell_translator();
private slots:
    void translateText();
private:
    Ui::cell_translator *ui;
};

#endif // CELL_TRANSLATOR_H
