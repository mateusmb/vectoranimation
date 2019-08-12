#ifndef PLAYSCREEN_H
#define PLAYSCREEN_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include "point.h"
#include <QMouseEvent>
#include <QPoint>
#include <QLine>
#include <QRubberBand>
#include "frame.h"

class PlayScreen : public QWidget
{
    Q_OBJECT
public:
    explicit PlayScreen(QWidget *parent = nullptr);
    void setFrames(QVector<Frame> frames);


protected:
    void paintEvent(QPaintEvent *event)        override;

signals:

public slots:
//    void clearImage();

private:
    QPoint lerp(QPoint point1, QPoint point2, float t);
    QPoint quad(QPoint point1, QPoint point2, float t);
    QPoint cub(QPoint point1, QPoint point2, float t);

private:
    QPen           pen;
    QVector<Frame> frames;
    QVector<QLine> drawings;
    Frame          current_frame;
};

#endif // CANVAS_H
