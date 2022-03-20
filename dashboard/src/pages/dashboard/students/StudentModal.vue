<template>
  <div ref="editModal" class="modal modal-signin bg-secondary py-5" tabindex="-1" role="dialog">
    <div class="modal-dialog modal-dialog-centered" role="document">
        <div class="modal-content rounded-5 shadow">
        <div class="modal-header p-5 pb-4 border-bottom-0">
            <h5 class="modal-title">{{ form.id > -1 ? 'Düzenle' : 'Ekle' }}</h5>
            <button type="button" class="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
        </div>

        <div class="modal-body p-5 pt-0">
            <form class="">
            <div class="form-floating mb-3">
                <input 
                    v-model="form.name"
                    type="text" 
                    class="form-control rounded-4" 
                    :class="{ 'is-invalid' : isSubmitted && v$.name.$invalid, 'is-valid' : isSubmitted && !v$.name.$invalid }"
                    placeholder="Esila">

                <div v-if="v$.name.$invalid" class="invalid-feedback">
                    <span v-if="v$.name.required">Öğrenci adı girilmelidir!</span>
                </div>
                <label for="floatingInput">Ad</label>
            </div>
            <div class="form-floating mb-3">
                <input 
                    v-model="form.surname"
                    type="text" 
                    class="form-control rounded-4"
                    :class="{ 'is-invalid' : isSubmitted && v$.surname.$invalid, 'is-valid' : isSubmitted && !v$.surname.$invalid }"
                    placeholder="Öztürk">

                <div v-if="v$.surname.$invalid" class="invalid-feedback">
                    <span v-if="v$.surname.required">Öğrenci soyadı girilmelidir!</span>
                </div>
                <label for="floatingPassword">Soyad</label>
            </div>
            <div class="form-floating mb-3">
                <input 
                    v-model="form.number"
                    type="text" 
                    class="form-control rounded-4"
                    :class="{ 'is-invalid' : isSubmitted && v$.number.$invalid, 'is-valid' : isSubmitted && !v$.number.$invalid }"
                    placeholder="980">

                <div v-if="v$.number.$invalid" class="invalid-feedback">
                    <span v-if="v$.number.required">Öğrenci numarası girilmelidir!</span>
                </div>
                <label for="floatingPassword">Numara</label>
            </div>
            <div class="form-floating mb-3">
                <input 
                    v-model="form.class"
                    type="text" 
                    class="form-control rounded-4"
                    :class="{ 'is-invalid' : isSubmitted && v$.class.$invalid, 'is-valid' : isSubmitted && !v$.class.$invalid }"
                    placeholder="7-C">

                <div v-if="v$.class.$invalid" class="invalid-feedback">
                    <span v-if="v$.class.required">Öğrenci sınıfı girilmelidir!</span>
                </div>
                <label for="floatingPassword">Sınıf</label>
            </div>
            </form>
        </div>
        <div class="modal-footer flex-nowrap p-0">
                <button @click.prevent="onSubmit" v-if="form.id  == -1" class="w-100 mb-2 btn btn-md rounded-4 btn-success" type="submit" :disabled="loading">
                    <span v-if="!loading">Kaydet</span> 
                    <span v-else>
                        <span class="spinner-grow spinner-grow-sm" role="status" aria-hidden="true"></span>Kaydediliyor...
                    </span>
                </button>
                <button @click.prevent="onSubmit" v-else class="w-100 mb-2 btn btn-md rounded-4 btn-warning" type="submit" :disabled="loading">
                    <span v-if="!loading">Güncelle</span> 
                    <span v-else>
                        <span class="spinner-grow spinner-grow-sm" role="status" aria-hidden="true"></span>Güncelleniyor...
                    </span>
                </button>
                <button @click.prevent="onClose" class="w-100 mb-2 btn btn-md rounded-4 btn-secondary" type="submit">Kapat</button>
        </div>
        </div>
    </div>
    </div>
</template>

<script>
import { Modal } from 'bootstrap'
import { ref, reactive, computed, nextTick } from 'vue'
import useVuelidate from '@vuelidate/core'
import { required } from '@vuelidate/validators'
import { useStore } from 'vuex'

export default {
    props: {
        item: {
            type: Object,
            required: true
        },
        index: Number
    },
    setup(props) {
        const initialState = {
            id: null,
            name: '',
            surname: '',
            number: '',
            class: ''
        }
        let modal = null
        const form = reactive({ ...initialState })
        const editModal = ref(null)
        const isSubmitted = ref(false)
        const store = useStore()
        const loading = computed(() => store.state.student.loading)

        const show = () => {
            modal = new Modal(editModal.value, {
                keyboard: false,
                backdrop: true
            })
            editModal.value.addEventListener('hidden.bs.modal', onHidden)
            editModal.value.addEventListener('shown.bs.modal', onShown)
            modal.show()
        }

        const hide = () => {
            modal.hide()
        }

        const onClose = () => {
            modal.hide()
        }

        const rules = computed(() => {
            return {
                name: { required },
                surname: { required },
                number: { required },
                class: { required }
            }
        })

        const v$ = useVuelidate(rules, form)

        const onSubmit = async (e) => {
            e.preventDefault()
            isSubmitted.value = true
            const result = await v$.value.$validate()
            if(!result) {
                alert('Formda hatalar var!')
                return
            }
            try {
                if(form.id > -1) {
                    await store.dispatch('student/updateStudent', { student: form, index: props.index })
                } else {
                    await store.dispatch('student/addStudent', form)
                }
                modal.hide()
                alert('İşlem başarılı!')
            } catch(error) {
                console.log(error)
                alert('Bir hata oluştu!')
            }
        }

        const onHidden = async () => {
            await nextTick()
            resetForm()
            console.log('Hidden')
        }

        const onShown = () => {   
            console.log('Shown')
            Object.assign(form, props.item)
        }

        const resetForm = () => {
            Object.assign(form, initialState)
            isSubmitted.value = false
            v$.value.$reset()
        }

        return {
            form,
            editModal,
            isSubmitted,
            loading,
            modal,
            v$,
            show,
            hide,
            onClose,
            onSubmit,
            resetForm
        }
    }
}
</script>

<style>

</style>