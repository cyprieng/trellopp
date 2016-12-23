#include "trello.h"

#include <liboauthcpp/liboauthcpp.h>
#include <QApplication>

using namespace std;


string const Trello::API_KEY = "74e477acd204a2d7623a0af949651912";
string const Trello::API_SECRET = "5cb5b570bb2bf09dc042bfcb1372bc2f07ff0b0b7c7916fa5c796b9db0c7c724";


string request_token_url = "https://trello.com/1/OAuthGetRequestToken";
string authorize_url = "https://api.twitter.com/oauth/authorize";
string access_token_url = "https://api.twitter.com/oauth/access_token";


string Trello::connect()
{
  OAuth::Consumer consumer(Trello::API_KEY, Trello::API_SECRET);
  OAuth::Client oauth(&consumer);

  // Get request token
  string oAuthQueryString = oauth.getURLQueryString(OAuth::Http::Get, request_token_url);
  string oauthUrl = request_token_url + "?" + oAuthQueryString;
  return oauthUrl;
}

Trello::Trello(string token)
{
  m_token = token;
}

Trello::~Trello()
{

}
