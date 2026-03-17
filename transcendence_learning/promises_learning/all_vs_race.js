const recordVideoOne = new Promise((resolve, reject) => {
	resolve('Video 1 Recorded')
})
const recordVideoTwo = new Promise((resolve, reject) => {
	resolve('Video 2 Recorded')
})
const recordVideoThree = new Promise((resolve, reject) => {
	resolve('Video 3 Recorded')
})

Promise.all([
	recordVideoOne,
	recordVideoTwo,
	recordVideoThree
]).then((messages) => {
	console.log(messages)
})

//promise.all waits for all of them at the same time
//promise.race returns as soon as one of them complete