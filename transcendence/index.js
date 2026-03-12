const express = require('express');

const app = express();

app.get('/api/aaa', (req, res) => {
	res.statusCode = 200;
	res.setHeader('Content-Type', 'text/plain');
	res.end('Hello retard')
	// res.send("ahahaha");
});

app.listen(3000, () => {
	console.log("listening on 3000");
})