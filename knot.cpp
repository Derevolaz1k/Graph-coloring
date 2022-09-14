#include "knot.h"
#include "qbrush.h"

Knot::Knot(QObject *parent): QObject(parent), QGraphicsEllipseItem(){
    setData(1,"Knot");
}


void Knot::adjustLines(){
    QPointF dp = this->boundingRect().center();
    QPointF itemPos = this->scenePos()+dp;

    foreach(auto line, lines){

       QPointF lineP1 = line->line().p1();
       QPointF lineP2 = line->line().p2();

       if(lineP2 == itemPos){
           line->setLine(QLineF(lineP2, lineP1));
       }else {
           line->setLine(QLineF(lineP1, lineP2));
       }
    }
}

void Knot::redrawLines(){
    QPointF dp = this->boundingRect().center();
    QPointF itemPos = this->scenePos()+dp;

    foreach(auto line, lines){

       QPointF lineP2 = line->line().p2();
       line->setLine(QLineF(itemPos, lineP2));
    }
}

bool Knot::checkLines(QLineF testLine){

    foreach(auto line, lines){

        QLineF normalLine = line->line();
        QPointF p1 = normalLine.p1();
        QPointF p2 = normalLine.p2();
        QLineF invertedLine = QLineF(p2, p1);

        if(normalLine==testLine || invertedLine==testLine)return false;
    }
    return true;
}

bool Knot::adjacency(QColor color)
{

for(const auto &it:this->knots)
{
  if(it->brush()==color)
  {
      return false;
  }
}
return true;
}


QGraphicsLineItem* Knot::lineTo(Knot *targetItem){

        Knot *pressedItem =this;
        QPointF dp1 = pressedItem->boundingRect().center();
        QPointF dp2 = targetItem->boundingRect().center();
        QPointF p1 = pressedItem->scenePos()+dp1;
        QPointF p2 = targetItem->scenePos()+dp2;
        QLineF pline = QLineF(p1, p2);
        knots.append(targetItem);
        targetItem->knots.append(this);
    if(pressedItem->checkLines(pline)){
        //static int i = 1;
        auto *line = new QGraphicsLineItem;
        line->setFlag(QGraphicsItem::ItemIsMovable, false);
        line->setData(1,"line");
        line->setLine(pline);
        pressedItem->lines.append(line);
        targetItem->lines.append(line);
        //i++;
        return line;
    }else return nullptr;
}

















