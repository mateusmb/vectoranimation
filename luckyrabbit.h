#ifndef LUCKYRABBIT_H
#define LUCKYRABBIT_H

#include <QMainWindow>
#include "canvas.h"
#include "steamboat.h"

namespace Ui {
class LuckyRabbit;
}

class LuckyRabbit : public QMainWindow
{
    Q_OBJECT

public:
    explicit LuckyRabbit(QWidget *parent = nullptr);
    ~LuckyRabbit();

private slots:
    void on_drawButton_clicked();

    void on_clearButton_clicked();

    void on_selectionButton_clicked();

    void on_moveButton_clicked();

    void on_timeline_sliderMoved(int position);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::LuckyRabbit *ui;
    Steamboat *steamboat;
};

#endif // LUCKYRABBIT_H
