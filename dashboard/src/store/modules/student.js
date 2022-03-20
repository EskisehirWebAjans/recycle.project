import Request from "@/shared/api/Request"

export default {
    namespaced: true,
    state: {
        students: [],
        recyclings: [],
        loading: false,
    },
    mutations: {
        SET_STUDENTS: (state, students) => {
            state.students = []
            students.map(student => {
                state.students.push(student)
            })
        },
        ADD_STUDENT: (state, student) => {
            state.students.unshift(student)
        },
        UPDATE_STUDENT: (state, { student, index }) => {
            Object.assign(state.students[index], student)
        },
        REMOVE_STUDENT: (state, index) => {
            state.students.splice(index, 1)
        },
        SET_LOADING: (state, loading) => {
            state.loading = loading
        },
        SET_RECYCLINGS: (state, recyclings) => {
            state.recyclings = []
            recyclings.map(recycling => {
                state.recyclings.push(recycling)
            })
        },
        REMOVE_RECYCLING: (state, index) => {
            state.recyclings.splice(index, 1)
        },
    },
    actions: {
        listStudents: async ({ commit }) => {
            commit('SET_LOADING', true)
            return Request.get('listStudents.php')
                .then((response) => {
                    console.log(response)
                    commit('SET_LOADING', false)
                    commit('SET_STUDENTS', response)
                })
                .catch((error) => {
                    console.log(error)
                    commit('SET_LOADING', false)
                    throw new Error(error.message)
                })
        },
        addStudent: async({ commit }, student) => {
            commit('SET_LOADING', true)
            return Request.post('addStudent.php', student)
                .then((response) => {
                    console.log(response)
                    commit('SET_LOADING', false)
                    if(response.status) {
                        commit('ADD_STUDENT', response.student)
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
        updateStudent: async({ commit }, { student, index }) => {
            commit('SET_LOADING', true)
            return Request.post('updateStudent.php', student)
                .then((response) => {
                    console.log(response)
                    commit('SET_LOADING', false)
                    if(response.status) {
                        commit('UPDATE_STUDENT', { student: response.student, index })
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
        deleteStudent: async ({ commit }, { student, index }) => {
            commit('SET_LOADING', true)
            return Request.post('deleteStudent.php', student)
                .then((response) => {
                    console.log(response)
                    commit('SET_LOADING', false)
                    if(response.status) {
                        commit('REMOVE_STUDENT', index)
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
        listRecyclings: async({ commit }) => {
            commit('SET_LOADING', true)
            return Request.get('listRecycling.php')
                .then((response) => {
                    console.log(response)
                    commit('SET_LOADING', false)
                    commit('SET_RECYCLINGS', response)
                })
                .catch((error) => {
                    console.log(error)
                    commit('SET_LOADING', false)
                    throw new Error(error.message)
                })
        },
        deleteRecycling: async ({ commit }, { recycling, index }) => {
            commit('SET_LOADING', true)
            return Request.post('deleteRecycling.php', recycling)
                .then((response) => {
                    console.log(response)
                    commit('SET_LOADING', false)
                    if(response.status) {
                        commit('REMOVE_RECYCLING', index)
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