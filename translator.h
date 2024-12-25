#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QMainWindow>

namespace Ui {
class translator;
}

class translator : public QMainWindow
{
    Q_OBJECT

public:
    explicit translator(QWidget *parent = nullptr);
    ~translator();

private slots:
    void translateText();
private:
    Ui::translator *ui;
};

#endif // TRANSLATOR_H
