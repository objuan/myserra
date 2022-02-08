<template>
    <div>
    <b-card  :header="'VAR: '+board.id+' ' +board.name+'('+board.description+') '+board.cpu_type" 
         style="max-width: 90rem;">
            <b-card-text>
                  
              <b-button  v-if="!compact" variant="success" @click="newVar()">Add Var</b-button>
                        
                <table style="width:100%" border=1>
                    <tr>
                        <td v-if="!compact"></td>
                        <td></td>
                        <td>ID</td>
                        <td>name</td>
                        <td v-if="!compact">desc</td>
                        <td>pin</td>
                        <td v-if="!compact">type</td>
                        <td v-if="!compact">save</td>
                        <td v-if="!compact">startup</td>
                        <td>value</td>
                        <td></td>
                    </tr>
                    <tr v-for="(sw, index) in var_list" :key="index">
                        <td v-if="!compact">
                            
                             <b-button :v-b-modal="'modal-1'" variant="danger" >X</b-button>
                             
                           
                            <b-modal :id="'modal-'+sw.id" title="BootstrapVue">
                                <p class="my-4">Hello from modal!</p>
                            </b-modal>
                            </td>
                        <td> 
                         
                            <b-button v-if="sw.varType=='btn_toggle'" variant="success" @click="toggle(sw)">Toggle</b-button>
                        </td>
                       <td>{{sw.id}}</td>
                       <td>
                           <div  v-if="!compact">
                            <b-form-input  v-model="sw.name" placeholder="Enter  name" type="text"></b-form-input>
                          </div>
                           <div  v-if="compact">
                           {{sw.name}}
                          </div>
                       </td>
                       <td v-if="!compact">
                             <b-form-input  v-model="sw.description" placeholder="Enter  desc" type="text"></b-form-input>
                       </td>
                       <td>
                           <div  v-if="!compact">
                            <b-form-input  v-model="sw.pin" placeholder="Enter  PIN" type="number"></b-form-input>
                         </div>
                           <div  v-if="compact">
                           {{sw.pin}}
                          </div>
                       </td>
                      
                       <td v-if="!compact">
                         
                           <b-dropdown :text="sw.varType" class="m-md-2" >
                                <b-dropdown-item  @click="onSelectType(sw,s)" v-for="(s, index) in var_type_list" :key="index" 
                                        >{{s}}</b-dropdown-item>
                                </b-dropdown>
                       </td>
                        <td v-if="!compact">
                         
                              <b-dropdown :text="sw.saveMode" class="m-md-2" >
                                <b-dropdown-item   @click="onSelectSavewMode(sw,s)"  v-for="(s, index) in var_saveMode_list" :key="index" 
                                        >{{s}}</b-dropdown-item>
                                </b-dropdown>
                       </td>
                         <td v-if="!compact">
                            <b-dropdown :text="sw.startupMode" class="m-md-2" >
                                <b-dropdown-item   @click="onSelectStartupMode(sw,s)"  v-for="(s, index) in var_startup_list" :key="index" 
                                        >{{s}}</b-dropdown-item>
                                </b-dropdown>
                       </td>
                       <td class="static">
                              <p  >
                          
                             <b-form-input  v-model="sw.value" placeholder="Enter  desc" type="text"></b-form-input>
                            </p>
                         </td>
                      <td>
                            <b-button variant="success" @click="saveVar(sw)">Save</b-button>
                
                          </td>
                    </tr>
                </table>
            </b-card-text>
        </b-card>
    </div>
</template>

<script>
    import axios from 'axios';
     import {RegisterVar} from './common'
    //import Vue from 'vue'
  

    export default {
        name: "Vars",
        props: {
            board: {
                type: Object,
                required: true,
            },
             compact: {
                type: Boolean,
                required: false,
                default : false
            },
        },
        
        components: {
                
        },
        data() {
            return {
                var_list: [],
                var_type_list : ['text_bool','text_int','text_real','text_string','btn_toggle','json'],
                 var_saveMode_list : ['','0','10','30','60','600','3600'],
                   var_startup_list : ['','db','hw']
            };
        },

        watch: {
            board: {
                    immediate: true,
                    handler() {
                        if (this.board.id)
                            this.load();
                    }
                }
        },
        methods: {
            
            load: function() {
               
                var self=this;
                //console.log(this.board);
                axios.get('/api/board/'+this.board.id+"/vars").then(
                    response => {
                       
                         this.var_list = response.data;
                         //console.log("vars",this.var_list )
                         for(var i=0;i<this.var_list.length;i++)
                         {
                              RegisterVar(this.var_list[i].id, function(v) {
                                    //console.log( "var", e.data);
                                  
                                    //console.log(v);
                                    let idx = self.var_list.findIndex((x) => x.id === v.id) ;

                                    //console.log("var", idx, self.var_list,v);
                                     if (idx!=-1)
                                       self.var_list[idx].value = v.value;
                                });

                         }
                    }
                );
            
            },

            newVar: function() {
                    console.log ("new"  );
                    this.new_var ={"name":"default"}    ;
                    axios.post('/api/board/'+this.board.id+"/vars", this.new_var)
                     .then(
                        () => {
                            this.new_var = "";
                        }
                    );
            },
            deleteVar: function(sw) {
                    console.log ("save" , sw);
                    axios.delete('/api/var/'+sw.id, sw);
            },
            saveVar: function(sw) {
                    console.log ("save" , sw);
                    axios.put('/api/var/'+sw.id, sw);
            },

            toggle: function(v) {
                console.log(this.board);
                axios.get('/api/var/'+v.id+'/cmd/TOGGLE');

            },
            onSelectType: function(sw,sw_type) {
                console.log ("select" , sw,sw_type);
                let idx = this.var_list.findIndex((x) => x.id === sw.id) ;
                console.log (this.var_list,idx);
                this.var_list[idx].varType = sw_type;
               // Vue.set(this.var_list[idx].varType,sw_type);
            },
            onSelectSavewMode: function(sw,sw_type) {
                console.log ("select" , sw,sw_type);
                let idx = this.var_list.findIndex((x) => x.id === sw.id) ;
                console.log (this.var_list,idx);
                this.var_list[idx].saveMode = sw_type;
               // Vue.set(this.var_list[idx].varType,sw_type);
            },
              onSelectStartupMode: function(sw,sw_type) {
                console.log ("select" , sw,sw_type);
                let idx = this.var_list.findIndex((x) => x.id === sw.id) ;
                console.log (this.var_list,idx);
                this.var_list[idx].startupMode = sw_type;
               // Vue.set(this.var_list[idx].varType,sw_type);
            },
        },
        created() {
        //  this.connect_event();
        },
    }
</script>
