const userLeft = false
const userWatchingCatMeme = false

function watchTutorialPromise() {
	return new Promise((resolve, reject) => {
		if (userLeft) {
			reject({
				name: 'User Left',
				message: ':('
			})
		}
		else if (userWatchingCatMeme) {
			reject({
				name: 'User watching cat meme',
				message: 'WebDevSimplefied < Cat'
			})
		} else {
			resolve('sub')
		}
	})
}

watchTutorialPromise().then((message) => {
	console.log('Success ' + message)
}).catch((error) => {
	console.log(error.name + ' '  + error.message)
})
