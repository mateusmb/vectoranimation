#include "steamboat.h"
#include "ui_steamboat.h"
#include <iostream>

Steamboat::Steamboat(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Steamboat),
    pix(QSize(64,64)),
    painter(&pix)
{
    ui->setupUi(this);
    ui->curvesList->setIconSize(QSize(128,128));
    ui->curvesList->setMinimumHeight(300);



    QEasingCurve aux;
//	connect(ui->curvesList, SIGNAL(currentRowChanged(int)), this, SLOT(curveChanged(int)));
    createCurveIcons();
    ui->curvesList->setCurrentRow(int(QEasingCurve::Linear));
}

QEasingCurve createCurve(QEasingCurve curve_type)
{
    QEasingCurve curve(curve_type);
    return curve;
}

// Need refactoring imediately
void Steamboat::createCurveIcons()
{
    // Icon creation
    QLinearGradient gradient(0, 0, 0, 64);
    gradient.setColorAt(0.0, QColor(240,240,240));
    gradient.setColorAt(1.0, QColor(224,224,224));
    QBrush brush(gradient);
    const QMetaObject &mo = QEasingCurve::staticMetaObject;
    QMetaEnum meta_enum = mo.enumerator(mo.indexOfEnumerator("Type"));


    ui->curvesList->addItem(curveItem(QEasingCurve::Linear, QSize(64,64),
                                      brush, "Linear"));
    ui->curvesList->addItem(curveItem(QEasingCurve::InOutQuad, QSize(64,64),
                                      brush, "Quadrática"));
    ui->curvesList->addItem(curveItem(QEasingCurve::InOutCubic, QSize(64,64),
                                      brush, "Cúbica"));
}

/* Create a custom QListWidgetItem for each curve
 * Receives a QPainter, QEasingCurve::Type, QSize,
 * QPixmap, QMetaEnum
 *
*/

QListWidgetItem *Steamboat::curveItem(QEasingCurve::Type curve_type,
                                       QSize icon_size, QBrush brush,
                                       QString meta_enum)
{

    painter.fillRect(QRect(QPoint(0,0), icon_size), brush);
    QEasingCurve curve = createCurve((QEasingCurve::Type) curve_type);
    painter.setPen(QColor(0,0,255,64));
    qreal x_axis = icon_size.height()/1.5;
    qreal y_axis = icon_size.width()/3;
    painter.drawLine(0, x_axis, icon_size.width(), x_axis);
    painter.drawLine(y_axis, 0, y_axis, icon_size.height());
    qreal curve_scale = icon_size.height()/2;
    painter.setPen(Qt::NoPen);

    // start point
    painter.setBrush(Qt::red);
    QPoint start(y_axis, x_axis - curve_scale * curve.valueForProgress(0));
    painter.drawRect(start.x() - 1, start.y() - 1, 3, 3);

    // end point
    painter.setBrush(Qt::blue);
    QPoint end(y_axis + curve_scale, x_axis - curve_scale * curve.valueForProgress(1));
    painter.drawRect(end.x() - 1, end.y() - 1, 3, 3);

    QPainterPath curve_path;
    curve_path.moveTo(start);

    // curve drawing
    for(qreal t = 0; t <= 1.0; t+=1.0/curve_scale) {
        QPoint to;
        to.setX(y_axis + curve_scale * t);
        to.setY(x_axis - curve_scale * curve.valueForProgress(t));
        curve_path.lineTo(to);
    }

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.strokePath(curve_path, QColor(32,32,32));
    painter.setRenderHint(QPainter::Antialiasing, false);
    QListWidgetItem *item = new QListWidgetItem;
    item->setIcon(QIcon(pix));
    item->setText(meta_enum);
    return item;
}

//void MainWindow::curveChanged(int row)
//{
//	QEasingCurve::Type curve_type = (QEasingCurve::Type) row;
//	animation->setEasingCurve(createCurve(curve_type));
//	animation->setCurrentTime(0);
//}



Steamboat::~Steamboat()
{
    delete ui;
}


void Steamboat::on_curvesList_currentRowChanged(int currentRow)
{
    QEasingCurve::Type curve_type = (QEasingCurve::Type) currentRow;
}

void Steamboat::setFrames(QVector<Frame> frames)
{
    ui->widget->setFrames(frames);
}
