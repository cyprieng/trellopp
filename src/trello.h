#ifndef DEF_TRELLO
#define DEF_TRELLO

#include <iostream>
#include <string>
#include <liboauthcpp/liboauthcpp.h>

class Trello
{
 public:
  static const std::string API_KEY;
  static const std::string API_SECRET;
  static OAuth::Token connect();

  Trello(OAuth::Token& token);
  ~Trello();

 private:
  OAuth::Token* m_token;
};

#endif
