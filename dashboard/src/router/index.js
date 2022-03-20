import { createRouter, createWebHashHistory } from 'vue-router'

const routes = [
  {
    path: '/giris-yap',
    name: 'login',
    meta: {
      title: '',
      requiresVisitor: true
    },
    component: () => import('@/pages/Login')
  },
  {
    path: '/',
    redirect: '/dashboard',
    component: () => import('@/pages/Dashboard'),
    meta: {
      title: 'Panel',
    },
    children: [
      {
        path: '/dashboard',
        name: 'dashboard',
        component: () => import('@/pages/dashboard/home/Home'),
        meta: {
          title: 'Anasayfa',
          requiresAuth: true,
        }
      },
      {
        path: '/ogrenciler',
        name: 'students',
        component: () => import('@/pages/dashboard/students/Students'),
        meta: {
          title: 'Öğrenciler',
          requiresAuth: true,
        }
      },
      {
        path: '/urunler',
        name: 'products',
        component: () => import('@/pages/dashboard/products/Products'),
        meta: {
          title: 'Ürünler',
          requiresAuth: true,
        }
      },
      {
        path: '/atiklar',
        name: 'pack-types',
        component: () => import('@/pages/dashboard/packs/PackTypes'),
        meta: {
          title: 'Atık Türleri',
          requiresAuth: true,
        }
      },
      {
        path: '/ogrenci-atiklari',
        name: 'student-recycles',
        component: () => import('@/pages/dashboard/students/StudentRecycles'),
        meta: {
          title: 'Öğrenci Atıkları',
          requiresAuth: true,
        }
      }
    ]
  },

]

const router = createRouter({
  history: createWebHashHistory(),
  routes
})

export default router
