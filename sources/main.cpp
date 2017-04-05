#include "mainwindow.h"
#include <QApplication>
#include <QStyle>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QApplication::setStyle(QStyleFactory::create("fusion"));

  Q_INIT_RESOURCE(res);

  (new MainWindow)->show();

  return a.exec();
}
