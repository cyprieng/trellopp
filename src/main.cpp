#include <QApplication>
#include <QtWebEngineWidgets>

#include "trello.h"

using namespace std;

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  Trello *trello = new Trello();

  return app.exec();
}
