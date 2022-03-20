import { createStore } from 'vuex'
import app from './modules/app'
import product from './modules/product'
import student from './modules/student'
import auth from './modules/auth'
import stat from './modules/stat'

export default createStore({
  state: {
  },
  getters: {
  },
  mutations: {
  },
  actions: {
  },
  modules: {
    app,
    product,
    student,
    auth,
    stat
  }
})
