import Vue from 'vue'
import App from './App.vue'

import VueRouter from 'vue-router'

import BoardList from './components/BoardList'
import Centralina from './components/Centralina'
import Giardino from './components/Giardino'
import Semenzario from './components/Semenzario'
import Log from './components/Log'

// import some global styles
//import './styles/style.scss'

Vue.config.productionTip = false

Vue.use(VueRouter)


const routes = [
  { path: '/centralina', alias: '/', component: Centralina },
  { path: '/boardlist',  component: BoardList },
  { path: '/giardino',  component: Giardino },
  { path: '/log', component: Log },
  { path: '/semenzario',  component: Semenzario }
]

// Create the router instance and pass the `routes` option
const router = new VueRouter({
  mode: 'history',
  routes: routes,
})
/*
new Vue({
  render: h => h(App),
}).$mount('#app')
*/

/* eslint-disable no-new */
new Vue({
  el: '#app',
  router,
  render: h => h(App)
})
