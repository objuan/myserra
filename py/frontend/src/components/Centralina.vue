<template>
  <div>

  <table border=0 style="width:100%">
    <tr valign="top">
     
      <tr>
       
    </tr>
  </table>

  <b-card  header="LEDS" 
         style="max-width: 90rem;">
            <b-card-text>
                <timedswitch vswitch="8" venable="11" vscheduler="12" />
               
                
            </b-card-text>
        </b-card>
    </div>
</template>

<script>
  //  import axios from 'axios';
  //  import Vue from 'vue'
   // import VueTimepicker from 'vue2-timepicker'
     import timedswitch from './TimedSwitch.vue'
   // import GetVarConnection from './common'

    export default {
        name: "centralina",
        props: {
           
        },
        
        components: {
                timedswitch 
        },
        data() {
            return {
                
            };
        },
       
        methods: {
            
        },
    }
</script>

