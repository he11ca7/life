#include "clscellwidget.h"

clsCellWidget::clsCellWidget(enmCellStates state, QWidget *parent) : QCheckBox(parent)
{
  connect(this,
          SIGNAL(stateChanged(int)),
          this,
          SLOT(slotClicked(int))
          );

  setState(state);
}

void clsCellWidget::setState(enmCellStates state)
{
  this->state = state;
  slotUpdateWidget();
}

enmCellStates clsCellWidget::getState()
{
  return state;
}

void clsCellWidget::slotClicked(int check)
{
  switch (check)
  {
  case 0:
  {
    setState(cellDead);
    break;
  }
  case 2:
  {
    setState(cellAlive);
    break;
  }
  default:
    break;
  }
  slotUpdateWidget();
}

void clsCellWidget::slotUpdateWidget()
{
  switch (getState())
  {
  case cellDead:
  {
    setChecked(false);
    break;
  }
  case cellAlive:
  {
    setChecked(true);
    break;
  }
  default:
    break;
  }
}
