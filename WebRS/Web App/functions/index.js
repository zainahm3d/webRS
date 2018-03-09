const functions = require('firebase-functions');
var request = require('request');

let waitingMessage = 'Awaiting response'
var responseFlag = true;
exports.carCommandsHandler = functions.database
    .ref('latestCommand/')
    .onUpdate(event => {
        const commandData = event.data.val().fromWeb;

        if (responseFlag) {
            request
                .post('REMOVED').form({ 'data': commandData })
                .on('response', function(response) {
                    console.log('Status: ' + response.statusCode)
                })
                .on('error', function(err) {
                    console.log(err)
                })
            console.log('----------' + commandData + '----------')
            responseFlag = false
            return event.data.ref.set(waitingMessage)
        } else {
            responseFlag = true
            return commandData
        }
    })

exports.deleteCarResponse = functions.database
    .ref('carCommanded/')
    .onWrite(event => {
        const commandData = event.data.val()
        if (commandData === 'Sending...') {
            return
        } else {
            return event.data.ref.set('Success')
        }
    })