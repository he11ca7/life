#include "clsworldwidget.h"

clsWorldWidget::clsWorldWidget(int width, int height, QWidget *parent) : QWidget(parent)
{
  ptrCells = NULL;
  setSize(width, height);
}

clsCellWidget *clsWorldWidget::getCell(int x, int y)
{
  return ptrCells->at(x * getWidth() + y);
}

void clsWorldWidget::setSize(int width, int height)
{
  this->width = width;
  this->height = height;
  updateWidget();
  slotEmitSignalPopulationChanged();
}

void clsWorldWidget::updateWidget()
{
  // Очистка
  if(ptrCells)
  {
    for(int i = 0; i < ptrCells->size(); i++)
    {
      ptrLayout->removeWidget(ptrCells->at(i));
      delete ptrCells->at(i);
    }
    delete ptrCells;
    delete ptrLayout;
  }

  // Пересоздание
  ptrCells = new QVector<clsCellWidget *>;
  int sizeOfMatrix = getWidth() * getHeight();
  ptrCells->resize(sizeOfMatrix);
  for(int i = 0; i < sizeOfMatrix; i++)
  {
    (*ptrCells)[i] = new clsCellWidget;
    connect(ptrCells->at(i),
            SIGNAL(clicked(bool)),
            this, SLOT(slotEmitSignalPopulationChanged())
            );
  }

  ptrLayout = new QGridLayout;
  ptrLayout->setSizeConstraint(QLayout::SetFixedSize);
  ptrLayout->setSpacing(0);
  setLayout(ptrLayout);

  // Прикрепление
  setUpdatesEnabled(false);
  for(int i = 0; i < getHeight(); i++)
    for(int j = 0; j < getWidth(); j++)
      ptrLayout->addWidget(getCell(i, j), i, j);
  setUpdatesEnabled(true);
}

void clsWorldWidget::slotEmitSignalPopulationChanged()
{
  int populationCounter = 0;
  for(int x = 0; x < height; x++)
    for(int y = 0; y < width; y++)
      if(getCell(x, y)->getState() == cellAlive) ++populationCounter;
  emit signalPopulationChanged(QString::number(populationCounter));
}

void clsWorldWidget::slotStep()
{
  int width = getWidth();
  int height = getHeight();

  // Копируем состояния предыдущего поколения
  enmCellStates states[height][width];
  for(int i = 0; i < height; i++)
    for(int j = 0; j < width; j++)
      states[i][j] = getCell(i, j)->getState();

  for(int x = 0; x < height; x++)
    for(int y = 0; y < width; y++)
    {
      int counter = 0;
      // Считаем количество соседей
      int _x, _y;
      // 1
      if(x == 0) _x = (height - 1); else _x = x - 1;
      if(y == 0) _y = (width - 1); else _y = y - 1;
      if(states[_x][_y] == cellAlive) ++counter;

      // 2
      if(x == 0) _x = (height - 1); else _x = x - 1;
      _y = y;
      if(states[_x][_y] == cellAlive) ++counter;

      // 3
      if(x == 0) _x = (height - 1); else _x = x - 1;
      if(y == (width - 1)) _y = 0; else _y = y + 1;
      if(states[_x][_y] == cellAlive) ++counter;

      // 4
      _x = x;
      if(y == (width - 1)) _y = 0; else _y = y + 1;
      if(states[_x][_y] == cellAlive) ++counter;

      // 5
      if(x == (height - 1)) _x = 0; else _x = x + 1;
      if(y == (width - 1)) _y = 0; else _y = y + 1;
      if(states[_x][_y] == cellAlive) ++counter;

      // 6
      if(x == (height - 1)) _x = 0; else _x = x + 1;
      _y = y;
      if(states[_x][_y] == cellAlive) ++counter;

      // 7
      if(x == (height - 1)) _x = 0; else _x = x + 1;
      if(y == 0) _y = (width - 1); else _y = y - 1;
      if(states[_x][_y] == cellAlive) ++counter;

      // 8
      _x = x;
      if(y == 0) _y = (width - 1); else _y = y - 1;
      if(states[_x][_y] == cellAlive) ++counter;

      if(getCell(x, y)->getState() == cellDead)
      {
        if(counter == 3) getCell(x, y)->setState(cellAlive);
      }
      else
      {
        if((counter < 2) || (counter > 3)) getCell(x, y)->setState(cellDead);
      }
    }

  slotEmitSignalPopulationChanged();
}

void clsWorldWidget::slotClearWorld()
{
  setSize(getWidth(), getHeight());
}

void clsWorldWidget::slotFillRandomly()
{
  for(int i = 0; i < getHeight(); i++)
    for(int j = 0; j < getWidth(); j++)
      if(qrand() % 3 == 0)
        getCell(i, j)->setState(cellAlive);
      else
        getCell(i, j)->setState(cellDead);
  slotEmitSignalPopulationChanged();
}
