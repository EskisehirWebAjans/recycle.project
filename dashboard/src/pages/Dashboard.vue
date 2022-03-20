<template>
  <NavBar/>
  <div class="container-fluid">
    <div class="row">
        <SideBar/>
        <main class="col-md-9 ms-sm-auto col-lg-10 px-md-4">
            <BreadCrumb/>
            <router-view/>
        </main>
    </div>
  </div>
</template>

<script>
import NavBar from '@/components/dashboard/NavBar.vue'
import SideBar from '@/components/dashboard/SideBar.vue'
import BreadCrumb from '@/components/dashboard/BreadCrumb.vue'

export default {
    components: {
        NavBar,
        SideBar,
        BreadCrumb
    }
}
</script>

<style>

</style>