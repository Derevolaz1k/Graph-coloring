#include "graphicscene.h"
graphicScene::graphicScene( QObject *parent) : QGraphicsScene(parent)
{
    markerRect = new Knot;
    markerRect->setRect(0,0,10,10);
    markerRect->setData(1,"marker");
    markerRect->hide();
    addItem(markerRect);

    markerLine=new QGraphicsLineItem;
    markerLine->hide();
    addItem(markerLine);
}


void graphicScene::mousePressEvent(QGraphicsSceneMouseEvent * event){

    pressedItem = static_cast<Knot*> (this->itemAt(event->scenePos().x(),
                                                    event->scenePos().y(),
                                                    QTransform()));
    if(!deleteCheckBoxPressed)
    {
    if(pressedItem->data(1)!="Knot"){pressedItem=nullptr;}
    targetItem=nullptr;

    if(pressedItem && !isCtrlKeyPress){

        isPressed=true;
        m_shiftMouseCoords = pressedItem->pos() - event->scenePos();

    }else if(pressedItem && isCtrlKeyPress && !isLineDrawing){
        isPressed=true;
        isLineDrawing=true;
        m_shiftMouseCoords = pressedItem->pos() - event->scenePos();
    }
    }
    else if(deleteCheckBoxPressed&&pressedItem->data(1)=="Knot")
    {
        this->removeItem(pressedItem);
        for(auto it:pressedItem->lines)
        {
            this->removeItem(it);
        }
        while (!pressedItem->lines.empty())
        {
            pressedItem->lines.pop_back();
        }
        while (!pressedItem->knots.empty())
        {
            pressedItem->knots.pop_back();
        }
       // delete pressedItem
    }
    else
    {
        return;
    }
}


void graphicScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){

    if(isLineDrawing && !targetItem){
        isPressed=false;
        isLineDrawing=false;
        markerRect->hide();
        markerLine->hide();
        targetItem = nullptr;

    }else if(isLineDrawing && targetItem!=nullptr && pressedItem!=nullptr){

        isPressed=false;
        isLineDrawing=false;
        markerRect->hide();
        markerLine->hide();

        QGraphicsLineItem *line;
        if((line=pressedItem->lineTo(targetItem))){
            addItem(line);
        }//else delete line;
    }
    Q_UNUSED(event)
}


void graphicScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){

    if(pressedItem && isPressed && !isLineDrawing){

        if(pressedItem->lines.isEmpty()==false){

            pressedItem->adjustLines();
            pressedItem->setPos(event->scenePos() + m_shiftMouseCoords);
            pressedItem->redrawLines();

        }else{
        pressedItem->setPos(event->scenePos() + m_shiftMouseCoords);
        }

    }else if(pressedItem && isPressed && isLineDrawing){
        markerRect->setPos(event->scenePos() + m_shiftMouseCoords);
        markerRect->show();

        QPointF dp1=pressedItem->boundingRect().center();
        QPointF dp2=markerRect->boundingRect().center();

        QPointF p1=pressedItem->scenePos()+dp1;
        QPointF p2=markerRect->scenePos()+dp2;

        if(markerRect->contains(p1)==false){

            markerLine->setLine(QLineF(p1, p2));
            markerLine->show();
        }

        if(markerRect->collidingItems().at(0)->type()==Knot{}.type()
           && markerRect->collidingItems().at(0) != pressedItem
           && isLineDrawing)
        if(markerRect->collidingItems().at(0) &&
           markerRect->collidingItems().at(0) != pressedItem &&
           markerRect->collidingItems().at(0) != markerLine &&
           isLineDrawing)
               {
                 targetItem=static_cast<Knot*>(markerRect->collidingItems().at(0));
               }
    }
}



void graphicScene::keyPressEvent(QKeyEvent *e){
    if(e->key()==Qt::Key_Control){
         isCtrlKeyPress=true;
    }
}

void graphicScene::keyReleaseEvent(QKeyEvent *e){
    if(e->key()==Qt::Key_Control){
         isCtrlKeyPress=false;
    }
}

