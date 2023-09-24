
import fs from "fs";
import FormData from "form-data";
import fetch from "node-fetch";

const sendEmail = async () => {
    try {
        const form = new FormData();
        form.append('subject', 'Testing');
        form.append('toRecipients', 'ishita.jain2@bajajfinserv.in');
        form.append('attachments', fs.createReadStream('./index.html'), {
            filename: 'file',
        });
        const resp = await fetch('https://bfhldevapigw.healthrx.co.in/tech-digital-cockpit-be/sendMail/send-email', {
            method: 'POST',
            body: form,
            redirect: 'follow',
        });
        const result = await resp.text();
        console.log('resp', resp);
        console.log(result);
    } catch (err) {
        console.log('error', err);
    }
}

sendEmail();