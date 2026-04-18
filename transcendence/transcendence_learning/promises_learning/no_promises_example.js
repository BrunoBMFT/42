const userLeft = false
const userWatchingCatMeme = false

function watchTutorialCallback(callback, errorCallback) {
	if (userLeft) {
		errorCallback({
			name: 'User Left',
			message: ':('
		})
	}
	else if (userWatchingCatMeme) {
		errorCallback({
			name: 'User watching cat meme',
			message: 'WebDevSimplefied < Cat'
		})
	} else {
		callback('sub')
	}
}

watchTutorialCallback((message) => {
	console.log('Success ' + message)
}, (error) => {
	console.log(error.name + ' '  + error.message)
})