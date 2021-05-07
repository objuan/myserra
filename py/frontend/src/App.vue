
<template>
  <div id="app">

    <b-navbar toggleable="lg" type="dark" variant="info">
      <b-navbar-brand href="#">MySerra</b-navbar-brand>
       <span class="btn-success">
          State: {{board_state}}&nbsp;&nbsp;&nbsp;
       </span>

      <b-navbar-toggle target="nav-collapse"></b-navbar-toggle>

      <b-collapse id="nav-collapse" is-nav>
        <b-nav card-header tabs>
          <b-nav-item  to="/centralina" exact exact-active-class="active">Centralina</b-nav-item>
          <b-nav-item  to="/boardlist" exact exact-active-class="active">Boards</b-nav-item>
          <b-nav-item to="/log" exact exact-active-class="active">Log </b-nav-item>
          <b-nav-item to="/admin/" exact exact-active-class="active">Admin </b-nav-item>
        </b-nav>

        <!-- Right aligned nav items -->
        <b-navbar-nav class="ml-auto">
          <b-nav-form>
            <b-form-input size="sm" class="mr-sm-2" placeholder="Search"></b-form-input>
            <b-button size="sm" class="my-2 my-sm-0" type="submit">Search</b-button>
          </b-nav-form>

          <b-nav-item-dropdown right>
            <!-- Using 'button-content' slot -->
            <template #button-content>
              <em>User</em>
            </template>
            <b-dropdown-item href="#">Profile</b-dropdown-item>
            <b-dropdown-item href="#">Sign Out</b-dropdown-item>
          </b-nav-item-dropdown>
        </b-navbar-nav>
      </b-collapse>
    </b-navbar>

    <router-view ></router-view>

  </div>
</template>

<script>
//import HelloWorld from './components/HelloWorld.vue'
//import BoardList from './components/BoardList.vue'

import Vue from 'vue'
import { BootstrapVue, IconsPlugin } from 'bootstrap-vue'

// Import Bootstrap an BootstrapVue CSS files (order is important)
import 'bootstrap/dist/css/bootstrap.css'
import 'bootstrap-vue/dist/bootstrap-vue.css'
//import Log from './components/Log.vue'

// Make BootstrapVue available throughout your project
Vue.use(BootstrapVue)
// Optionally install the BootstrapVue icon components plugin
Vue.use(IconsPlugin)

export default {
  name: 'App',
  components: {
  //  Log
  },
  data() {
    return {
      board_state : "............"
    };
  },
  methods: {
  
    connect_event: function() {
      var ws = new WebSocket('ws://'
                + window.location.host
                + '/ws/event/');

      var self=this;

    ws.onopen = function(e) {
        console.log("Socket open",e);
      
      };
      ws.onmessage = function(e) {
         //console.log( e.data);
         var o = JSON.parse(e.data);
        //console.log( e.data,o);
        if (o.type=="connect")
          self.board_state=o.msg;
      };

      ws.onclose = function(e) {
        console.log('Socket is closed. Reconnect will be attempted in 1 second.', e.reason);
        setTimeout(function() {
          self.connect_event();
        }, 1000);
      };

      ws.onerror = function(err) {
        console.error('Socket encountered error: ', err.message, 'Closing socket');
        ws.close();
      };
    }
  },
  created() {
    
    this.connect_event();
  },
}
// =======

</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}

</style>
