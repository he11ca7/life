#pragma once
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QIcon>

enum enmCellStates
{
  cellDead,
  cellAlive
};

class clsCellWidget : public QCheckBox
{
  Q_OBJECT

private:

  enmCellStates state;

public:

  clsCellWidget(
      enmCellStates state = cellDead,
      QWidget *parent = NULL);
  virtual ~clsCellWidget() {}

  void setState(enmCellStates state);
  enmCellStates getState();

public slots:

  void slotClicked(int check);
  void slotUpdateWidget();
};
