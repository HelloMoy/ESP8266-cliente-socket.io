var express = require('express');
var app = express();
var server = require('http').Server(app);
var io = require('socket.io')(server);
var num = 0;

io.on('connection', (socket) =>{
    console.log('Cliente conectado');
    //Recibir Alerta del cliente
    socket.on('alerta', (data) => {
        console.log(data);
    });
});

//Enviar contador al cliente
setInterval( () => { 
    io.emit('saludo', 'Hola'); 
}, 1000);



server.listen(5000, () => {
    console.log('Servidor en puerto 5000');
});