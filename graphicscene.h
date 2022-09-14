#ifndef GRAPHICSCENE_H
#define GRAPHICSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <vector>
#include <algorithm>

#include "knot.h"


class graphicScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit graphicScene( QObject *parent = nullptr);
    Knot *pressedItem; //итем, на который нажали мышью
    Knot *targetItem; //целевой итем при рисовании линии
    Knot *markerRect; //маркер при рисовании линии

    QGraphicsLineItem *markerLine;

    bool isPressed = false; //нажатие на итем в сцене
    bool isCtrlKeyPress = false; //нажат ли ctrl
    bool isLineDrawing = false; //рисуется ли линия
    QPointF m_shiftMouseCoords; //дельта сдвига мышки

    bool deleteCheckBoxPressed = false;
private:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);//Нажатие мыши
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);//Сдвиг мыши
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);//Отжатие мыши
    void keyPressEvent(QKeyEvent *e);//Нажатие кнопки(не мыши)
    void keyReleaseEvent(QKeyEvent *e);};//отжатие кнопки(не мыши)

#endif // GRAPHICSCENE_H
