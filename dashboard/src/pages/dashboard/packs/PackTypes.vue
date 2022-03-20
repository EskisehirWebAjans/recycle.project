<template>
  <div class="d-flex justify-content-center" v-if="loading">
    <div class="spinner-grow text-success" role="status">
        <span class="visually-hidden">Loading...</span>
    </div>
  </div>
  <div class="table-responsive" v-else>
    <table class="table table-striped table-sm">
      <thead>
        <tr>
          <th scope="col">#</th>
          <th scope="col">Tür</th>
          <th scope="col">Puan</th>
          <th scope="col">İşlemler</th>
        </tr>
      </thead>
      <tbody>
        <template v-if="packs.length > 0">
            <tr v-for="(pack, index) in packs" :key="pack.id">
              <td> {{ index + 1 }} </td>
              <td> {{ pack.title }} </td>
              <td> {{ pack.reward }} </td>
              <td>
                <div class="btn-group me-2">
                  <button 
                      @click="onEdit(pack)"
                      type="button" 
                      class="btn btn-sm btn-outline-warning">Düzenle</button>
                </div>
              </td>
            </tr>
          </template>
          <template v-else>
            <tr>
                <td colspan="6">
                    <h2>Öğrenci bulunamadı!</h2>  
                </td>
            </tr>
          </template>
      </tbody>    
    </table>
  </div>
  <PackModal ref="editModal" :item="activeItem" :index="activeIndex"/>
</template>

<script>
import PackModal from "./PackModal.vue"
import { reactive, ref, onMounted, computed } from 'vue'
import { useStore } from 'vuex'
export default {
  setup() {
    const activeItem = reactive({})
    const activeIndex = ref(null)
    const editModal = ref(null)
    const store = useStore()
    const packs = computed(() => store.state.product.packs)
    const loading = computed(() => store.state.product.loading)

    onMounted( async () => {
      await store.dispatch('product/listPackTypes')
    })

    const onEdit = (item) => {
      Object.assign(activeItem, item)
      activeIndex.value = packs.value.indexOf(item)
      editModal.value.show()
    }

    return {
      packs,
      loading,
      activeItem,
      activeIndex,
      editModal,
      onEdit
    }
  },
  components: { PackModal }
}
</script>

<style>

</style>