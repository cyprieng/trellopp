#include "trello.h"
#include "utils.h"

#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QtWebEngineWidgets>

using namespace std;

// API credentials
string const Trello::API_KEY = "74e477acd204a2d7623a0af949651912";
string const Trello::API_SECRET = "5cb5b570bb2bf09dc042bfcb1372bc2f07ff0b0b7c7916fa5c796b9db0c7c724";

// Trello OAuth URLs
string const request_token_url = "https://trello.com/1/OAuthGetRequestToken";
string const authorize_url = "https://trello.com/1/OAuthAuthorizeToken";
string const access_token_url = "https://trello.com/1/OAuthGetAccessToken";


Trello::Trello() : QObject(){
  OAuth::Consumer consumer(Trello::API_KEY, Trello::API_SECRET);
  OAuth::Client oauth(&consumer);

  // Get request token
  string oauth_query_string = oauth.getURLQueryString(OAuth::Http::Get, request_token_url);
  QString oauth_url = QString::fromStdString(request_token_url + "?" + oauth_query_string);
  QString data = getURLContent(oauth_url);

  m_request_token = new OAuth::Token(OAuth::Token::extract(data.toStdString()));
  QString get_authorize_url = QString::fromStdString(authorize_url + "?oauth_token=" + m_request_token->key());

  // Open URL and retrieve verification code
  m_view = new QWebEngineView();
  m_view->load(get_authorize_url);
  m_view->show();
  connect(m_view, SIGNAL(loadFinished(bool)), this, SLOT(slotTrelloWebView(bool)));
}

void Trello::slotTrelloWebView(bool loaded){
  const QUrl url = m_view->url();
  if(url.url().toStdString().compare("https://trello.com/1/token/approve") == 0){
    m_view->page()->toPlainText([this](const QString &content){
      QStringList splitted_content = content.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);
      QString last_line = splitted_content.at(splitted_content.size() - 1);
      last_line.remove(' ');
      string verification_code = last_line.toStdString();
      m_view->close();
      processVerificationCode(verification_code);
    });
  }
}

void Trello::processVerificationCode(string& verification_code){
  OAuth::Consumer consumer(Trello::API_KEY, Trello::API_SECRET);
  m_request_token->setPin(verification_code);
  OAuth::Client oauth = OAuth::Client(&consumer, m_request_token);
  string oauth_query_string = oauth.getURLQueryString(OAuth::Http::Get, access_token_url, string(""), true);

  QString oauth_url = QString::fromStdString(access_token_url + "?" + oauth_query_string);
  QString data = getURLContent(oauth_url);
  OAuth::KeyValuePairs access_token_resp_data = OAuth::ParseKeyValuePairs(data.toStdString());
  OAuth::Token access_token = OAuth::Token::extract(access_token_resp_data);
  m_token = &access_token;
}

Trello::Trello(OAuth::Token& token){
  m_token = &token;
}

Trello::~Trello(){

}
