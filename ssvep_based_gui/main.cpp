#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  MainWindow window;
  window.resize(QSize(500, 200));
  window.show();

  return app.exec();
}
