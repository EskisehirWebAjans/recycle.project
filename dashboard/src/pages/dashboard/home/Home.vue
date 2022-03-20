<template>
  <div class="row row-cols-1 row-cols-md-4 mb-3 text-center">
      <div class="col">
        <div class="card mb-4 rounded-3 shadow-sm">
          <div class="card-header py-3">
            <h4 class="my-0 fw-normal">Kağıt</h4>
          </div>
          <div class="card-body">
            <h1 class="card-title pricing-card-title"> {{ paper }} </h1>
            
          </div>
        </div>
      </div>
      <div class="col">
        <div class="card mb-4 rounded-3 shadow-sm">
          <div class="card-header py-3">
            <h4 class="my-0 fw-normal">Cam</h4>
          </div>
          <div class="card-body">
            <h1 class="card-title pricing-card-title"> {{ glass }} </h1>
            
          </div>
        </div>
      </div>
      <div class="col">
        <div class="card mb-4 rounded-3 shadow-sm">
          <div class="card-header py-3">
            <h4 class="my-0 fw-normal">Plastik</h4>
          </div>
          <div class="card-body">
            <h1 class="card-title pricing-card-title"> {{ plastic }} </h1>
            
          </div>
        </div>
      </div>
      <div class="col">
        <div class="card mb-4 rounded-3 shadow-sm">
          <div class="card-header py-3">
            <h4 class="my-0 fw-normal">Metal</h4>
          </div>
          <div class="card-body">
            <h1 class="card-title pricing-card-title"> {{ metal }} </h1>
            
          </div>
        </div>
      </div>
  </div>
  <div class="table-responsive">
        <table class="table table-striped table-sm">
            <thead>
                <tr>
                <th scope="col">#</th>
                <th scope="col">Öğrenci</th>
                <th scope="col">Sınıf</th>
                <th scope="col">Numara</th>
                <th scope="col">Puan</th>
                </tr>
            </thead>
            <tbody>
                <template v-if="topList.length > 0">
                    <tr v-for="(top, index) in topList" :key="index">
                        <td> {{ index + 1 }} </td>
                        <td>{{ top.name }} {{ top.surname }}</td>
                        <td>{{ top.class }}</td>
                        <td>{{ top.number }}</td>
                        <td> {{ top.point }} </td>
                    </tr>
                </template>  
                <template v-else>
                    <tr>
                        <td colspan="5">
                            <h2>Öğrenci bulunamadı!</h2>  
                        </td>
                    </tr>
                </template>
            </tbody>    
        </table>
  </div>
</template>

<script>
import { onMounted } from '@vue/runtime-core'
import { useStore } from 'vuex'
import { ref } from 'vue'
export default {
    setup() {
        const store = useStore()
        const paper = ref(0)
        const glass = ref(0)
        const plastic = ref(0)
        const metal = ref(0)
        const topList = ref([])

        onMounted(async () => {
            paper.value = await store.dispatch('stat/getStatByType', 1)
            glass.value = await store.dispatch('stat/getStatByType', 2)
            plastic.value = await store.dispatch('stat/getStatByType', 3)
            metal.value = await store.dispatch('stat/getStatByType', 4)
            topList.value = await store.dispatch('stat/topList')
        })

        return {
            paper,
            glass,
            plastic,
            metal,
            topList
        }
    }
}
</script>

<style scoped>
.container {
  max-width: 960px;
}
.pricing-header {
  max-width: 700px;
}
</style>