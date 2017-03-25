# QtSendGrid


##Usage

For more information see https://sendgrid.com/docs/API_Reference/Web_API_v3/index.html

    SendGrid::SendGridClient sgc
    
    SendGrid::SendGridMessage msg;

    msg.setSubject("QtSendGrid Test");
    msg.setFrom( new SendGrid::EmailAddress {"info@eample.com", "Example.com"});
    msg.AddContent(SendGrid::SendGridMimeType::Html, ...);
    msg.AddContent(SendGrid::SendGridMimeType::Text, ...);

    SendGrid::Personalization p;

    p.to.append( SendGrid::EmailAddress{r});
    p.cc.append({"saooom8@gmail.com"});

    msg.addPersonalization(p);
    
    sgc.sendEmail(msg);
