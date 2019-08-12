#include "canvas.h"
#include <iostream>

Canvas::Canvas(QWidget *parent) : QWidget(parent),
  pen(Qt::black, 10, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin),
  image_modified(false),
  mouse_pressed(false),
  draw_mode(true),
  selection_mode(false),
  move_mode(false),
  rubber_band(QRubberBand::Line, this)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setCurrentFrame(1);
}

void Canvas::clearImage()
{
    lines.clear();
    current_frame.shapes.clear();
    update();
}

void Canvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setPen(pen);
    painter.drawLines(this->current_frame.shapes);
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if(this->selection_mode) {
        rubber_origin = event->pos();
        rubber_band.setGeometry(QRect(rubber_origin, QSize()));
        rubber_band.show();
    } else if(move_mode) {
        mouse_pressed = true;
        move_point_last = event->pos();
    } else {
        if(event->button() == Qt::LeftButton) {
            mouse_pressed = true;
            if(draw_mode) {
                last_point = event->pos();
            }
        }
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if(this->selection_mode) {
        rubber_band.setGeometry(QRect(rubber_origin, event->pos()).normalized());
    } else if(move_mode) {
        moveRubberPoints(event->pos());
    } else {
        if(mouse_pressed) {
            if(draw_mode) {
                drawLineBetweenPoints(event->pos());
            }
        }
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if(this->selection_mode) {

//        rubber_band.hide();
        QPalette palette;
        palette.setBrush(QPalette::Highlight, QBrush(Qt::black));
        rubber_band.setPalette(palette);
        QRect contained_rubber(rubber_origin, event->pos());
        for(auto line : lines) {
            if(contained_rubber.normalized().contains(line.p1()) &&
                    contained_rubber.normalized().contains(line.p1())) {
                lines_selected.append(line);
            }
        }
    } else if(move_mode) {
        moveRubberPoints(event->pos());
        mouse_pressed = false;
    } else {
        if(mouse_pressed) {
            if(draw_mode) {
                drawLineBetweenPoints(event->pos());
                mouse_pressed = false;
            }
        }
    }
}

void Canvas::drawLineBetweenPoints(const QPoint &end_point)
{
    lines.append(QLine(last_point, end_point));
    this->current_frame.shapes = lines;
    update();
    image_modified = true;
    last_point = end_point;
}

void Canvas::moveRubberPoints(const QPoint &end_point)
{
    move_point_end = end_point;
    int delta_x = move_point_end.x() - move_point_last.x();
    int delta_y = move_point_end.y() - move_point_last.y();
    rubber_band.move(rubber_band.x()+delta_x,rubber_band.y()+delta_y);
    for(int i = 0; i < lines_selected.size(); i++) {
        lines_selected[i].setP1(QPoint(lines_selected[i].x1()+delta_x,lines_selected[i].y1()+delta_y));
        lines_selected[i].setP2(QPoint(lines_selected[i].x2()+delta_x,lines_selected[i].y2()+delta_y));
    }
    this->current_frame.shapes = lines_selected;
    update();
    move_point_last = move_point_end;
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

void Canvas::setFrame()
{
    Frame frame;
    frame.id = current_frame.id;
    frame.shapes = current_frame.shapes;
    frames.append(frame);
    std::cout << "Frame setted: " << frame.id << std::endl;
    std::cout << "::Lines::" << std::endl;
    for(auto line : frame.shapes) {
        std::cout << line.p1().x() << "," << line.p1().y() << "," << line.p2().x() << "," << line.p2().y() << std::endl;
    }
    std::cout << "::Lines end::" << std::endl;
}

void Canvas::setCurrentFrame(int current_frame)
{
    this->current_frame.id = current_frame;
    bool frame_exists = false;
    for(auto frame : frames) {
        if(frame.id == current_frame) {
            frame_exists = true;
        }
    }

    if(frame_exists) {
        std::cout << "Exist frame" << std::endl;
        this->current_frame = frames[current_frame];
        update();
    }
}
