#ifndef KNOT_H
#define KNOT_H
#include <QObject>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QKeyEvent>
#include <QDebug>

class Knot : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT

public:
    enum { Type = UserType + 1 };
        int type() const
        {
            // Разрешает использовать qgraphicsitem_cast с этим элементом.
            return Type;
        }

    explicit Knot(QObject *parent = 0);
    QList<QGraphicsLineItem *>  lines; //список входящих линий
    void adjustLines(); //подгонка линий правильным концом к итему
    void redrawLines(); //отрисовать линии итема
    bool checkLines(QLineF testLine); //не рисуем ли линию 2й раз
    QGraphicsLineItem* lineTo(Knot *targetItem); //создание линии между двумя итемами
    bool adjacency(QColor color); // Проверка входящих цветов
    QList<Knot*> knots;//Список входящих объектов
private:

};

#endif // KNOT_H
