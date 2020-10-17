var net = require('net');
var server = net.createServer();    

server.on('connection', (conn) => {    
    console.log("A");
  var remoteAddress = conn.remoteAddress + ':' + conn.remotePort;  
  console.log('new client connection from %s', remoteAddress);
  conn.on('data', onConnData);  
  conn.once('close', onConnClose);  
  conn.on('error', onConnError);
  function onConnData(d) {  
    console.log('connection data from %s: %j', remoteAddress, d);  
    conn.write(d);  
  }
  for(let i = 0; i < 100; i++) {
      const time = i * 2000;
      setTimeout(() => {
  conn.write("qwe");
      }, time);
  }
  function onConnClose() {  
    console.log('connection from %s closed', remoteAddress);  
  }
  function onConnError(err) {  
    console.log('Connection %s error: %s', remoteAddress, err.message);  
  }  
});

server.listen(9000, function() {    
  console.log('server listening to %j', server.address());  
});
