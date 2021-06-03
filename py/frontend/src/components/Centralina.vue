<template>
  <div>

  <table border=0 style="width:100%">
    <tr valign="top">
     
      <tr>
       
    </tr>
  </table>

    <b-card  header="LEDS" >
            <b-card-text>
                <timedswitch vswitch="8" venable="11" vscheduler="12" />
            </b-card-text>
        </b-card>

          <b-card  header="LAB" >
            <b-card-text>
                <lab ec="13" ec_k="14"  ph="16"  ph_volt="17"   ph_ref_4="18"   
                ph_ref_6="19" temperature="15" distance="20" distance_empty="21" />
            </b-card-text>
        </b-card>
    </div>
</template>

<script>
  //  import axios from 'axios';
  //  import Vue from 'vue'
   // import VueTimepicker from 'vue2-timepicker'
     import timedswitch from './TimedSwitch.vue'
     import lab from './Lab.vue'
   // import GetVarConnection from './common'

    export default {
        name: "centralina",
        props: {
           
        },
        
        components: {
                timedswitch ,lab
        },
        data() {
            return {
                
            };
        },
       
        methods: {
            
        },
    }
</script>

