#include "sendgridclient.h"

using namespace SendGrid;

const QString SendGridMimeType::Html = "text/html";
const QString SendGridMimeType::Text = "text/plain";

SendGridClient::SendGridClient()
{

}

SendGridClient::SendGridClient(QByteArray apiKey, QByteArray host, QHash<QByteArray, QByteArray> requestHeaders, QString urlPath)
{
    setHost(host);
    this->urlPath = urlPath;

    QHash<QByteArray, QByteArray> defaultHeaders = {
        {"Authorization", "Bearer " + apiKey},
        {"Content-Type", "application/json"},
        {"User-Agent", "sendgrid/" + this->version + " Qt"},
        {"Accept", "application/json"}
    };

    addHeaders(defaultHeaders);
    addHeaders(requestHeaders);
}

void SendGridClient::sendEmail(SendGridMessage &msg)
{
    connect(this, &RestConsumer::serverError, [](const QByteArray err){
        qDebug() << err;
    });

    connect(this, &RestConsumer::posted, [](const QByteArray data){
        qDebug() << "POSTed" << data;
    });

    connect(this, &RestConsumer::networkError, [](){
        qDebug() << "RestConsumer::networkError";
    });

    post("/mail/send", msg.toString());

}
