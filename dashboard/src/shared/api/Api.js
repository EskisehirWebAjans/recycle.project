import axios from 'axios'

const Api = axios.create({
    headers: {
        'Content-Type': 'application/json',
        'Access-Control-Allow-Origin': '*',
        'Access-Control-Allow-Methods': 'GET, PUT, POST, DELETE, OPTIONS',
      },
      baseURL: 'http://185.179.26.181/~recycleproject/api/',
})

export default Api