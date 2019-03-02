#include "canvas.h"

Canvas::Canvas(QWidget *parent) : QWidget(parent),
  pen(Qt::black, 10, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin),
  image_modified(false),
  mouse_pressed(false),
  draw_mode(true),
  selection_mode(false),
  move_mode(false)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

void Canvas::clearImage()
{
    lines.clear();
    update();
}

void Canvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setPen(pen);
    painter.drawLines(lines);
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        mouse_pressed = true;
        if(draw_mode) {
            last_point = event->pos();
        }
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if(mouse_pressed) {
        if(draw_mode) {
            drawLineBetweenPoints(event->pos());
        }
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if(mouse_pressed) {
        if(draw_mode) {
            drawLineBetweenPoints(event->pos());
            mouse_pressed = false;
        }
    }
}

void Canvas::drawLineBetweenPoints(const QPoint &end_point)
{
    lines.append(QLine(last_point, end_point));
    update();
    image_modified = true;
    last_point = end_point;
}

bool Canvas::openImage(const QString &file)
{
    QImage image_loaded;
    if(!image_loaded.load(file)) {
        return false;
    } else {
        QSize size = image_loaded.size().expandedTo(this->size());
        image = image_loaded;
        image_modified = false;
        update();
        return true;
    }
}
