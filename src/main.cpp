#include <iostream>
#include <QCoreApplication>

#include "trello.h"

using namespace std;

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  Trello::connect();

  return 0;
}
