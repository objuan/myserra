<template>
<div>

    <b-tabs content-class="mt-3">
        <b-tab title="Monitor" active><p>I'm the first tab</p></b-tab>
        <b-tab title="Settings">
            <div v-if="lab_board">
            <Board :board="lab_board" :compact="true"/>
            </div>
        </b-tab>
        <b-tab title="Calibrate">
            <div v-if="lab_board && var_ph_pump && var_ec_pump_1 && var_ec_pump_2">
                    <table witdh="100%">
                        <tr v-for="(pump, index) in pumps" :key="index" >
                            <td>
                               {{pump.name}}
                            </td>
                            <td>
                                 <b-button variant="success" @click="calibratePump(pump)">Start</b-button>
                            </td>
                           <td>
                                Calibrate Time secs
                            </td>
                             <td>

                                <b-form-input  v-model="pump.calib.time_secs" placeholder="Calibrate Time secs" type="number"></b-form-input>
                            </td>
                             <td>
                                Water filled (ML)
                            </td>
                             <td>
                                <b-form-input  v-model="pump.calib.filled_ml" placeholder="Water filled" type="number"></b-form-input>
                            </td>
                            <td>
                                  <b-button variant="primary" @click="savePump(pump)">Save</b-button>
                            </td>
                             <td>
                                Ml Per Secs {{pump.calib.ml_at_seconds}}
                            </td>
                            <td>
                                 <b-button variant="secondary" @click="testTimePump(pump)">Test Fill</b-button>
                            </td>
                            <td>
                                Fill Millilitres
                            </td>
                             <td>
                               <b-form-input  v-model="pump.calib_test_ml" placeholder="Water filled" type="number"></b-form-input>
                            </td>
                        </tr>
                    </table>
            </div>
        </b-tab>
  </b-tabs>


 </div>
</template>

<script>
    import axios from 'axios';
    import Board from './Board.vue'
  //  import App from '../App.vue';
   // import GetVarConnection from './common'

    export default {
        name: "lab",
        props: ['ec','ec_k','ph','ph_volt','ph_ref_4','ph_ref_6','temperature','distance','distance_empty'
        ,'ec_pump_1','ec_pump_2','ph_pump','mix_up_pump','water_in_pump','tank_1_in_pump','tank_1_out_pump'],
        
        components: {
            Board,
               // App
        },
        data() {
            return {
                 openClass: 'text-success',
                 closeClass: 'text-danger',

                 calib_data_ec : {name:'ec', idx:0,time_secs:60,ml: 0},
        
                 lab_board : null,
                 var_ec : null,
                 var_ec_k : null,
                var_ph : null,
                var_ph_volt : null,
                var_ph_ref_4 : null,
                  var_ph_ref_6: null,
                var_temperature : null,
                 var_distance : null,
                  var_distance_empty : null,

                  var_ec_pump_1:null,
                  var_ec_pump_2:null,
                  var_ph_pump:null,
                  var_mix_up_pump:null,
                  var_water_in_pump:null,
                  var_tank_1_in_pump:null,
                  var_tank_1_out_pump:null,

                  pumps: []
            };
        },
     
        methods: {
            testTimePump: function(pump) {
                 axios.post('/api/lab/test_time',  pump);
             },
            calibratePump: function(pump) {
                  axios.post('/api/lab/calibrate',  pump.calib);
             },
            savePump: function(pump) {
                axios.put('/api/switch/'+pump.id+'/calibrate', pump.calib);
             },
            
            save: function() {
                console.log("save");
                //  axios.put('/api/var/'+this.var_scheduling.id, this.var_scheduling);
             },
            
            connect_var: function() {
                    var self=this;
                    var ws = new WebSocket('ws://' + window.location.host  + '/ws/var/');
                    
                    ws.onmessage = function(e) {
                        var sw = JSON.parse(e.data);
                        if (sw.type=="var")
                        {
                           console.log("vaR");
                        }
                    };

                    ws.onclose = function() {
                        setTimeout(function() {
                        self.connect_var();
                        }, 1000);
                    };

                    ws.onerror = function() {
                        ws.close();
                    };
            },

            get_pump(id){
                return new Promise((resolve) => {
        
                   axios.get('/api/switch/'+id).then(   response => {
                        var sw = response.data
                        axios.get('/api/switch/'+id+"/calibrate").then(   response => {
                            sw.calib = response.data;
                            sw.calib_test_ml=60
                            resolve(sw);
                         }).catch(err => {
                              console.log(err) ;
                               resolve(response.data)
                              });

                        
                       
                   });
                })

             
            }
            

        },
        created() {

            this.connect_var();

            axios.get('/api/board/7').then(
                response => {
                this.lab_board = response.data;
                }
            );

            axios.get('/api/var/'+this.ec).then(   response => {
                this.var_ec = response.data; });

             axios.get('/api/var/'+this.ec_k).then(   response => {
                this.var_ec_k = response.data; });
            axios.get('/api/var/'+this.ph).then(   response => {
                            this.var_ph= response.data; });
            axios.get('/api/var/'+this.ph_volt).then(   response => {
                            this.var_ph_volt = response.data; });
            axios.get('/api/var/'+this.ph_ref_4).then(   response => {
                            this.var_ph_ref_4 = response.data; });
            axios.get('/api/var/'+this.ph_ref_6).then(   response => {
                            this.var_ph_ref_6 = response.data; });
            axios.get('/api/var/'+this.temperature).then(   response => {
                            this.var_temperature = response.data; });
            axios.get('/api/var/'+this.distance).then(   response => {
                            this.var_distance= response.data; });
            axios.get('/api/var/'+this.distance_empty).then(   response => {
                            this.var_distance_empty= response.data; });

            this.get_pump(this.ec_pump_1).then(   response => {
                            this.var_ec_pump_1= response;this.pumps.push(this.var_ec_pump_1);  });
            this.get_pump(this.ec_pump_2).then(   response => {
                            this.var_ec_pump_2= response; this.pumps.push(this.var_ec_pump_2); });
            this.get_pump(this.ph_pump).then(   response => {
                            this.var_ph_pump= response; this.pumps.push(this.var_ph_pump); });
            this.get_pump(this.mix_up_pump).then(   response => {
                            this.var_mix_up_pump= response; this.pumps.push(this.var_mix_up_pump); });
            this.get_pump(this.water_in_pump).then(   response => {
                            this.var_water_in_pump= response; this.pumps.push(this.var_water_in_pump); });
             this.get_pump(this.tank_1_in_pump).then(   response => {
                            this.var_tank_1_in_pump =response; this.pumps.push(this.var_tank_1_in_pump); });
             this.get_pump(this.tank_1_out_pump).then(   response => {
                            this.var_tank_1_out_pump=response; this.pumps.push(this.var_tank_1_out_pump); });
                    
        },
    }
</script>
