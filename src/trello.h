#ifndef DEF_TRELLO
#define DEF_TRELLO

#include <QApplication>
#include <QtWebEngineWidgets>
#include <iostream>
#include <string>
#include <liboauthcpp/liboauthcpp.h>

class Trello : public QObject
{
 Q_OBJECT

 public:
  static const std::string API_KEY;
  static const std::string API_SECRET;

  Trello();
  Trello(OAuth::Token& token);
  ~Trello();

 public slots:
  void slotTrelloWebView(bool loaded);

 private:
  void processVerificationCode(std::string& verification_code);
  OAuth::Token* m_token;
  QWebEngineView* m_view;
  OAuth::Token* m_request_token;
};

#endif
