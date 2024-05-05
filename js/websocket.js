
const http = require('http'); 
const WebSocketServer = require("websocket").server; 
let connection = null; 
const server = http.createServer((req, res) => {
    console.log("I've received a request");
    res.end('I am connected');
});

const websocket = new WebSocketServer({
    "httpServer":server
});


// if somebody calls the websocket, and go ahead call this fn.
websocket.on("request",()=>{
    console.log('req initiated');

    connection = request.accept(null, request.origin);
    connection.on("onopen",(e)=>{
        console.log('yo what aup');
    })
    connection.on("onclose",(e)=>{
        console.log('yo what aup--->> closed');
    })

    connection.on("onmessage",(message)=>{
        console.log('recieved message',message);

    })

})

server.listen(8080, ()=>{
    console.log("server listening on 8080 bruh");
})
