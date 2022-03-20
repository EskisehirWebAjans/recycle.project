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
            <th scope="col">Ad</th>
            <th scope="col">Soyad</th>
            <th scope="col">Numara</th>
            <th scope="col">Sınıf</th>
            <th scope="col">İşlemler</th>
          </tr>
        </thead>
        <tbody>
          <template v-if="students.length > 0">
            <tr v-for="(student, index) in students" :key="student.id">
              <td> {{ index + 1 }} </td>
              <td> {{ student.name }} </td>
              <td> {{ student.surname }} </td>
              <td> {{ student.number }} </td>
              <td> {{ student.class }} </td>
              <td>
                <div class="btn-group me-2">
                  <button 
                      @click="onEdit(student)"
                      type="button" 
                      class="btn btn-sm btn-outline-warning">Düzenle</button>
                  <button 
                      @click="onDelete(student)"
                      type="button" 
                      class="btn btn-sm btn-outline-danger">Sil</button>
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
      <StudentModal ref="editModal" :item="activeItem" :index="activeIndex"/>
    </div>
</template>

<script>
import { reactive, ref, onMounted, computed } from 'vue'
import StudentModal from "./StudentModal.vue"
import { useStore } from 'vuex'
export default {
  setup() {
    const activeItem = reactive({})
    const activeIndex = ref(null)
    const editModal = ref(null)
    const store = useStore()
    const students = computed(() => store.state.student.students)
    const loading = computed(() => store.state.student.loading)

    onMounted( async () => {
      await store.dispatch('student/listStudents')
    })

    const onAdd = () => {
      Object.assign(activeItem, {
          id: -1,
          name: '',
          surname: '',
          number: '',
          class: ''
      })
      editModal.value.show()
    } 

    const onEdit = (item) => {
      Object.assign(activeItem, item)
      activeIndex.value = students.value.indexOf(item)
      editModal.value.show()
    }
    
    const onDelete = async (item) => {
      if (confirm("Seçili öğrenciyi silmek istiyor musunuz?")) {
          const index = students.value.indexOf(item);
          if (index > -1) {
              try {
                  await store.dispatch("student/deleteStudent", {
                      student: item,
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
      students,
      loading,
      activeItem,
      activeIndex,
      editModal,
      onAdd,
      onEdit,
      onDelete
    }
  },
  components: { StudentModal }
}
</script>

<style>

</style>