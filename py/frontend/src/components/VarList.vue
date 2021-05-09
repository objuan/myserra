<template>
    <div>
    <b-card  :header="'VAR: '+board.id+' ' +board.name+'('+board.description+') '+board.cpu_type" 
         style="max-width: 90rem;">
            <b-card-text>
                <table style="width:100%" border=1>
                    <tr>
                        <td></td>
                        <td>ID</td>
                        <td>name</td>
                        <td>desc</td>
                        <td>pin</td>
                        <td>type</td>
                        <td>value</td>
                    
                    </tr>
                    <tr v-for="(sw, index) in var_list" :key="index">
                        <td> 
                         
                            <b-button v-if="sw.varType=='btn_toggle'" variant="success" @click="toggle(sw)">Toggle</b-button>
                        </td>
                       <td>{{sw.id}}</td>
                       <td>
                         <b-form-input  v-model="sw.name" placeholder="Enter  name" type="text"></b-form-input>
                       </td>
                       <td>
                             <b-form-input  v-model="sw.description" placeholder="Enter  desc" type="text"></b-form-input>
                       </td>
                       <td>
                            <b-form-input  v-model="sw.pin" placeholder="Enter  PIN" type="number"></b-form-input>
                       </td>
                      
                       <td>
                         
                              <b-dropdown :text="sw.varType" class="m-md-2" >
                                <b-dropdown-item  v-for="(s, index) in var_type_list" :key="index" 
                                        >{{s}}</b-dropdown-item>
                                </b-dropdown>
                       </td>
                       <td class="static">
                              <p  >
                            {{sw.value}}
                            </p>
                         </td>
                      
                    </tr>
                </table>
            </b-card-text>
        </b-card>
    </div>
</template>

<script>
    import axios from 'axios';
    //import Vue from 'vue'


    export default {
        name: "Vars",
        props: {
            board: {
                type: Object,
                required: true,
            },
        },
        
        components: {
                
        },
        data() {
            return {
                var_list: [],
                var_type_list : ['bool','real','int','string']
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
              connect_event: function() {
                    var ws = new WebSocket('ws://' + window.location.host  + '/ws/var/');
                    var self=this;
                    
                    ws.onmessage = function(e) {
                        console.log( "var", e.data);
                        var sw = JSON.parse(e.data);
                        //console.log( e.data,o);
                        if (sw.type=="var")
                        {
                            console.log( e.data);
                            let idx = self.var_list.findIndex((x) => x.id === sw.id) ;
                            self.var_list[idx].value = sw.value;
                        }
                    };

                    ws.onclose = function() {
                        setTimeout(function() {
                        self.connect_event();
                        }, 1000);
                    };

                    ws.onerror = function() {
                        ws.close();
                    };
            },

            load: function() {
                //console.log(this.board);
                axios.get('/api/board/'+this.board.id+"/vars").then(
                    response => {
                    this.var_list = response.data;
                    }
                );
            
            },

            toggle: function(v) {
                console.log(this.board);
                axios.get('/api/var/'+v.id+'/cmd/TOGGLE');

            },
        },
        created() {
          this.connect_event();
        },
    }
</script>
