<template>
  <nav id="sidebarMenu" class="col-md-3 col-lg-2 d-md-block bg-light sidebar collapse">
      <div class="position-sticky pt-3">
        <ul class="nav flex-column">
          <li class="nav-item">
            <router-link :to="{ name: 'dashboard' }" class="nav-link fs-5" :exact-active-class="'active'">
              <BIconHouseFill/> Anasayfa
            </router-link>
          </li>
          <li class="nav-item">
            <router-link :to="{ name: 'products' }"  class="nav-link fs-5" :exact-active-class="'active'">
              <BIconUpcScan /> Ürünler
            </router-link>
          </li>
          <li class="nav-item">
            <router-link :to="{ name: 'students' }"  class="nav-link fs-5" :exact-active-class="'active'">
              <BIconPeopleFill /> Öğrenciler
            </router-link>
          </li>
          <li class="nav-item">
            <router-link :to="{ name: 'pack-types' }"  class="nav-link fs-5" :exact-active-class="'active'">
              <BIconTrash2Fill /> Atık Türleri
            </router-link>
          </li>
          <li class="nav-item">
            <router-link :to="{ name: 'student-recycles' }"  class="nav-link fs-5" :exact-active-class="'active'">
              <BIconRecycle /> Öğrenci Atıkları
            </router-link>
          </li>
        </ul>
      </div>
    </nav>
</template>

<script>
export default {

}
</script>

<style>

</style>