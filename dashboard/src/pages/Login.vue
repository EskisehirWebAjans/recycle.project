<template>
    <main class="form-signin text-center" style="padding-top: 40px; padding-bottom: 40px;">
        <form @click.prevent="onSubmit">
            <img class="mb-4" src="@/assets/recycle-logo.png" alt="" width="72" height="57">
            <h1 class="h3 mb-3 fw-normal">Geri Dönüşüm Projesi</h1>
            
            <div class="form-floating mb-2">
                <input 
                    type="text" 
                    class="form-control"
                    :class="{ 'is-invalid' : isSubmitted && v$.username.$invalid, 'is-valid' : isSubmitted && !v$.username.$invalid }"
                    id="floatingInput" 
                    placeholder="Kullanıcı adı giriniz..." 
                    v-model="form.username">

                <div v-if="v$.username.$invalid" class="invalid-feedback">
                    <span v-if="v$.username.required">Kullanıcı adı girilmelidir!</span>
                </div>
                <label for="floatingInput">Kullanıcı Adı</label>
            </div>
            <div class="form-floating">
                <input 
                    type="password" 
                    class="form-control"
                    :class="{ 'is-invalid' : isSubmitted && v$.password.$invalid, 'is-valid' : isSubmitted && !v$.password.$invalid }"
                    id="floatingPassword" 
                    placeholder="Şifre giriniz..." 
                    v-model="form.password">

                <div v-if="v$.password.$invalid" class="invalid-feedback">
                    <span v-if="v$.password.required">Şifre girilmelidir!</span>
                </div>
                <label for="floatingPassword">Şifre</label>
            </div>
            <button class="w-100 btn btn-lg btn-primary" type="submit" :disabled="loading">
                <span v-if="!loading">Giriş Yap</span> 
                <span v-else>
                    <span class="spinner-grow spinner-grow-sm" role="status" aria-hidden="true"></span>
                    Giriş Yapılıyor...
                </span>
            </button>
            <p class="mt-5 mb-3 text-muted">Atatürk Ortaokulu &copy; 2022</p>
        </form>
    </main>

</template>

<script>
    import { reactive, computed, ref} from 'vue'
    import useVuelidate from '@vuelidate/core'
    import { required } from "@vuelidate/validators"
    import { useRouter } from 'vue-router'
import { useStore } from 'vuex'

    export default {
        setup() {
            const router = useRouter()
            const store = useStore()
            const isSubmitted = ref(false)
            const loading = computed(() => store.state.auth.loading)

            const form = reactive({
                username: '',
                password: ''
            })

            const rules = computed(() => {
                return {
                    username: { required },
                    password: { required }
                }
            })

            const v$ = useVuelidate(rules, form)

            const onSubmit = async () => {
                isSubmitted.value = true
                const result = await v$.value.$validate()
                if(!result) {
                    alert('Formda hatalar var!')
                    return
                }
                try {
                    await store.dispatch('auth/doLogin', form)
                    router.push({
                        name: 'dashboard'
                    })
                } catch(error) {
                    console.log(error)
                    alert(error)
                }
            }
            
            return { 
                form,
                loading,
                onSubmit,
                v$,
                isSubmitted,
                router
            }
        }
    }
</script>

<style scoped>
    html,
    body {
        height: 100%;
    }

    body {
        display: flex;
        align-items: center;
        padding-top: 40px;
        padding-bottom: 40px;
        background-color: #f5f5f5;
    }
    .form-signin {
        width: 100%;
        max-width: 330px;
        padding: 15px;
        margin: auto;
    }

    .form-signin .checkbox {
        font-weight: 400;
    }

    .form-signin .form-floating:focus-within {
        z-index: 2;
    }

    .form-signin input[type="email"] {
        margin-bottom: -1px;
        border-bottom-right-radius: 0;
        border-bottom-left-radius: 0;
    }

    .form-signin input[type="password"] {
        margin-bottom: 10px;
        border-top-left-radius: 0;
        border-top-right-radius: 0;
    }
</style>