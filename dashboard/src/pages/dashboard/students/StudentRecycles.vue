<template>
  <div class="d-flex justify-content-center" v-if="loading">
    <div class="spinner-grow text-success" role="status">
        <span class="visually-hidden">Loading...</span>
    </div>
  </div>
  <div class="table-responsive" v-else>
      <button 
        @click="onRefresh()"
        type="button" 
        class="btn btn-md btn-primary">Yenile
      </button>
        <table class="table table-striped table-sm">
          <thead>
            <tr>
              <th scope="col">#</th>
              <th scope="col">Öğrenci</th>
              <th scope="col">No</th>
              <th scope="col">Sınıf</th>
              <th scope="col">Atık</th>
              <th scope="col">Puan</th>
              <th scope="col">Tarih</th>
            </tr>
          </thead>
          <tbody>
            <template v-if="recyclings.length > 0">
              <tr v-for="(recycling, index) in recyclings" :key="recyclings.id">
                <td> {{ index + 1 }} </td>
                <td> {{ recycling.name }} {{ recycling.surname }} </td>
                <td> {{ recycling.number }} </td>
                <td> {{ recycling.class }} </td>
                <td> {{ recycling.rTitle }} </td>
                <td> {{ recycling.reward }} </td>
                <td> {{ recycling.inserted }} </td>
                <td>
                  <div class="btn-group me-2">
                    <button
                        @click="onDelete(recycling)"
                        type="button" 
                        class="btn btn-sm btn-outline-danger">Sil</button>
                  </div>
                </td>
              </tr>
            </template>
            <template v-else>
              <tr>
                  <td colspan="6">
                      <h2>Geri dönüşüm işlemi bulunamadı!</h2>  
                  </td>
              </tr>
            </template>
          </tbody>    
        </table>
    </div>
</template>

<script>
import { ref, onMounted, computed } from 'vue'
import { useStore } from 'vuex'
export default {
  setup() {
    const activeIndex = ref(null)
    const store = useStore()
    const recyclings = computed(() => store.state.student.recyclings)
    const loading = computed(() => store.state.student.loading)

    onMounted( async () => {
      await store.dispatch('student/listRecyclings')
    })

    const onRefresh = async () => {
      await store.dispatch('student/listRecyclings')
    }

    const onDelete = async (item) => {
      if (confirm("Seçili işlemi silmek istiyor musunuz?")) {
          const index = recyclings.value.indexOf(item);
          if (index > -1) {
              try {
                  await store.dispatch("student/deleteRecycling", {
                      recycling: item,
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
      activeIndex,
      recyclings,
      loading,
      onDelete,
      onRefresh
    }
  }
}
</script>

<style>

</style>