import Request from "@/shared/api/Request"

export default {
    namespaced: true,
    state: {
        user: null,
        loading: false,
        token: localStorage.getItem('token') || null,
    },
    mutations: {
        SET_USER: (state, user) => {
            localStorage.setItem('user', JSON.stringify(user))
            state.user = Object.assign({}, user)
        },
        SET_TOKEN: (state, token) => {
            localStorage.setItem('token', token)
            state.token = token
        },
        SET_LOADING: (state, loading) => {
            state.loading = loading
        },
        DESTROY_TOKEN: (state) => {
            state.token = null
            state.user = null
            localStorage.removeItem('token')
            localStorage.removeItem('user')
        }
    },
    actions: {
        doLogin: async({ commit }, user) => {
            commit('SET_LOADING', true)
            return Request.post('doLogin.php', user)
                .then((response) => {
                    console.log(response)
                    commit('SET_LOADING', false)
                    if(response.status) {
                        commit('SET_USER', response.user)
                        commit('SET_TOKEN', response.token)
                    } else {
                        throw new Error(response.info)
                    }
                })
                .catch((error) => {
                    console.log(error)
                    commit('SET_LOADING', false)
                    throw new Error(error.message)
                })
        },
        doLogout: ({ commit }) => {
            return new Promise((resolve, reject) => {
                try {
                    commit('DESTROY_TOKEN')
                } catch(error) {
                    reject({
                        status: true,
                        info: 'Çıkış başarısız!'
                    })
                }
                resolve({
                    status: true,
                    info: 'Çıkış başarılı!'
                })
            })
        }
    }
}