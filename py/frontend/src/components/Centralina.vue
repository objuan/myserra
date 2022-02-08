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
                ph_ref_6="19" temperature="15" distance="20" distance_empty="21" 
                ec_pump_1="11"  ec_pump_1_weight="22"  ec_pump_2="12" ph_pump="13"
                mix_up_pump="14" water_in_pump="15" tank_1_in_pump="9" tank_1_out_pump="10"
                />
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

