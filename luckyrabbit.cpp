#include "luckyrabbit.h"
#include "ui_luckyrabbit.h"
#include <iostream>

LuckyRabbit::LuckyRabbit(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LuckyRabbit)
{
    ui->setupUi(this);

    ui->drawButton->setIcon(QIcon(QPixmap(":/res/icons/046-pen.png")));
    ui->drawButton->setIconSize(ui->drawButton->size());

    ui->clearButton->setIcon(QIcon(QPixmap(":/res/icons/047-eraser.png")));
    ui->clearButton->setIconSize(ui->clearButton->size());

    ui->selectionButton->setIcon(QIcon(QPixmap(":/res/icons/044-marquee.png")));
    ui->selectionButton->setIconSize(ui->selectionButton->size());

    ui->moveButton->setIcon(QIcon(QPixmap(":/res/icons/033-move.png")));
    ui->moveButton->setIconSize(ui->moveButton->size());
}

LuckyRabbit::~LuckyRabbit()
{
    delete ui;
}

void LuckyRabbit::on_drawButton_clicked()
{
    ui->canvas->setDrawMode(true);
    ui->canvas->setSelectionMode(false);
    ui->canvas->setMoveMode(false);
}

void LuckyRabbit::on_clearButton_clicked()
{
    ui->canvas->clearImage();
}

void LuckyRabbit::on_selectionButton_clicked()
{
    ui->canvas->setSelectionMode(true);
    ui->canvas->setDrawMode(false);
    ui->canvas->setMoveMode(false);
}

void LuckyRabbit::on_moveButton_clicked()
{
    ui->canvas->setMoveMode(true);
    ui->canvas->setDrawMode(false);
    ui->canvas->setSelectionMode(false);
}

void LuckyRabbit::on_timeline_sliderMoved(int position)
{
    ui->frame->setNum(position);
    ui->canvas->setCurrentFrame(position);
}

void LuckyRabbit::on_pushButton_clicked()
{
    ui->canvas->setFrame();
}
