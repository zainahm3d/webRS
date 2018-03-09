//front end code to handle remote start



function fireSet(data) {
    const promise = firebase.database().ref('latestCommand/').update({
        'fromWeb': data
    })
}

function sendingMessageSet() {
    const promise = firebase.database().ref('/').update({
        'carCommanded': 'Sending...'
    })
}

var returnStateRef = firebase.database().ref('latestCommand/response');
returnStateRef.on('value', function(snapshot) {
    console.log(snapshot.val())
    var messageBar = document.getElementById('messageBar');
    messageBar.innerText = snapshot.val()
});

var returnStateRef = firebase.database().ref('carCommanded');
returnStateRef.on('value', function(snapshot) {
    console.log(snapshot.val())
    var messageBar = document.getElementById('messageBar');
    messageBar.innerText = snapshot.val()
});

function commandCar(command) {

    var confirmVar = confirm("Press \"OK\" to " + command)

    if (confirmVar) {
        console.log(command + " Has run")
        fireSet(command);
        sendingMessageSet();
    } else {
        alert("Command aborted")
    }
}