#pragma once
#include "clscellwidget.h"
#include <QWidget>
#include <QLayout>
#include <QVector>

class clsWorldWidget : public QWidget
{
  Q_OBJECT

private:

  QVector< clsCellWidget* > *ptrCells;

  int
  width,
  height;

  QGridLayout *ptrLayout;

public:

  clsWorldWidget(
      int width = 9,
      int height = 9,
      QWidget *parent = NULL);
  virtual ~clsWorldWidget() {}

  clsCellWidget *getCell(int x, int y);
  int getWidth() {return width;}
  int getHeight() {return height;}
  void setSize(int width, int height);

  void updateWidget();


private slots:

  void slotEmitSignalPopulationChanged();

public slots:

  void slotStep();
  void slotClearWorld();
  void slotFillRandomly();

signals:

  void signalPopulationChanged(QString population);
};
