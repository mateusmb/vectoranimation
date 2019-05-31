#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include "point.h"
#include <QMouseEvent>
#include <QPoint>
#include <QLine>
#include <QRubberBand>
#include "frame.h"

class Canvas : public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = nullptr);
    bool openImage(const QString &file);
    bool saveImage(const QString &file, const char *format);

    void setDrawMode(bool draw_mode) { this->draw_mode = draw_mode; }
    bool isDrawMode() const { return draw_mode; }

    void setSelectionMode(bool selection_mode) { this->selection_mode = selection_mode; }
    bool isSelectionMode() const { return selection_mode; }

    void setMoveMode(bool move_mode) { this->move_mode = move_mode; }
    bool isMoveMode() const { return move_mode; }

    void  setCurrentFrame(int current_frame);
    Frame getCurrentFrame() const { return current_frame; }

    void setFrame();

protected:
    void paintEvent(QPaintEvent *event)        override;
    void mousePressEvent(QMouseEvent *event)   override;
    void mouseMoveEvent(QMouseEvent *event)    override;
    void mouseReleaseEvent(QMouseEvent *event) override;

signals:

public slots:
    void clearImage();

private:
    QImage         image;
    QPen           pen;
    QPoint         last_point;
    QPoint         end_point;
    QPoint         move_point_last;
    QPoint         move_point_end;
    QPoint         rubber_origin;
    QVector<QLine> lines;
    QVector<QLine> lines_selected;
    QVector<Frame> frames;
    QRubberBand    rubber_band;
    bool           image_modified, mouse_pressed;
    bool           draw_mode, selection_mode, move_mode;
    Frame          current_frame;

    void drawLineBetweenPoints(const QPoint &end_point);
    void moveRubberPoints(const QPoint &end_point);

};

#endif // CANVAS_H
