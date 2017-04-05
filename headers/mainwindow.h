#pragma once
#include <QApplication>
#include <QMainWindow>
#include <QDockWidget>
#include <QGroupBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include "clscellwidget.h"
#include "clsworldwidget.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT

private:

  QTimer *ptrTimer;

  clsWorldWidget *ptrWorldWidget;

  // Настройки мира
  QSpinBox
  *ptrWorldWidthSpinBox,
  *ptrWorldHeightSpinBox;
  QPushButton
  *ptrWorldSizeSetPushButton,
  *ptrResetWorldButton,
  *ptrFillRandomButton;

  // Настройки таймера
  QDoubleSpinBox *ptrTimeoutSpinBox;
  QPushButton
  *ptrTimerStartButton,
  *ptrTimerStopButton,
  *ptrStepButton;

  // Статистика
  QLabel *ptrStatisticsLabel;

  QDockWidget
  *ptrWorldSizeSettingsDockWidget,
  *ptrTimeoutSettingsDockWidget,
  *ptrStatisticsDockWidget;

public:

  MainWindow(QWidget *parent = NULL);
  ~MainWindow();

private slots:

  void slotWorldSizeSetPushButtonClicked();
  void slotTimerStartButtonClicked();
  void slotTimerStopButtonClicked();
};
