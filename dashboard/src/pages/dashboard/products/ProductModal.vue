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
                    placeholder="Yulaflı Bisküvi">

                <div v-if="v$.title.$invalid" class="invalid-feedback">
                    <span v-if="v$.title.required">Ürün adı girilmelidir!</span>
                </div>
                <label for="floatingInput">Ürün</label>
            </div>
            <div class="form-floating mb-3">
                <input 
                    v-model="form.barcode"
                    type="text" 
                    class="form-control rounded-4"
                    :class="{ 'is-invalid' : isSubmitted && v$.barcode.$invalid, 'is-valid' : isSubmitted && !v$.barcode.$invalid }"
                    placeholder="8949844994">

                <div v-if="v$.barcode.$invalid" class="invalid-feedback">
                    <span v-if="v$.barcode.required">Ürün barkodu girilmelidir!</span>
                </div>
                <label for="floatingPassword">Barkod</label>
            </div>
            <div class="form-floating mb-3">
                
                <select 
                    v-model="form.recycle_type"
                    class="form-select"
                    :class="{ 'is-invalid' : isSubmitted && v$.recycle_type.$invalid, 'is-valid' : isSubmitted && !v$.recycle_type.$invalid }">
                    <option value="">Ambalaj Türü Seçiniz...</option>
                    <option 
                        v-for="(pack, index) in packs" :key="index"
                        :value="pack.id"> 
                        {{ pack.title }} 
                    </option>
                </select>
                <div v-if="v$.recycle_type.$invalid" class="invalid-feedback">
                    <span v-if="v$.recycle_type.required">Ürün paket türü girilmelidir!</span>
                </div>
                <label for="floatingSelect">Paket Türü</label>
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
            barcode: '',
            recycle_type: ''
        }
        let modal = null
        const form = reactive({ ...initialState })
        const editModal = ref(null)
        const isSubmitted = ref(false)
        const store = useStore()
        const packs = computed(() => store.state.product.packs)
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
                barcode: { required },
                recycle_type: { required }
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
                    await store.dispatch('product/updateProduct', { product: form, index: props.index })
                } else {
                    await store.dispatch('product/addProduct', form)
                }
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
            packs,
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
    .bi {
        vertical-align: -.125em;
        fill: currentColor;
    }

    .rounded-4 { border-radius: .5rem; }
    .rounded-5 { border-radius: .75rem; }
    .rounded-6 { border-radius: 1rem; }

    .modal-sheet .modal-dialog {
        width: 380px;
        transition: bottom .75s ease-in-out;
    }
    .modal-sheet .modal-footer {
        padding-bottom: 2rem;
    }

    .modal-alert .modal-dialog {
        width: 380px;
    }

    .border-right { border-right: 1px solid #eee; }

    .modal-tour .modal-dialog {
        width: 380px;
    }
</style>