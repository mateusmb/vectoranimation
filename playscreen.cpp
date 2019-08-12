#include "playscreen.h"
#include <iostream>
#include <math.h>

PlayScreen::PlayScreen(QWidget *parent) : QWidget(parent),
     pen(Qt::black, 10, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

void PlayScreen::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setPen(pen);
    painter.drawLines(this->current_frame.shapes);
}

void PlayScreen::setFrames(QVector<Frame> frames)
{
    int inbetween = frames[1].id - frames[0].id;
    std::cout << "Inbetween qtd: " << inbetween << std::endl;

    this->frames.append(frames[0]);
    this->current_frame = frames[0];

    float t = 0.0;

//    for(int i = 0; i < inbetween-1; i++) {
//        t = i/inbetween;
//        Frame frame;
//        for(auto frame : this->frames) {
//            for(int i = 0; i < frame.shapes.size(); i++) {
//                QPoint point1 = lerp(frame.shapes[i].p1(), frame.shapes[i+1].p1(), t);
//                QPoint point2 = lerp(frame.shapes[i].p2(), frame.shapes[i+1].p2(), t);
//            }
//        }
//    }

}

QPoint PlayScreen::lerp(QPoint point1, QPoint point2, float t)
{
    int x = (1 - t) * point1.x() + t * point2.x();
    int y = (1 - t) * point1.y() + t * point2.y();
    return QPoint(x,y);
}

QPoint PlayScreen::quad(QPoint point1, QPoint point2, float t)
{
    int x = (1 - pow(t,2)) * point1.x() + t * point2.x();
    int y = (1 - pow(t,2)) * point1.y() + t * point2.y();
    return QPoint(x,y);
}

QPoint PlayScreen::cub(QPoint point1, QPoint point2, float t)
{
    int x = (1 - pow(t,3)) * point1.x() + t * point2.x();
    int y = (1 - pow(t,3)) * point1.y() + t * point2.y();
    return QPoint(x,y);
}
