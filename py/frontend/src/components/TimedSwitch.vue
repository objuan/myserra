<template>
    <div>
                <table v-if="sw_switch" border="1" width="100%">
                    <tr>
                         <td>
                             <b> {{sw_switch.name}}  </b>
                        </td>
                        <td>
                            Elettrovalvola 
                        </td>
                        <td v-bind:class="[sw_switch.state=='open' ? openClass : closeClass]">
                            {{sw_switch.state}}({{sw_switch.pin_value}})
                        </td>
                         <td colspan="3">
                              <b-button variant="success" @click="manualSwitch(sw_switch)">Manual Switch</b-button>
                        </td>
                    </tr>
                    <tr v-if="scheduling  && var_enable" >
                        <td>
                            <i>Scheduling </i>
                        </td>
                         <td :title="JSON.stringify(scheduling)">
                           <b-button  variant="success" @click="toggle(var_enable)" >Toggle</b-button>
                           <div v-bind:class="[var_enable.value=='True' ? openClass : closeClass]">
                               {{var_enable.value=="True" ? "Enabled" : "Disabled"}}  
                          </div>
                        </td>
                        <td>
                            Da
                        </td>
                        <td>
                             <vue-timepicker v-model="da" format="HH:mm"></vue-timepicker>
                        </td>
                        <td>
                            A
                        </td>
                        <td>
                             <vue-timepicker v-model="a" format="HH:mm"></vue-timepicker>
                        </td>

                       
                        <td>
                              <b-button variant="success" @click="save()" :title="JSON.stringify(scheduling)">Save</b-button>
                        </td>

                    </tr>
                   
                </table>
            
    </div>
</template>

<script>
    import axios from 'axios';
    import Vue from 'vue'
    import VueTimepicker from 'vue2-timepicker'
    import 'vue2-timepicker/dist/VueTimepicker.css'
   // import GetVarConnection from './common'
   import {RegisterVar,RegisterSwitch} from './common'

    export default {
        name: "timedswitch",
        props: ['vswitch','venable','vscheduler']
           
        ,
        
        components: {
                VueTimepicker 
        },
        data() {
            return {
                 openClass: 'text-success',
                 closeClass: 'text-danger',
                 sw_switch : null,
                 var_scheduling:null,
                 var_enable : null,
                 scheduling : null,
                   da: {    HH: '10',   mm: '05' },
                   a : {    HH: '20',   mm: '08' },
            };
        },
       
        methods: {
             manualSwitch: function(value) {
                //console.log(value);
                     axios.get('/api/switch/'+value.id+"/cmd/toggle").then(
                        response => 
                    {
                       
                        Vue.set(this.sw_switch,  response.data);
                        console.log("switch",response.data);
                    }
             );
             },
              toggle: function(v) {

                axios.get('/api/var/'+v.id+'/cmd/TOGGLE');

            },
            save: function() {
                console.log("save");
                  this.scheduling.da = this.da;
                  this.scheduling.a = this.a;
                  this.var_scheduling.value = this.scheduling;
                  axios.put('/api/var/'+this.var_scheduling.id, this.var_scheduling);
             },
              connect_event: function() {
                    var self=this;
                    RegisterSwitch(this.vswitch, function(sw) {
                        self.sw_switch = sw;
                    });

            },
            connect_var: function() {
                var self=this;
                RegisterVar(this.venable, function(v) {
                     self.var_abilitato = v;
                });
                   
            },

            

        },
        created() {
           this.connect_event();
            this.connect_var();

                axios.get('/api/switch/'+this.vswitch).then(
                    response => {
                        this.sw_switch = response.data;
                    }
                );
                  axios.get('/api/var/'+this.venable).then(
                    response => {
                        this.var_abilitato = response.data;
                    }
                );
                var self=this;
                axios.get('/api/var/'+this.vscheduler).then(
                    response => {
                        self.var_scheduling = response.data;
                        if ( this.var_scheduling.value!="")
                        {
                            var a =self.var_scheduling.value.replaceAll('\'',"\"");
                            console.log(a);
                            try{
                                self.scheduling= JSON.parse( a);
                                self.da = self.scheduling.da;
                                self.a = self.scheduling.a;
                            } catch(e) {
                                alert(e); // error in the above string (in this case, yes)!
                                self.scheduling = {};
                            }
                        }
                        else{
                             self.scheduling = {};
                        }
                    }
                );
        },
    }
</script>
