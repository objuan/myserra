<template>
<div>
    <table witdh="100%"  v-if="var_ph && var_temperature && var_distance_empty && var_distance">
                <tr>
                    <td>
                        <b>PH </b>
                    </td>
                    <td>
                       {{var_ph.value}}
                    </td>
                     <td>
                         <b>EC </b>
                    </td>
                    <td>
                       {{var_ec.value}}
                    </td>
                      <td>
                         <b>Temperature </b>
                    </td>
                    <td>
                       {{var_temperature.value}}
                    </td>
                      <td>
                         <b>Litres </b>
                    </td>
                    <td>
                       {{litres()}} /  {{totalLitres()}} ({{fillPencent()}}%)
                    </td>
                </tr>
              </table>
        
        <b-tabs content-class="mt-3">
            <b-tab title="Monitor" active>
              
              <table witdh="100%"  v-if="var_ec_pump_1_weight">
                <tr>
                    <td>
                        <b>EC A</b> PUMP Weight
                    </td>
                    <td>
                       {{var_ec_pump_1_weight.value}}
                    </td>
                    <td>
                        Litres
                    </td>
                </tr>
              </table>
              <hr/>
              <table width="100%">
                 <tr v-for="(m, index) in log" :key="index" >
                     <td align="left" style="width:160px">
                         {{m.time}}
                    </td>
                     <td  align="left" style="width:100px">
                         {{m.level}}
                    </td>
                     <td align="left">
                         {{m.msg}}
                    </td>
                </tr>
              </table>
        </b-tab>
        <b-tab title="Manual">
            <table width="100%">
                 <tr >
                     <td align="left" style="width:160px">
                        Fill Tank
                    </td>
                     <td>
                         <b-form-select v-model="test_tank.id" :options="['1','2']"></b-form-select>
                    </td>    
                   <td align="left" style="width:160px">
                        Litres
                    </td>
                     <td>
                         <b-form-input  v-model="test_tank.litres" placeholder="litres to get" type="number"></b-form-input>
                    </td>  
                     <td >
                        <b-button variant="primary" @click="fillTank()">Fill</b-button>
                    </td>    
                        
                </tr>
                <tr>
                    <td >
                        <b-button variant="secondary" @click="mixTank()">Mix</b-button>
                    </td>  
                      <td >
                        <b-button variant="danger" @click="emptyTank()">Empty</b-button>
                    </td>   
                </tr>
              </table>
        </b-tab>
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
                                Type
                            </td>
                             <td >
                                 <b-form-select v-model="pump.calib.calibrateType" :options="['TIME','WEIGHT']"></b-form-select>
                            </td>
                          
                             <td  v-if="pump.calib.calibrateType=='TIME'">
                                <b-form-input  v-model="pump.calib.filled_ml" placeholder="Water filled" type="number"></b-form-input>
                            </td>
                           
                             <td  v-if="pump.calib.calibrateType=='TIME'">
                                Ml Per Secs {{pump.calib.ml_at_seconds}}
                            </td>
                            <td  v-if="pump.weight && pump.calib.calibrateType=='WEIGHT'">
                               Weight {{pump.weight.value}}
                            </td>

                             <td  v-if="pump.calib.calibrateType=='WEIGHT'">
                                start:{{pump.calib.filled_gr_start}}   end: {{pump.calib.filled_gr_end}}
                            </td>
                
                             <td  v-if="pump.calib.calibrateType=='WEIGHT'">
                                Gr Per Secs {{pump.calib.gr_at_seconds}}
                            </td>
                             <td >
                                  <b-button variant="primary" @click="savePump(pump)">Save</b-button>
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
     import {RegisterVar} from './common'
   // import App from '../App.vue';

   // import GetVarConnection from './common'

    export default {
        name: "lab",
        props: ['ec','ec_k','ph','ph_volt','ph_ref_4','ph_ref_6','temperature','distance','distance_empty'
        ,'ec_pump_1','ec_pump_1_weight','ec_pump_2','ph_pump','mix_up_pump','water_in_pump','tank_1_in_pump','tank_1_out_pump'],
        
        components: {
            Board,
               // App,
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
                 var_ec_pump_1_weight : null,

                  var_ec_pump_1:null,
                  var_ec_pump_2:null,
                  var_ph_pump:null,
                  var_mix_up_pump:null,
                  var_water_in_pump:null,
                  var_tank_1_in_pump:null,
                  var_tank_1_out_pump:null,

                  pumps: [],
                  vars: [],
                  log: [],

                  LAB_BASE_AREA : 29*31 //uguale al python

                  ,test_tank:{ id:1 , litres : 5,mix_secs : 30}
                  
            };
        },
     
        methods: {
            totalLitres: function() {
                return (this.var_distance_empty.value * this.LAB_BASE_AREA) / 1000;
             },
            litres: function() {
                return this.totalLitres() - (this.var_distance.value * this.LAB_BASE_AREA) / 1000
             },
             fillPencent: function() {
                return 100.0 * (this.litres() / this.totalLitres())
             },
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
            fillTank: function() {
                axios.post('/api/lab/fill_tank',  this.test_tank);
             },
             emptyTank: function() {
                axios.post('/api/lab/empty_tank',  this.test_tank);
             },
            mixTank: function() {
                axios.post('/api/lab/mix_tank',  this.test_tank);
             },
            get_pump(id){
                return new Promise((resolve) => {
        
                   axios.get('/api/switch/'+id).then(   response => {
                        var sw = response.data
                        axios.get('/api/switch/'+id+"/calibrate").then(   response => {
                            sw.calib = response.data;

                            console.log("sw " , sw)
                            sw.calib_test_ml=60
                            resolve(sw);
                         }).catch(err => {
                              console.log(err) ;
                               resolve(response.data)
                              });

                        
                       
                   });
                })

             
            },
            get_var(v){
                return new Promise((resolve) => {
                    var self=this;
                   axios.get('/api/var/'+v).then(   response => {
                        var sw = response.data;
                        RegisterVar(sw.id, function(v) {
                                    //console.log( "var", e.data);
                                  
                                   // console.log(v);
                                    let idx = self.vars.findIndex((x) => x.id === v.id) ;

                                   // console.log("var", idx, self.vars,v);
                                     if (idx!=-1)
                                       self.vars[idx].value = v.value;
                                });

                       resolve(sw)
                       
                   });
                })

             
            },
            lablog_event: function() {
                var ws = new WebSocket('ws://' + window.location.host  + '/ws/lablog/');

                var self=this;

                ws.onopen = function(e) {
                    console.log("Socket open",e);
                
                };
                ws.onmessage = function(e) {
                    console.log( e.data);
                    var a =e.data.replaceAll('\'',"\"");
                    var o = JSON.parse(a);
                    self.log.push(o);
                    if (self.log.length> 20)
                        self.log.remove(0);

                };

                ws.onclose = function(e) {
                    console.log('Socket is closed. Reconnect will be attempted in 1 second.', e.reason);
                    setTimeout(function() {
                    self.lablog_event();
                    }, 1000);
                };

                ws.onerror = function(err) {
                    console.error('Socket encountered error: ', err.message, 'Closing socket');
                    ws.close();
                };
            }

        },
        created() {

            //this.connect_var();
            this.lablog_event();

            axios.get('/api/board/7').then(
                response => {
                this.lab_board = response.data;
                }
            );

          
           this. get_var(this.ec).then(   response => {
                this.var_ec = response; });

            this.get_var(this.ec_k).then(   response => {
                this.var_ec_k = response;  this.vars.push(this.ec_k); });
            this.get_var(this.ph).then(   response => {
                            this.var_ph= response;  this.vars.push(this.ph); });
            this.get_var(this.ph_volt).then(   response => {
                            this.var_ph_volt = response;  this.vars.push(this.ph_volt); });
            this.get_var(this.ph_ref_4).then(   response => {
                            this.var_ph_ref_4 = response; this.vars.push(this.ph_ref_4);  });
            this.get_var(this.ph_ref_6).then(   response => {
                            this.var_ph_ref_6 = response; this.vars.push(this.ph_ref_6);  });
            this.get_var(this.temperature).then(   response => {
                            this.var_temperature = response; this.vars.push(this.temperature);  });
            this.get_var(this.distance).then(   response => {
                            this.var_distance= response; this.vars.push(this.var_distance); });
            this.get_var(this.distance_empty).then(   response => {
                            this.var_distance_empty= response; this.vars.push(this.var_distance_empty);});

          
            this.get_pump(this.ec_pump_1).then(   response => {
                            this.var_ec_pump_1= response;this.pumps.push(this.var_ec_pump_1); 

                            this.get_var(this.ec_pump_1_weight).then(   response => {
                                console.log(" this.var_ec_pump_1", this.var_ec_pump_1)
                                this.var_ec_pump_1_weight= response;
                                this.vars.push(this.var_ec_pump_1_weight);
                                 this.var_ec_pump_1.weight = this.var_ec_pump_1_weight
                            });
             });
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
