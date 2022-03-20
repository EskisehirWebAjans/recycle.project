import Api from './Api'

export default({
    get(url) {
        return Api.get(url)
            .then(response => response.data)
    },
    post(url, data) {
        return Api.post(url, data)
            .then(response => response.data)
    }
})