#include "utils.h"

#include <QProcess>
#include <iostream>
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QTextCodec>


QString getURLContent(QString& url){
  QUrl qurl(url);

  // Event loop
  QEventLoop event_loop;
  QNetworkAccessManager mgr;
  QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &event_loop, SLOT(quit()));

  // HTTP request
  QNetworkRequest req(qurl);
  QNetworkReply *reply = mgr.get(req);
  event_loop.exec();

  if (reply->error() == QNetworkReply::NoError){
    //success
    QString data = QTextCodec::codecForMib(106)->toUnicode(reply->readAll());
    delete reply;
    return data;
  }
}
