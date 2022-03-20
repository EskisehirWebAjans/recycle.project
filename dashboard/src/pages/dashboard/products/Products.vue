<template>
    <div class="d-flex justify-content-center" v-if="loading">
        <div class="spinner-grow text-success" role="status">
            <span class="visually-hidden">Loading...</span>
        </div>
    </div>
    
    <div class="table-responsive" v-else>
        <button 
            @click="onAdd()"
            type="button" 
            class="btn btn-md btn-success">Yeni
        </button>
        <table class="table table-striped table-sm">
            <thead>
                <tr>
                <th scope="col">#</th>
                <th scope="col">Ürün</th>
                <th scope="col">Barkod</th>
                <th scope="col">Atık Türü</th>
                <th scope="col">İşlemler</th>
                </tr>
            </thead>
            <tbody>
                <template v-if="products.length > 0">
                    <tr v-for="(product, index) in products" :key="product.id">
                        <td> {{ index + 1 }} </td>
                        <td>{{ product.title }}</td>
                        <td>{{ product.barcode }}</td>
                        <td>{{ product.type }}</td>
                        <td>
                            <div class="btn-group me-2">
                                <button 
                                    @click="onEdit(product)"
                                    type="button" 
                                    class="btn btn-sm btn-outline-warning">Düzenle</button>
                                <button 
                                    @click="onDelete(product)"
                                    type="button" 
                                    class="btn btn-sm btn-outline-danger">Sil</button>
                            </div>
                        </td>
                    </tr>
                </template>  
                <template v-else>
                    <tr>
                        <td colspan="5">
                            <h2>Ürün bulunamadı!</h2>  
                        </td>
                    </tr>
                </template>
            </tbody>    
        </table>
        <ProductModal ref="editModal" :item="activeItem" :index="activeIndex"/>
    </div>
</template>

<script>
import ProductModal from './ProductModal.vue'
import { computed, onMounted, reactive, ref } from 'vue'
import { useStore } from 'vuex'
export default {
    setup() {
        const activeItem = reactive({})
        const activeIndex = ref(null)
        const editModal = ref(null)
        const store = useStore()
        const products = computed(() => store.state.product.products)
        const loading = computed(() => store.state.product.loading)

        onMounted(async () => {
            await store.dispatch("product/listProducts")
            await store.dispatch('product/listPackTypes')
        })

        const onAdd = () => {
            Object.assign(activeItem, {
                id: -1,
                title: '',
                barcode: '',
                recycle_type: ''
            })
            editModal.value.show()
        } 

        const onEdit = (item) => {
            Object.assign(activeItem, item)
            activeIndex.value = products.value.indexOf(item)
            editModal.value.show()
        }

        const onDelete = async (item) => {
            if (confirm("Seçili ürünü silmek istiyor musunuz?")) {
                const index = products.value.indexOf(item);
                if (index > -1) {
                    try {
                        await store.dispatch("product/deleteProduct", {
                            product: item,
                            index
                        })
                        alert('İşlem başarılı!')
                    } catch(error) {
                        console.log(error)
                        alert(error)
                    }
                }
                else {
                    alert("Ürün bulunamadı!");
                }
            }
        }  
        return {
            products,
            loading,
            activeItem,
            activeIndex,
            editModal,
            onEdit,
            onDelete,
            onAdd
        };
    },
    components: { ProductModal }
}
</script>

<style>

</style>