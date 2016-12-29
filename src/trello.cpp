#include "trello.h"
#include "utils.h"

#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>

using namespace std;

// API credentials
string const Trello::API_KEY = "74e477acd204a2d7623a0af949651912";
string const Trello::API_SECRET = "5cb5b570bb2bf09dc042bfcb1372bc2f07ff0b0b7c7916fa5c796b9db0c7c724";

// Trello OAuth URLs
string const request_token_url = "https://trello.com/1/OAuthGetRequestToken";
string const authorize_url = "https://trello.com/1/OAuthAuthorizeToken";
string const access_token_url = "https://trello.com/1/OAuthGetAccessToken";


OAuth::Token Trello::connect(){
  OAuth::Consumer consumer(Trello::API_KEY, Trello::API_SECRET);
  OAuth::Client oauth(&consumer);

  // Get request token
  string oauth_query_string = oauth.getURLQueryString(OAuth::Http::Get, request_token_url);
  QString oauth_url = QString::fromStdString(request_token_url + "?" + oauth_query_string);
  QString data = getURLContent(oauth_url);

  OAuth::Token request_token = OAuth::Token::extract(data.toStdString());
  QString get_authorize_url = QString::fromStdString(authorize_url + "?oauth_token=" + request_token.key());
  openUrl(get_authorize_url);

  string verification_code;
  cout << "Verification code: ";
  cin >> verification_code;

  request_token.setPin(verification_code);
  oauth = OAuth::Client(&consumer, &request_token);
  oauth_query_string = oauth.getURLQueryString(OAuth::Http::Get, access_token_url, string(""), true);

  oauth_url = QString::fromStdString(access_token_url + "?" + oauth_query_string);
  data = getURLContent(oauth_url);
  OAuth::KeyValuePairs access_token_resp_data = OAuth::ParseKeyValuePairs(data.toStdString());
  OAuth::Token access_token = OAuth::Token::extract(access_token_resp_data);
  return access_token;
}

Trello::Trello(OAuth::Token& token){
  m_token = &token;
}

Trello::~Trello(){

}
