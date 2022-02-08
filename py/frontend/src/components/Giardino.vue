<template>
    <div>
    <b-card  header="GIARDINO" 
         style="max-width: 90rem;">
            <b-card-text>
               <timedswitch vswitch="7" venable="10" vscheduler="9" />
                
                <timedswitch vswitch="17" venable="24" vscheduler="23" />
              
            </b-card-text>
        </b-card>
    </div>
</template>

<script>
   // import axios from 'axios';
    //import Vue from 'vue'
    //import VueTimepicker from 'vue2-timepicker'
    import 'vue2-timepicker/dist/VueTimepicker.css'
    import timedswitch from './TimedSwitch.vue'
   // import GetVarConnection from './common'

    export default {
        name: "giardino",
        props: {
           
        },
        
        components: {
            timedswitch
        },
      
       
        methods: {
            
        },
    }
</script>
