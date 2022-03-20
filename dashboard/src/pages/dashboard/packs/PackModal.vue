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
                        v-model="form.title"
                        type="text" 
                        class="form-control rounded-4" 
                        :class="{ 'is-invalid' : isSubmitted && v$.title.$invalid, 'is-valid' : isSubmitted && !v$.title.$invalid }"
                        placeholder="Kağıt">

                    <div v-if="v$.title.$invalid" class="invalid-feedback">
                        <span v-if="v$.title.required">Ambalaj bilgisi girilmelidir!</span>
                    </div>
                    <label for="floatingInput">Amabalaj Türü</label>
                </div>
                <div class="form-floating mb-3">
                    <input 
                        v-model="form.reward"
                        type="text" 
                        class="form-control rounded-4"
                        :class="{ 'is-invalid' : isSubmitted && v$.reward.$invalid, 'is-valid' : isSubmitted && !v$.reward.$invalid }"
                        placeholder="50">

                    <div v-if="v$.reward.$invalid" class="invalid-feedback">
                        <span v-if="v$.reward.required">Puan bilgisi girilmelidir!</span>
                    </div>
                    <label for="floatingPassword">Puan</label>
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
            title: '',
            reward: ''
        }
        let modal = null
        const form = reactive({ ...initialState })
        const editModal = ref(null)
        const isSubmitted = ref(false)
        const store = useStore()
        const loading = computed(() => store.state.product.loading)

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
                title: { required },
                reward: { required },
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
                await store.dispatch('product/updatePackType', { pack: form, index: props.index })
                modal.hide()
                alert('İşlem başarılı!')
            } catch(error) {
                console.log(error)
                    
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