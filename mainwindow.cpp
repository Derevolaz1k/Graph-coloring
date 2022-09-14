#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{   
    // настройка UI
   scene = new graphicScene(this);
   view = new QGraphicsView(scene);
    group = new QGroupBox;
    vLayout =new QVBoxLayout;
    AddKnot =new QPushButton("Generate random items");
    Coloring =new QPushButton("Repaint");
    DeleteKnot = new QCheckBox();
    DeleteKnot->setText("Switch to delete mode");
    connect(AddKnot, &QPushButton::clicked,
            this, &MainWindow::actionBtnClickedAddKnot);
    connect(Coloring, &QPushButton::clicked,
            this, &MainWindow::actionBtnClickedColoring);
    connect(DeleteKnot, SIGNAL(toggled(bool)),this, SLOT(actionBtnClickedDeleteKnot(bool)));
    vLayout->addWidget(view);
    vLayout->addWidget(AddKnot);
    vLayout->addWidget(Coloring);
    vLayout->addWidget(DeleteKnot);
    group->setLayout(vLayout);
    setCentralWidget(group);

}

MainWindow::~MainWindow(){}

bool MainWindow::allColored(QList<Knot*> other)
{
    for(const auto &it: other)
    {
        if(it->brush()==Qt::white)
        {
            return false;
        }
    }
    return true;
}

int MainWindow::rando(int low, int high){
          return (rand() % ((high + 1) - low) + low);
 }



void MainWindow::actionBtnClickedAddKnot(){
    Knot *knot = new Knot;
    knot->setRect(0,0,knotSize,knotSize);
    int x = rando(0, rndFactor);
    int y = rando(0, rndFactor);

    int test = 0;
    while(true){
        knot->moveBy(x, y);
        QList<QGraphicsItem *> collidingList = scene->collidingItems(knot);
        if(collidingList.size() == 0 || test>200)break;
        test++;
    }
    knotList.push_back(knot);
    scene->addItem(knot);
    centralWidget()->setFocus();
}

void MainWindow::actionBtnClickedColoring()
{
    for(auto&it:knotList)
    {
        it->setBrush(Qt::white);

    }
std::sort(knotList.begin(),knotList.end(),[&](Knot *other,Knot *other2)
{
    return other->lines.size()>other2->lines.size();
});
bool repaint;
QList<QColor> brushes{Qt::red,Qt::blue,Qt::green,Qt::yellow,Qt::magenta,Qt::cyan,Qt::darkRed,Qt::darkGreen,Qt::darkBlue,Qt::darkCyan,Qt::darkMagenta,Qt::darkYellow};
int counter = 0;
while(!allColored(knotList))
{
    QColor color = brushes[counter];
    for(int i = 0;i<knotList.size();i++)
    {
        if(knotList[i]->brush()!=Qt::white)
        {
            continue;
        }
        repaint = true;
        for(int j = 0;j<knotList.size();j++)
        {
            if(knotList[i]->adjacency(color)==false)
            {
                repaint=false;
                break;
            }
        }
        if(repaint==true)
        {
           knotList[i]->setBrush(color);
        }
    }
    counter++;
}
QMessageBox msgBox;
QString countPaint = "Хроматическое число графа: "+QString::number(counter);
msgBox.setText(countPaint);
msgBox.exec();//Вывод хроматического числа

}
void MainWindow::actionBtnClickedDeleteKnot(bool val)
{
if(val==true)
{
    scene->deleteCheckBoxPressed = true;
    qDebug()<<"TRUE";
}
else if(val==false)
{
    scene->deleteCheckBoxPressed = false;
    qDebug()<<"FALSE";
}
scene->update();
}
