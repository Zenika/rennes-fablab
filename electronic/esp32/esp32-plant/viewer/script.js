function connect() {
  const ws = new WebSocket('ws://localhost:8081');
  ws.onopen = function() {

  };

  ws.onmessage = function(e) {
    if (e.data) {
      try {
        const data = JSON.parse(e.data);
        console.log(data);
        Object.keys(data).forEach((key) => {
          if (document.getElementById(key)) {
            document.getElementById(key).getElementsByClassName('value')[0].innerText = data[key];
          }
        });
      } catch(_) {
        console.log(`Malformed payload : ${e.data}`);
      }
    }
    console.log('Message:', e.data);
  };

  ws.onclose = function(e) {
    console.log('Socket is closed. Reconnect will be attempted in 1 second.', e.reason);
    setTimeout(function() {
      connect();
    }, 1000);
  };

  ws.onerror = function(err) {
    console.error('Socket encountered error: ', err.message, 'Closing socket');
    ws.close();
  };
}

connect();