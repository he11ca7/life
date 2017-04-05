#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  ptrWorldWidget = new clsWorldWidget(12, 24);
  setCentralWidget(ptrWorldWidget);

  ptrTimer = new QTimer;
  connect(ptrTimer,
          SIGNAL(timeout()),
          ptrWorldWidget,
          SLOT(slotStep())
          );

  // Настройки размера мира
  ptrWorldWidthSpinBox = new QSpinBox;
  ptrWorldWidthSpinBox->setMinimum(3);
  ptrWorldWidthSpinBox->setMaximum(42);
  ptrWorldWidthSpinBox->setValue(ptrWorldWidget->getWidth());
  ptrWorldHeightSpinBox = new QSpinBox;
  ptrWorldHeightSpinBox->setMinimum(3);
  ptrWorldHeightSpinBox->setMaximum(42);
  ptrWorldHeightSpinBox->setValue(ptrWorldWidget->getHeight());
  ptrWorldSizeSetPushButton = new QPushButton("Применить");
  connect(ptrWorldSizeSetPushButton,
          SIGNAL(clicked()),
          this,
          SLOT(slotWorldSizeSetPushButtonClicked())
          );
  ptrResetWorldButton = new QPushButton("Очистить");
  connect(ptrResetWorldButton,
          SIGNAL(clicked(bool)),
          ptrWorldWidget,
          SLOT(slotClearWorld())
          );
  ptrFillRandomButton = new QPushButton("Случайно");
  connect(ptrFillRandomButton,
          SIGNAL(clicked(bool)),
          ptrWorldWidget,
          SLOT(slotFillRandomly())
          );
  QGridLayout *ptrWorldSizeSettingsLayout = new QGridLayout;
  ptrWorldSizeSettingsLayout->setSizeConstraint(QLayout::SetFixedSize);
  ptrWorldSizeSettingsLayout->addWidget(new QLabel("Ширина"), 0, 0);
  ptrWorldSizeSettingsLayout->addWidget(ptrWorldWidthSpinBox, 0, 1);
  ptrWorldSizeSettingsLayout->addWidget(new QLabel("Высота"), 1, 0);
  ptrWorldSizeSettingsLayout->addWidget(ptrWorldHeightSpinBox, 1, 1);
  ptrWorldSizeSettingsLayout->addWidget(ptrWorldSizeSetPushButton, 2, 0, 1, 2);
  ptrWorldSizeSettingsLayout->addWidget(ptrResetWorldButton, 3, 0, 1, 2);
  ptrWorldSizeSettingsLayout->addWidget(ptrFillRandomButton, 4, 0, 1, 2);
  QGroupBox *ptrWorldSizeSettingsWidget = new QGroupBox;
  ptrWorldSizeSettingsWidget->setLayout(ptrWorldSizeSettingsLayout);
  ptrWorldSizeSettingsDockWidget = new QDockWidget("Игровой мир");
  ptrWorldSizeSettingsDockWidget->setWidget(ptrWorldSizeSettingsWidget);

  // Моделирование
  ptrTimeoutSpinBox = new QDoubleSpinBox;
  ptrTimeoutSpinBox->setMinimum(0.01);
  ptrTimeoutSpinBox->setMaximum(10.0);
  ptrTimeoutSpinBox->setValue(0.2);
  ptrTimerStartButton = new QPushButton("Старт");
  connect(ptrTimerStartButton,
          SIGNAL(clicked()),
          this,
          SLOT(slotTimerStartButtonClicked())
          );
  ptrTimerStopButton = new QPushButton("Стоп");
  ptrTimerStopButton->setEnabled(false);
  connect(ptrTimerStopButton,
          SIGNAL(clicked()),
          this,
          SLOT(slotTimerStopButtonClicked())
          );
  ptrStepButton = new QPushButton("Шаг");
  connect(ptrStepButton,
          SIGNAL(clicked(bool)),
          ptrWorldWidget,
          SLOT(slotStep())
          );
  QGridLayout *ptrTimerSettingsLayout = new QGridLayout;
  ptrTimerSettingsLayout->setSizeConstraint(QLayout::SetFixedSize);
  ptrTimerSettingsLayout->addWidget(new QLabel("Таймаут"), 0, 0);
  ptrTimerSettingsLayout->addWidget(ptrTimeoutSpinBox, 0, 1);
  ptrTimerSettingsLayout->addWidget(ptrTimerStartButton, 1, 0, 1, 2);
  ptrTimerSettingsLayout->addWidget(ptrTimerStopButton, 2, 0, 1, 2);
  ptrTimerSettingsLayout->addWidget(ptrStepButton, 3, 0, 1, 2);
  QGroupBox *ptrTimerSettingsWidget = new QGroupBox;
  ptrTimerSettingsWidget->setLayout(ptrTimerSettingsLayout);
  ptrTimeoutSettingsDockWidget = new QDockWidget("Моделирование");
  ptrTimeoutSettingsDockWidget->setWidget(ptrTimerSettingsWidget);

  // Статистика
  ptrStatisticsLabel = new QLabel("0");
  connect(ptrWorldWidget,
          SIGNAL(signalPopulationChanged(QString)),
          ptrStatisticsLabel,
          SLOT(setText(QString))
          );
  QGridLayout *ptrStatisticsLayout = new QGridLayout;
  ptrStatisticsLayout->addWidget(new QLabel("Население:"), 0, 0);
  ptrStatisticsLayout->addWidget(ptrStatisticsLabel, 0, 1);
  ptrStatisticsLayout->setSizeConstraint(QLayout::SetFixedSize);
  QGroupBox *ptrStatisticsGroupBox = new QGroupBox;
  ptrStatisticsGroupBox->setLayout(ptrStatisticsLayout);
  ptrStatisticsDockWidget = new QDockWidget("Статистика");
  ptrStatisticsDockWidget->setWidget(ptrStatisticsGroupBox);

  addDockWidget(Qt::RightDockWidgetArea, ptrWorldSizeSettingsDockWidget, Qt::Vertical);
  addDockWidget(Qt::LeftDockWidgetArea, ptrTimeoutSettingsDockWidget, Qt::Vertical);
  addDockWidget(Qt::LeftDockWidgetArea, ptrStatisticsDockWidget, Qt::Vertical);
  setWindowTitle("Игра «Жизнь»");
  setWindowIcon(QIcon(":/res/cube.png"));
}

MainWindow::~MainWindow(){}

void MainWindow::slotWorldSizeSetPushButtonClicked()
{
  setUpdatesEnabled(false);
  ptrWorldWidget->setSize(ptrWorldWidthSpinBox->value(), ptrWorldHeightSpinBox->value());
  setUpdatesEnabled(true);
}

void MainWindow::slotTimerStartButtonClicked()
{
  ptrWorldWidget->setEnabled(false);
  ptrWorldSizeSettingsDockWidget->setEnabled(false);
  ptrTimeoutSpinBox->setEnabled(false);
  ptrTimerStartButton->setEnabled(false);
  ptrTimerStopButton->setEnabled(true);

  ptrTimer->start(ptrTimeoutSpinBox->value() * 1000);
}

void MainWindow::slotTimerStopButtonClicked()
{
  ptrWorldWidget->setEnabled(true);
  ptrWorldSizeSettingsDockWidget->setEnabled(true);
  ptrTimeoutSpinBox->setEnabled(true);
  ptrTimerStartButton->setEnabled(true);
  ptrTimerStopButton->setEnabled(false);

  ptrTimer->stop();
}
