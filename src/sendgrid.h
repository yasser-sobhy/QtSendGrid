#ifndef SENDGRID_H
#define SENDGRID_H

// <copyright">
// Copyright (c) SendGrid. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// </copyright>

#include <QList>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

namespace SendGrid {


template<typename T> QJsonObject hashToJson(QHash<QString, T> &hash){

    QJsonObject obj;

    for(QString key: hash.keys()){
        obj.insert(key, QJsonValue(hash[key]));
    }

    return obj;
}

template<typename T> QJsonArray listToJson(QList<T> &list){

    QJsonArray arr;

    for(T value: list){
        arr.append(QJsonValue(value));
    }

    return arr;
}

template<typename T> QJsonArray listToJson2(QList<T> &list){

    QJsonArray arr;

    for(T value: list){
        arr.append(QJsonValue(value.toJson()));
    }

    return arr;
}

//void removeEmpty(QJsonObject &obj){

//    for(QString key : obj.keys()){

//        if(obj[key].isObject()) {
//            if(obj[key].toObject().isEmpty()) obj.remove(key);
//        }

//        if(obj[key].isArray()) {
//            if(obj[key].toArray().isEmpty()) obj.remove(key);
//        }

//    }
//}

//void removeEmpty(QJsonArray &arr){

//}

/// <summary>
/// Helper for the common SendGrid email mime types.
/// </summary>
struct SendGridMimeType
{
    /// <summary>
    /// The mime type for HTML content.
    /// </summary>
    static const QString Html;

    /// <summary>
    /// The mime type for plain text content.
    /// </summary>
    static const QString Text;
};

/// <summary>
/// An object allowing you to specify how to handle unsubscribes.
/// </summary>
struct ASM
{
    /// <summary>
    /// Gets or sets the unsubscribe group to associate with this email.
    /// </summary>
    int groupId;

    /// <summary>
    /// Gets or sets an array containing the unsubscribe groups that you would like to be displayed on the unsubscribe preferences page.
    /// https://sendgrid.com/docs/User_Guide/Suppressions/recipient_subscription_preferences.html
    /// </summary>
    QList<int> groupsToDisplay;

    QJsonObject toJson(){
        return {
            {"groupId", QJsonValue(groupId)},
            {"groupsToDisplay", QJsonValue(listToJson(groupsToDisplay))}
        };
    }
};

/// <summary>
/// Gets or sets an array of objects in which you can specify any attachments you want to include.
/// </summary>
struct Attachment
{
    /// <summary>
    /// Gets or sets the Base64 encoded content of the attachment.
    /// </summary>
    QString content;

    /// <summary>
    /// Gets or sets the mime type of the content you are attaching. For example, application/pdf or image/jpeg.
    /// </summary>
    QString type;

    /// <summary>
    /// Gets or sets the filename of the attachment.
    /// </summary>
    QString filename;

    /// <summary>
    /// Gets or sets the content-disposition of the attachment specifying how you would like the attachment to be displayed. For example, "inline" results in the attached file being displayed automatically within the message while "attachment" results in the attached file requiring some action to be taken before it is displayed (e.g. opening or downloading the file). Defaults to "attachment". Can be either "attachment" or "inline".
    /// </summary>
    QString disposition;

    /// <summary>
    /// Gets or sets a unique id that you specify for the attachment. This is used when the disposition is set to "inline" and the attachment is an image, allowing the file to be displayed within the body of your email. Ex: <img src="cid:ii_139db99fdb5c3704"></img>
    /// </summary>
    QString contentId;

    QJsonObject toJson(){
        return {
            {"content", QJsonValue(content)},
            {"type", QJsonValue(type)},
            {"filename", QJsonValue(filename)},
            {"disposition", QJsonValue(disposition)},
            {"contentId", QJsonValue(contentId)}
        };
    }

};


/// <summary>
/// Gets or sets the address specified in the mail_settings.bcc object will receive a blind carbon copy (BCC) of the very first personalization defined in the personalizations array.
/// </summary>
struct BCCSettings
{
    /// <summary>
    /// Gets or sets a value indicating whether this setting is enabled.
    /// </summary>
    bool enable;

    /// <summary>
    /// Gets or sets the email address that you would like to receive the BCC.
    /// </summary>
    QString email;

    QJsonObject toJson(){
        return {
            {"enable", QJsonValue(enable)},
            {"email", QJsonValue(email)}
        };
    }
};

/// <summary>
/// Allows you to bypass all unsubscribe groups and suppressions to ensure that the email is delivered to every single recipient. This should only be used in emergencies when it is absolutely necessary that every recipient receives your email. Ex: outage emails, or forgot password emails.
/// </summary>
struct BypassListManagement
{
    /// <summary>
    /// Gets or sets a value indicating whether this setting is enabled.
    /// </summary>
    bool enable;

    QJsonObject toJson(){
        return {
            {"enable", QJsonValue(enable)}
        };
    }
};

/// <summary>
/// Allows you to track whether a recipient clicked a link in your email.
/// </summary>
struct ClickTracking
{
    /// <summary>
    /// Gets or sets a value indicating whether this setting is enabled.
    /// </summary>
    bool enable;

    /// <summary>
    /// Gets or sets if this setting should be included in the text/plain portion of your email.
    /// </summary>
    bool enableText;

    QJsonObject toJson(){
        return {
            {"enable", QJsonValue(enable)},
            {"enableText", QJsonValue(enableText)}
        };
    }
};

/// <summary>
/// Specifies the content of your email. You can include multiple mime types of content, but you must specify at least one. To include more than one mime type, simply add another object to the array containing the type and value parameters. If included, text/plain and text/html must be the first indices of the array in this order. If you choose to include the text/plain or text/html mime types, they must be the first indices of the content array in the order text/plain, text/html.*Content is NOT mandatory if you using a transactional template and have defined the template_id in the Request
/// </summary>
struct Content
{
    /// <summary>
    /// Initializes a new instance of the <see cref="Content"/> class.
    /// </summary>
    Content(){}

    /// <summary>
    /// Initializes a new instance of the <see cref="Content"/> class.
    /// </summary>
    /// <param name="type">The mime type of the content you are including in your email. For example, text/plain or text/html.</param>
    /// <param name="value">The actual content of the specified mime type that you are including in your email.</param>
    Content(QString type, QString value)
    {
        this->type = type;
        this->value = value;
    }

    /// <summary>
    /// Gets or sets the mime type of the content you are including in your email. For example, text/plain or text/html.
    /// </summary>
    QString type;

    /// <summary>
    /// Gets or sets the actual content of the specified mime type that you are including in your email.
    /// </summary>
    QString value;

    QJsonObject toJson(){
        return {
            {"type", QJsonValue(type)},
            {"value", QJsonValue(value)}
        };
    }
};

/// <summary>
/// An email object containing the email address and name of the sender or recipient.
/// </summary>
struct EmailAddress
{
    /// <summary>
    /// Initializes a new instance of the <see cref="EmailAddress"/> class.
    /// </summary>
    EmailAddress()
    {
    }

    /// <summary>
    /// Initializes a new instance of the <see cref="EmailAddress"/> class.
    /// </summary>
    /// <param name="email">The email address of the sender or recipient.</param>
    /// <param name="name">The name of the sender or recipient.</param>
    EmailAddress(QString email, QString name = "")
    {
        this->email = email;
        this->name = name;
    }

    /// <summary>
    /// Gets or sets the name of the sender or recipient.
    /// </summary>
    QString name;

    /// <summary>
    /// Gets or sets the email address of the sender or recipient.
    /// </summary>
    QString email;

    QJsonObject toJson(){
        return {
            {"name", QJsonValue(name)},
            {"email", QJsonValue(email)}
        };
    }

};

/// <summary>
/// The default footer that you would like appended to the bottom of every email.
/// </summary>
struct FooterSettings
{
    /// <summary>
    /// Gets or sets a value indicating whether this setting is enabled.
    /// </summary>
    bool enable;

    /// <summary>
    /// Gets or sets the plain text content of your footer.
    /// </summary>
    QString text;

    /// <summary>
    /// Gets or sets the HTML content of your footer.
    /// </summary>
    QString html;

    QJsonObject toJson(){
        return {
            {"enable", QJsonValue(enable)},
            {"text", QJsonValue(text)},
            {"html", QJsonValue(html)}
        };
    }
};

/// <summary>
/// Allows you to enable tracking provided by Google Analytics.
/// </summary>
struct Ganalytics
{
    /// <summary>
    /// Gets or sets a value indicating whether this setting is enabled.
    /// </summary>
    bool enable;

    /// <summary>
    /// Gets or sets the name of the referrer source. (e.g. Google, SomeDomain.com, or Marketing Email)
    /// </summary>
    QString utmSource;

    /// <summary>
    /// Gets or sets the name of the marketing medium. (e.g. Email)
    /// </summary>
    QString utmMedium;

    /// <summary>
    /// Gets or sets the identification of any paid keywords.
    /// </summary>
    QString utmTerm;

    /// <summary>
    /// Gets or sets the differentiation of your campaign from advertisements.
    /// </summary>
    QString utmContent;

    /// <summary>
    /// Gets or sets the name of the campaign.
    /// </summary>
    QString utmCampaign;

    QJsonObject toJson(){
        return {
            {"enable", QJsonValue(enable)},
            {"utmSource", QJsonValue(utmSource)},
            {"utmMedium", QJsonValue(utmMedium)},
            {"utmTerm", QJsonValue(utmTerm)},
            {"utmContent", QJsonValue(utmContent)},
            {"utmCampaign", QJsonValue(utmCampaign)}
        };
    }
};

/// <summary>
/// Helper class for plain html mime types
/// </summary>
struct HtmlContent : public Content
{
    /// <summary>
    /// Initializes a new instance of the <see cref="HtmlContent"/> class.
    /// </summary>
    /// <param name="value">The actual content of the specified mime type that you are including in your email.</param>
    HtmlContent(QString value)
    {
        this->type = SendGridMimeType::Html;
        this->value = value;
    }
};

/// <summary>
/// This allows you to send a test email to ensure that your request body is valid and formatted correctly. For more information, please see our Classroom.
/// https://sendgrid.com/docs/Classroom/Send/v3_Mail_Send/sandbox_mode.html
/// </summary>
struct SandboxMode
{
    /// <summary>
    /// Gets or sets a value indicating whether this setting is enabled.
    /// </summary>
    bool enable;

    QJsonObject toJson(){
        return {
            {"enable", QJsonValue(enable)}
        };
    }
};

/// <summary>
/// This allows you to test the content of your email for spam.
/// </summary>
struct SpamCheck
{
    /// <summary>
    /// Gets or sets a value indicating whether this setting is enabled.
    /// </summary>
    bool enable;

    /// <summary>
    /// Gets or sets the threshold used to determine if your content qualifies as spam on a scale from 1 to 10, with 10 being most strict, or most likely to be considered as spam.
    /// </summary>
    int threshold;

    /// <summary>
    /// Gets or sets an Inbound Parse URL that you would like a copy of your email along with the spam report to be sent to. The post_to_url parameter must start with http:// or https://.
    /// </summary>
    QString postToUrl;

    QJsonObject toJson(){
        return {
            {"enable", QJsonValue(enable)},
            {"threshold", QJsonValue(threshold)},
            {"postToUrl", QJsonValue(postToUrl)}
        };
    }
};


/// <summary>
/// A collection of different mail settings that you can use to specify how you would like this email to be handled.
/// </summary>
struct MailSettings
{
    /// <summary>
    /// Gets or sets the address specified in the mail_settings.bcc object will receive a blind carbon copy (BCC) of the very first personalization defined in the personalizations array.
    /// </summary>
    BCCSettings *bccSettings = nullptr;

    /// <summary>
    /// Gets or sets the bypass of all unsubscribe groups and suppressions to ensure that the email is delivered to every single recipient. This should only be used in emergencies when it is absolutely necessary that every recipient receives your email. Ex: outage emails, or forgot password emails.
    /// </summary>
    BypassListManagement *bypassListManagement = nullptr;

    /// <summary>
    /// Gets or sets the default footer that you would like appended to the bottom of every email.
    /// </summary>
    FooterSettings *footerSettings = nullptr;

    /// <summary>
    /// Gets or sets the ability to send a test email to ensure that your request body is valid and formatted correctly. For more information, please see our Classroom.
    /// https://sendgrid.com/docs/Classroom/Send/v3_Mail_Send/sandbox_mode.html
    /// </summary>
    SandboxMode *sandboxMode = nullptr;

    /// <summary>
    /// Gets or sets the ability to test the content of your email for spam.
    /// </summary>
    SpamCheck *spamCheck = nullptr;

    QJsonObject toJson(){

        QJsonObject obj;

        if(bccSettings) obj.insert("bccSettings", QJsonValue(bccSettings->toJson()));
        if(bypassListManagement) obj.insert("bypassListManagement", QJsonValue(bypassListManagement->toJson()));
        if(footerSettings) obj.insert("footerSettings", QJsonValue(footerSettings->toJson()));
        if(sandboxMode) obj.insert("sandboxMode", QJsonValue(sandboxMode->toJson()));
        if(spamCheck) obj.insert("spamCheck", QJsonValue(spamCheck->toJson()));

        return obj;
    }
};

/// <summary>
/// Allows you to track whether the email was opened or not, but including a single pixel image in the body of the content. When the pixel is loaded, we can log that the email was opened.
/// </summary>
struct OpenTracking
{
    /// <summary>
    /// Gets or sets a value indicating whether this setting is enabled.
    /// </summary>
    bool enable;

    /// <summary>
    /// Gets or sets the ability to specify a substitution tag that you can insert in the body of your email at a location that you desire. This tag will be replaced by the open tracking pixel.
    /// </summary>
    QString substitutionTag;

    QJsonObject toJson(){
        return {
            {"enable", QJsonValue(enable)},
            {"substitutionTag", QJsonValue(substitutionTag)}
        };
    }
};

/// <summary>
/// An array of messages and their metadata. Each object within personalizations can be thought of as an envelope - it defines who should receive an individual message and how that message should be handled. For more information, please see our documentation on Personalizations. Parameters in personalizations will override the parameters of the same name from the message level.
/// https://sendgrid.com/docs/Classroom/Send/v3_Mail_Send/personalizations.html
/// </summary>
struct Personalization
{
    /// <summary>
    /// Gets or sets an array of recipients. Each email object within this array may contain the recipient’s name, but must always contain the recipient’s email.
    /// </summary>
    QList<EmailAddress> to;

    /// <summary>
    /// Gets or sets an array of recipients who will receive a copy of your email. Each email object within this array may contain the recipient’s name, but must always contain the recipient’s email.
    /// </summary>
    QList<EmailAddress> cc;

    /// <summary>
    /// Gets or sets an array of recipients who will receive a blind carbon copy of your email. Each email object within this array may contain the recipient’s name, but must always contain the recipient’s email.
    /// </summary>
    QList<EmailAddress> bcc;

    /// <summary>
    /// Gets or sets the subject line of your email.
    /// </summary>
    QString subject;

    /// <summary>
    /// Gets or sets the object allowing you to specify specific handling instructions for your email.
    /// </summary>
    QHash<QString, QString> headers;

    /// <summary>
    /// Gets or sets an object following the pattern "substitution_tag":"value to substitute". All are assumed to be strings. These substitutions will apply to the content of your email, in addition to the subject and reply-to parameters.
    /// You may not include more than 100 substitutions per personalization object, and the total collective size of your substitutions may not exceed 10,000 bytes per personalization object.
    /// </summary>
    QHash<QString, QString> substitutions;

    /// <summary>
    /// Gets or sets the values that are specific to this personalization that will be carried along with the email, activity data, and links. Substitutions will not be made on custom arguments. personalizations[x].custom_args will be merged with message level custom_args, overriding any conflicting keys. The combined total size of the resulting custom arguments, after merging, for each personalization may not exceed 10,000 bytes.
    /// </summary>
    QHash<QString, QString> customArgs;

    /// <summary>
    /// Gets or sets a unix timestamp allowing you to specify when you want your email to be sent from SendGrid. This is not necessary if you want the email to be sent at the time of your API request.
    /// </summary>
    qint64 sendAt = 0;

    QJsonObject toJson(){

        QJsonObject obj;

        if(!to.isEmpty()) obj.insert("to", QJsonValue(listToJson2(to)));
        if(!cc.isEmpty()) obj.insert("cc", QJsonValue(listToJson2(cc)));
        if(!bcc.isEmpty()) obj.insert("bcc", QJsonValue(listToJson2(bcc)));
        if(!subject.isEmpty()) obj.insert("subject", QJsonValue(subject));
        if(!substitutions.isEmpty()) obj.insert("substitutions", QJsonValue(hashToJson(substitutions)));
        if(!customArgs.isEmpty()) obj.insert("custom_args", QJsonValue(hashToJson(customArgs)));
        if(sendAt > 0) obj.insert("send_at", QJsonValue(sendAt));

        return obj;
    }
};

/// <summary>
/// Helper class for plain text mime types
/// </summary>
struct PlainTextContent : public Content
{
    /// <summary>
    /// Initializes a new instance of the <see cref="PlainTextContent"/> class.
    /// </summary>
    /// <param name="value">The actual content of the specified mime type that you are including in your email.</param>
    PlainTextContent(QString value)
    {
        this->type = SendGridMimeType::Text;
        this->value = value;
    }
};

/// <summary>
/// Allows you to insert a subscription management link at the bottom of the text and html bodies of your email. If you would like to specify the location of the link within your email, you may use the substitution_tag.
/// </summary>
struct SubscriptionTracking
{
    /// <summary>
    /// Gets or sets a value indicating whether this setting is enabled.
    /// </summary>
    bool enable;

    /// <summary>
    /// Gets or sets the text to be appended to the email, with the subscription tracking link. You may control where the link is by using the tag (percent symbol) (percent symbol)
    /// </summary>
    QString text;

    /// <summary>
    /// Gets or sets the HTML to be appended to the email, with the subscription tracking link. You may control where the link is by using the tag (percent symbol) (percent symbol)
    /// </summary>
    QString html;

    /// <summary>
    /// Gets or sets a tag that will be replaced with the unsubscribe URL. for example: [unsubscribe_url]. If this parameter is used, it will override both the textand html parameters. The URL of the link will be placed at the substitution tag’s location, with no additional formatting.
    /// </summary>
    QString substitutionTag;

    QJsonObject toJson(){
        return {
            {"enable", QJsonValue(enable)},
            {"text", QJsonValue(text)},
            {"html", QJsonValue(html)},
            {"substitutionTag", QJsonValue(substitutionTag)}
        };
    }
};

/// <summary>
/// Settings to determine how you would like to track the metrics of how your recipients interact with your email.
/// </summary>
struct TrackingSettings
{
    /// <summary>
    /// Gets or sets tracking whether a recipient clicked a link in your email.
    /// </summary>
    ClickTracking *clickTracking = nullptr;

    /// <summary>
    /// Gets or sets tracking whether the email was opened or not, but including a single pixel image in the body of the content. When the pixel is loaded, we can log that the email was opened.
    /// </summary>
    OpenTracking *openTracking = nullptr;

    /// <summary>
    /// Gets or sets a subscription management link at the bottom of the text and html bodies of your email. If you would like to specify the location of the link within your email, you may use the substitution_tag.
    /// </summary>
    SubscriptionTracking *subscriptionTracking = nullptr;

    /// <summary>
    /// Gets or sets tracking provided by Google Analytics.
    /// </summary>
    Ganalytics *ganalytics = nullptr;

    QJsonObject toJson(){

        QJsonObject obj;

        if(clickTracking) obj.insert("clickTracking", QJsonValue(clickTracking->toJson()));
        if(openTracking) obj.insert("openTracking", QJsonValue(openTracking->toJson()));
        if(subscriptionTracking) obj.insert("subscriptionTracking", QJsonValue(subscriptionTracking->toJson()));
        if(ganalytics) obj.insert("ganalytics", QJsonValue(ganalytics->toJson()));

        return obj;
    }
};

}

#endif // SENDGRID_H
