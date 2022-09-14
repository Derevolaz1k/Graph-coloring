#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

#include <QPushButton>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QGroupBox>

#include <QMessageBox>
#include <QGraphicsView>
#include "graphicscene.h"
#include "knot.h"
#include <QEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    graphicScene *scene;//Сцена
    QGraphicsView *view;//Окно
    QPushButton *AddKnot;//Кнопка добавить узел
    QPushButton *Coloring;//Кнопка раскрасска
    QCheckBox *DeleteKnot;//Кнопка удаление
    QGroupBox *group;//Группа кнопок
    QVBoxLayout *vLayout;//Лэйаут
    bool allColored(QList<Knot*> other);//Проверка на раскраску
    QList<Knot*>knotList;//Список узлов

private:
    int knotSize = 40;//Размер узла
    int rndFactor = 250;//Рандом
    int rando(int low, int high); // рандомайзер в диапазоне от low до high


public slots:
    void actionBtnClickedAddKnot();
    void actionBtnClickedColoring();
    void actionBtnClickedDeleteKnot(bool);

};
#endif // MAINWINDOW_H
