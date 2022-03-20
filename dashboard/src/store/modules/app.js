export default {
    namespaced: true,
    state: {
        title: '',
        loading: false
    },
    mutations: {
        SET_TITLE(state, title) {
            state.title = title
        }
    },
    actions: {
        setTitle({ commit }, title) {
            commit('SET_TITLE', title)
        }
    }
}