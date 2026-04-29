function makeRequest(location) {
	return new Promise((resolve, reject) => {
		console.log('Making request to ' + location)
		if (location === 'Google') {
			resolve('Google says hi')
		} else {
			reject('We can only talk to Google')
		}
	})
}

function processRequest(response) {
	return new Promise((resolve, reject) => {
		console.log('Processing response')
		resolve('Extra info + ' + response)
	})
}

//not async
// makeRequest('Google').then(response => {
// 	console.log('response received')
// 	return processRequest(response)
// }).then(processedResponse => {
// 	console.log(processedResponse)
// }).catch(err => {
// 	console.log(err)
// })

//Synchronous code runs top to bottom
//Asynchronous can create threads to run code in parallel, in case a function takes a while to finish
async function doWork() {
	try {
		const response = await makeRequest('Google')
		console.log('response received')
		const processedResponse = await processRequest(response)
		console.log(processedResponse)
	} catch (err) {
		console.log(err)
	} 
}

doWork()