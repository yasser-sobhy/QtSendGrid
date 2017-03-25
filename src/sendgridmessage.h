#ifndef SENDGRIDMESSAGE_H
#define SENDGRIDMESSAGE_H

#include <QHash>
#include <QHash>
#include "sendgrid.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

namespace SendGrid {

class SendGridMessage
{
public:
    SendGridMessage(){}

    void addPersonalization(Personalization personalization)
    {
        if(!personalizations) personalizations = new QList<Personalization>();

        this->personalizations->append(personalization);
    }

    void setFrom(EmailAddress *email)
    {
        if(from) delete from;

        this->from = email;
    }

    void setReplyTo(EmailAddress *email)
    {
        if(replyTo) delete replyTo;

        this->replyTo = email;
    }

    void setSubject(QString subject)
    {
        this->subject = subject;
    }

    void AddContent(QString mimeType, QString text)
    {
        if(!contents) contents = new QList<Content>();

        this->contents->append({ mimeType, text});
    }

    void addContents(QList<Content> contents)
    {
        if(!this->contents) this->contents = new QList<Content>();

        this->contents->append(contents);
    }

    void addAttachment(QString filename, QString content, QString type = nullptr, QString disposition = nullptr, QString content_id = nullptr)
    {
        if(!attachments) attachments = new QList<Attachment>();

        this->attachments->append({ filename, content, type, disposition, content_id});
    }

    void addAttachments(QList<Attachment> attachments)
    {
        if(!this->attachments) this->attachments = new QList<Attachment>();

        this->attachments->append(attachments);
    }

    void setTemplateId(QString templateID)
    {
        this->templateId = templateID;
    }

    void addSection(QString key, QString value)
    {
        if(!sections) sections = new QHash<QString, QString>();

        this->sections->insert(key, value);
    }

    void addSections(QHash<QString, QString> sections)
    {
        if(!this->sections) this->sections = new QHash<QString, QString>();

        this->sections->unite(sections);
    }

    void addHeader(QString key, QString value)
    {
        if(!headers) headers = new QHash<QString, QString>();

        this->headers->insert(key, value);
    }
    void addHeaders(QHash<QString, QString> headers)
    {
        if(!this->headers) this->headers = new QHash<QString, QString>();

        this->headers->unite(headers);
    }
    void addCategory(QString category)
    {
        if(!this->categories) this->categories = new QList<QString>();

        this->categories->append(category);
    }

    void addCategories(QList<QString> categories)
    {
        if(!this->categories) this->categories = new QList<QString>();

        this->categories->append(categories);
    }
    void addCustomArg(QString key, QString value)
    {
        if(!this->customArgs) this->customArgs = new QHash<QString, QString>();

        this->customArgs->insert(key, value);
    }

    void addCustomArgs(QHash<QString, QString> customArgs)
    {
        if(!this->customArgs) this->customArgs = new QHash<QString, QString>();

        this->customArgs->unite(customArgs);
    }

    void setSendAt(qint64 sendAt)
    {
        this->sendAt = sendAt;
    }

    void setBatchId(QString batchId)
    {
        this->batchId = batchId;
    }
    void setAsm(int groupID, QList<int> groupsToDisplay)
    {
        if(this->_asm) delete this->_asm;

        this->_asm = new ASM {groupID, groupsToDisplay};
    }

    void setIpPoolName(QString ipPoolName)
    {
        this->ipPoolName = ipPoolName;
    }

    void setBccSetting(bool enable, QString email)
    {
        if(!this->mailSettings) this->mailSettings = new MailSettings();

        if(this->mailSettings->bccSettings) delete this->mailSettings->bccSettings;

        this->mailSettings->bccSettings = new BCCSettings{
            enable,
            email
        };
    }

    void setBypassQListManagement(bool enable)
    {
        if(!this->mailSettings) this->mailSettings = new MailSettings();

        if(this->mailSettings->bypassListManagement) delete this->mailSettings->bypassListManagement;

        this->mailSettings->bypassListManagement = new BypassListManagement{
            enable
        };
    }

    void setFooterSetting(bool enable, QString html = nullptr, QString text = nullptr)
    {
        if(!this->mailSettings) this->mailSettings = new MailSettings();

        if(this->mailSettings->footerSettings) delete this->mailSettings->footerSettings;

        this->mailSettings->footerSettings = new FooterSettings{
            enable,
            html,
            text
        };
    }

    void setSandBoxMode(bool enable)
    {
        if(!this->mailSettings) this->mailSettings = new MailSettings();
        if(this->mailSettings->sandboxMode) delete this->mailSettings->sandboxMode;

        this->mailSettings->sandboxMode = new SandboxMode{
            enable
        };
    }

    void setSpamCheck(bool enable, int threshold = 1, QString postToUrl = nullptr)
    {
        if(!this->mailSettings) this->mailSettings = new MailSettings();

        if(this->mailSettings->spamCheck) delete this->mailSettings->spamCheck;

        this->mailSettings->spamCheck = new SpamCheck{
            enable,
            threshold,
            postToUrl
        };
    }

    void setClickTracking(bool enable, bool enableText)
    {
        if(!this->trackingSettings) this->trackingSettings = new TrackingSettings();

        if(this->trackingSettings->clickTracking) delete this->trackingSettings->clickTracking;

        this->trackingSettings->clickTracking = new ClickTracking{
            enable,
            enableText
        };
    }

    void setOpenTracking(bool enable, QString substitutionTag)
    {
        if(!this->trackingSettings) this->trackingSettings = new TrackingSettings();

        if(this->trackingSettings->openTracking) delete this->trackingSettings->openTracking;

        this->trackingSettings->openTracking = new OpenTracking{
            enable,
            substitutionTag
        };
    }

    void setSubscriptionTracking(bool enable, QString html = nullptr, QString text = nullptr, QString substitutionTag = nullptr)
    {
        if(!this->trackingSettings) this->trackingSettings = new TrackingSettings();

        if(this->trackingSettings->subscriptionTracking) delete this->trackingSettings->subscriptionTracking;

        this->trackingSettings->subscriptionTracking = new SubscriptionTracking{
            enable,
            substitutionTag,
            html,
            text
        };
    }

    void setGoogleAnalytics(bool enable, QString utmCampaign = nullptr, QString utmContent = nullptr, QString utmMedium = nullptr, QString utmSource = nullptr, QString utmTerm = nullptr)
    {
        if(!this->trackingSettings) this->trackingSettings = new TrackingSettings();

        if(this->trackingSettings->ganalytics) delete this->trackingSettings->ganalytics;

        this->trackingSettings->ganalytics = new Ganalytics{
            enable,
            utmCampaign,
            utmContent,
            utmMedium,
            utmSource,
            utmTerm
        };
    }

    QByteArray toString()
    {
        if (!this->plainTextContent.isEmpty() || !this->htmlContent.isEmpty())
        {
            if (!this->plainTextContent.isEmpty())
                this->contents->append( { SendGridMimeType::Text, this->plainTextContent} );

            if (!this->htmlContent.isEmpty())
                this->contents->append( { SendGridMimeType::Html,this->htmlContent } );

            this->plainTextContent = "";
            this->htmlContent = "";
        }

        if (this->contents)
        {
            // MimeType.Text > MimeType.Html > Everything Else
            for (int i = 0; i < this->contents->count(); i++)
            {
                if ((*this->contents)[i].type == SendGridMimeType::Html)
                {
                    auto tempContent = (*this->contents)[i];
                    this->contents->removeAt(i);
                    this->contents->insert(0, tempContent);
                }

                if ((*this->contents)[i].type == SendGridMimeType::Text)
                {
                    auto tempContent = (*this->contents)[i];
                    this->contents->removeAt(i);
                    this->contents->insert(0, tempContent);
                }
            }
        }

        QJsonDocument doc;
        QJsonObject obj;

        if(from) obj.insert("from", from->toJson());
        if(!subject.isEmpty()) obj.insert("subject", subject);
        if(personalizations) obj.insert("personalizations", listToJson2(*personalizations));
        if(contents) obj.insert("content", listToJson2(*contents));
        if(attachments) obj.insert("attachments", listToJson2(*attachments));
        if(!templateId.isEmpty()) obj.insert("template_id", templateId);

        if(headers) obj.insert("headers", hashToJson(*headers));
        if(sections) obj.insert("sections", hashToJson(*sections));
        if(categories) obj.insert("categories", listToJson(*categories));
        if(customArgs) obj.insert("custom_args", hashToJson(*customArgs));
        if(sendAt > 0) obj.insert("send_at", sendAt);
        if(_asm) obj.insert("asm", _asm->toJson());
        if(!batchId.isEmpty()) obj.insert("batch_id", batchId);
        if(!ipPoolName.isEmpty()) obj.insert("ip_pool_name", ipPoolName);
        if(mailSettings) obj.insert("mail_settings", mailSettings->toJson());
        if(trackingSettings) obj.insert("tracking_settings", trackingSettings->toJson());
        if(replyTo) obj.insert("reply_to", replyTo->toJson());

        doc.setObject(obj);
        return doc.toJson();
    }

private:
    EmailAddress *from = nullptr;
    QString subject;
    QList<Personalization> *personalizations = nullptr;
    QList<Content> *contents = nullptr;
    QString plainTextContent;
    QString htmlContent;
    QList<Attachment> *attachments = nullptr;
    QString templateId;
    QHash<QString, QString> *headers = nullptr;
    QHash<QString, QString> *sections = nullptr;
    QList<QString> *categories = nullptr;
    QHash<QString, QString> *customArgs = nullptr;
    qint64 sendAt = 0;
    ASM *_asm = nullptr;
    QString batchId;
    QString ipPoolName;
    MailSettings *mailSettings = nullptr;
    TrackingSettings *trackingSettings = nullptr;
    EmailAddress *replyTo = nullptr;
};

}
#endif // SENDGRIDMESSAGE_H
