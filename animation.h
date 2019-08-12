#ifndef ANIMATION_H
#define ANIMATION_H

#include <QtCore/qpropertyanimation.h>
#include <QtWidgets>

class Animation : public QPropertyAnimation {
public:
    Animation(QObject *obj, const QByteArray &prop) :
        QPropertyAnimation(obj, prop)
    {
        path = QPainterPath();
    }

    void updateCurrentTime(int currentTime) override
    {
        QPropertyAnimation::updateCurrentTime(currentTime);
    }

public:
    QPainterPath path;

};

#endif // ANIMATION_H
