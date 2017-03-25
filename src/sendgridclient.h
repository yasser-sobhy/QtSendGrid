#ifndef SENDGRIDCLIENT_H
#define SENDGRIDCLIENT_H

#include "sendgrid/restconsumer.h"
#include "sendgrid/sendgridmessage.h"

#include <QString>

namespace SendGrid {

class SendGridClient : public Gurra::RestConsumer
{

public:
    SendGridClient();
    SendGridClient(QByteArray apiKey, QByteArray host = "https://api.sendgrid.com/v3", QHash<QByteArray, QByteArray> requestHeaders = {}, QString urlPath = {});

    void sendEmail(SendGridMessage &msg);

private:
    QByteArray version = "1.0";
    QString urlPath;
    QString mediaType;
};

}
#endif // SENDGRIDCLIENT_H
