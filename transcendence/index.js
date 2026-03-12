const express = require('express');

const app = express();

app.get('/api/w', (req, res) => {
	res.send("ahahaha");
});

app.listen(3000, () => {
	console.log("listening on 3000");
})