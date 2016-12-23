#include <iostream>
#include "trello.h"

using namespace std;

int main()
{
  string token = Trello::connect();

  cout << token << endl;

  return 0;
}
