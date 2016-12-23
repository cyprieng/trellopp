#ifndef DEF_TRELLO
#define DEF_TRELLO

#include <iostream>
#include <string>

class Trello
{
 public:
  static const std::string API_KEY;
  static const std::string API_SECRET;
  static std::string connect();

  Trello(std::string token);
  ~Trello();

 private:
  std::string m_token;
};

#endif
