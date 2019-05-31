#ifndef FRAME_H
#define FRAME_H
#include <QVector>
#include <QLine>

struct Frame {
    int id;
    QVector<QLine> shapes;
};

#endif // FRAME_H
