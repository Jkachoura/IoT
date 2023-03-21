const input = document.querySelector('input');
const button = document.querySelector('button');
const messages = document.querySelector('#messages');

const clientId = 'user-' + Math.random().toString(16).substr(2, 4);
const host = 'mqtt://netwerkenbasis.com:1883';
const options = {
    username: 'student',
    password: 'welkom01',
    keepalive: 50,
    clientId: clientId,
    protocolVersion: 4,
    clean: true,
    reconnectPeriod: 2000,
    connectTimeout: 50000,
};
const client = mqtt.connect(host, options);

//Connection lukt
client.on('connect', () => {
    console.log('Connected to the broker');
    client.subscribe('chat/messages');
});

//Connection lukt niet
client.on('error', (err) => {
    console.log('Connection failed error: ', err);
    client.end();
});

//Als er een message is ontvangen op de topic en het is van een andere Client
// Voeg de message toe aan de chatbox
client.on('message', (topic, message, packet) => {
    var otherCliendId = message.toString().substring(0, 9)
    if (otherCliendId != clientId) {
        const li = document.createElement('li');
        li.innerHTML = otherCliendId + ': ' + message.toString().substring(9);
        messages.appendChild(li);
    }
})

//Als er op de enter knop wordt gedrukt wordt de message verstuurd
input.addEventListener('keyup', function(event) {
    if (event.keyCode === 13) {
        event.preventDefault();
        sendMessage();
    }
});

//Als er geklikt wordt op de send button wordt de message verstuurd
button.addEventListener('click', sendMessage);

//Verstuur de message en publish het op de topic
function sendMessage() {
    if (input.value) {
        const li = document.createElement('li');
        li.innerHTML = clientId + ': ' + input.value;
        messages.appendChild(li);
        client.publish('chat/messages', clientId + input.value)
        input.value = '';
    }
}