const addon = require('./build/Release/addon');
var http = require('http');

let asyncResult = {};

addon.startAsyncTask((err, result) => {
    if (err) {
        console.error("❌ Помилка:", err);
    } else {
        asyncResult = result;
    }
});

http.createServer((req, res) => {
    res.writeHead(200, { "Content-Type": "application/json" });
    res.write(JSON.stringify(asyncResult));
    res.end();
}).listen(8080);

