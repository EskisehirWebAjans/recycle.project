import Request from "@/shared/api/Request"

export default {
    namespaced: true,
    state: {
        loading: false
    },
    mutations: {
        SET_LOADING: (state, loading) => {
            state.loading = loading
        },
    },
    actions: {
        getStatByType: async ({ commit }, type) => {
            commit('SET_LOADING', true)
            return Request.post('getStatByType.php', type)
                .then((response) => {
                    console.log(response)
                    commit('SET_LOADING', false)
                    if(response.status) {
                        return response.total
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
        topList: async ({ commit }) => {
            commit('SET_LOADING', true)
            return Request.get('topList.php')
                .then((response) => {
                    console.log(response)
                    commit('SET_LOADING', false)
                    if(response.status) {
                        return response.students
                    } else {
                        throw new Error(response.info)
                    }
                })
                .catch((error) => {
                    console.log(error)
                    commit('SET_LOADING', false)
                    throw new Error(error.message)
                })
        }
    }
}