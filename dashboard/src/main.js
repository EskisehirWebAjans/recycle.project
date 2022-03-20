import { createApp, computed } from 'vue'
import { BootstrapIconsPlugin } from 'bootstrap-icons-vue'

import App from './App.vue'
import router from './router'
import store from './store'


import 'bootstrap'
import '@/assets/css/styles.css'

const loggedIn = computed(() => store.state.auth.token !== null)

router.beforeEach((to, from, next) => {
    store.dispatch('app/setTitle', to.meta.title)
    // next()
    if (to.matched.some(record => record.meta.requiresAuth)) {
        console.log(loggedIn.value)
        if(loggedIn.value) {
            next()
        } else {
            next({ 
                name: 'login'
            })
        }
    } else {
        next()
    }
})

createApp(App)
    .use(store)
    .use(router)
    .use(BootstrapIconsPlugin)
    .mount('#app')
