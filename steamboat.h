#ifndef STEAMBOAT_H
#define STEAMBOAT_H

#include <QMainWindow>
#include <QtWidgets>
#include <animation.h>
#include "frame.h"
#include <QVector>

namespace Ui {
class Steamboat;
}

class RectItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
    RectItem(qreal x1, qreal y1, qreal w, qreal h) :
        QGraphicsRectItem(x1, y1, w, h)
    {}
};

class LineItem : public QObject, public QGraphicsLineItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
    LineItem(qreal x1, qreal y1, qreal x2, qreal y2) :
        QGraphicsLineItem(x1, y1, x2, y2)
    {}
};

class Steamboat : public QMainWindow
{
    Q_OBJECT

public:
    explicit Steamboat(QWidget *parent = 0);
    ~Steamboat();
    void setFrames(QVector<Frame> frames);

private slots:

    void on_curvesList_currentRowChanged(int currentRow);

private:
    void createCurveIcons();
    void curveChanged(int row);
    QListWidgetItem *curveItem(QEasingCurve::Type curve_type,
                               QSize icon_size, QBrush brush, QString meta_enum);

private:
    Ui::Steamboat *ui;
    RectItem *rect;
    QVector<LineItem> *lines;
    QVector<QLine> drawings;
    QVector<Animation> animations;
    Animation *animation;
    QPixmap pix;
    QPainter painter;
    QVector<Frame> frames;
};

#endif // STEAMBOAT_H
