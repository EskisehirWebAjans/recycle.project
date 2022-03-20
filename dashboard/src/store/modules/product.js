import Request from '@/shared/api/Request'

export default {
    namespaced: true,
    state: {
        products: [],
        packs: [],
        loading: false
    },
    mutations: {
        SET_PRODUCTS: (state, products) => {
            state.products = []
            products.map(product => {
                state.products.push(product)
            })
        },
        ADD_PRODUCT: (state, product) => {
            state.products.unshift(product)
        },
        UPDATE_PRODUCT: (state, { product, index }) => {
            Object.assign(state.products[index], product)
        },
        REMOVE_PRODUCT: (state, index) => {
            state.products.splice(index, 1)
        },
        SET_LOADING: (state, loading) => {
            state.loading = loading
        },
        SET_PACKS: (state, packs) => {
            state.packs = []
            packs.map(pack => {
                state.packs.push(pack)
            })
        },
        UPDATE_PACK: (state, { pack, index }) => {
            Object.assign(state.packs[index], pack)
        }
    },
    actions: {
        listProducts: async ({ commit }) => {
            commit('SET_LOADING', true)
            return Request.get('listProducts.php')
                .then((response) => {
                    console.log(response)
                    commit('SET_LOADING', false)
                    commit('SET_PRODUCTS', response)
                })
                .catch((error) => {
                    console.log(error)
                    commit('SET_LOADING', false)
                    throw new Error(error.message)
                })
        },
        addProduct: async ({ commit }, product) => {
            commit('SET_LOADING', true)
            return Request.post('addProduct.php', product)
                .then((response) => {
                    console.log(response)
                    commit('SET_LOADING', false)
                    if(response.status) {
                        commit('ADD_PRODUCT', response.product)
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
        updateProduct: async ({ commit }, { product, index }) => {
            commit('SET_LOADING', true)
            return Request.post('updateProduct.php', product)
                .then((response) => {
                    console.log(response)
                    commit('SET_LOADING', false)
                    if(response.status) {
                        commit('UPDATE_PRODUCT', { product: response.product, index })
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
        deleteProduct: async ({ commit }, { product, index }) => {
            commit('SET_LOADING', true)
            return Request.post('deleteProduct.php', product)
                .then((response) => {
                    console.log(response)
                    commit('SET_LOADING', false)
                    if(response.status) {
                        commit('REMOVE_PRODUCT', index)
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
        listPackTypes: async ({ commit }) => {
            commit('SET_LOADING', true)
            return Request.get('listPackTypes.php')
                .then((response) => {
                    console.log(response)
                    commit('SET_LOADING', false)
                    commit('SET_PACKS', response)
                })
                .catch((error) => {
                    console.log(error)
                    commit('SET_LOADING', false)
                    throw new Error(error.message)
                })
        },
        updatePackType: async ({ commit }, { pack, index }) => {
            commit('SET_LOADING', true)
            return Request.post('updatePackType.php', pack)
                .then((response) => {
                    console.log(response)
                    commit('SET_LOADING', false)
                    if(response.status) {
                        console.log(response.pack)
                        commit('UPDATE_PACK', { pack: response.pack, index })
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
    }
}