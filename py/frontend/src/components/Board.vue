<template>
    <div>
    <b-card  :header="'BOARD: '+board.id+' ' +board.name+'('+board.description+') '+board.cpu_type" 
         style="max-width: 90rem;">
            <b-card-text>
                <table>
                    <tr v-if="!compact">
                        <td>
                             <b-button variant="success" @click="newSwitch()">Add Switch</b-button>
                        </td>
                       
                        <td>
                              <b-form-checkbox
                                v-model="board.enable_cpu"
                                unchecked-value="not_accepted"
                                >
                                Enabled
                                </b-form-checkbox>
                                
                        </td>
                        <td>
                            address win
                         </td>
                        
                         <td><b-form-input  v-model="board.usb_address_usb" placeholder="Address WIN" type="text"></b-form-input>
                         </td>
                         <td>
                            address lx
                         </td>
                         
                         <td><b-form-input  v-model="board.usb_address_lx" placeholder="Address WIN" type="text"></b-form-input>
                         </td>
                         <td>
                              <b-button variant="success" @click="saveBoard()">Set</b-button>
                              
                          </td>
                           <td>
                              <b-button variant="danger" @click="cmdBoard('restart')">Restart</b-button>
                             <b-button variant="danger" @click="cmdBoard('stop')">Stop</b-button>
                               
                          </td>
                    </tr>
                </table>
                <table style="width:100%" border=1>
                    <tr>
                        <td  v-if="!compact"></td>
                        <td>ID</td>
                        <td>name</td>
                        <td  v-if="!compact">desc</td>
                        <td>pin</td>
                        <td  v-if="!compact">type</td>
                        <td>state</td>
                        <td></td>
                        <td></td>
                    </tr>
                    <tr v-for="(sw, index) in switch_list" :key="index">
                        <td  v-if="!compact"> <b-button variant="danger" @click="deleteSwitch(sw)">X</b-button></td>
                       <td>{{sw.id}}</td>
                       <td>
                         <b-form-input  v-model="sw.name" placeholder="Enter  name" type="text"></b-form-input>
                       </td>
                       <td  v-if="!compact">
                             <b-form-input  v-model="sw.description" placeholder="Enter  desc" type="text"></b-form-input>
                       </td>
                       <td>
                            <b-form-input  v-model="sw.pin" placeholder="Enter  PIN" type="number"></b-form-input>
                       </td>
                      
                       <td  v-if="!compact">
                              <b-dropdown :text="sw.switchType.name" class="m-md-2" >
                                <b-dropdown-item  @click="onSelectType(sw,s)" v-for="(s, index) in switch_type_list" :key="index" 
                                        >{{s.name}}</b-dropdown-item>
                                </b-dropdown>
                       </td>
                       <td class="static">
                              <p style="width: 8rem;" v-bind:class="{ 'bg-success': sw.state=='open', 'bg-danger':  sw.state!='open'} ">
                            {{sw.state}}({{sw.pin_value}})
                            </p>
                            </td>
                       <td>
                            <b-button variant="success" @click="saveSwitch(sw)">Save</b-button>
                       </td>
                       <td>
                             <b-button v-if="sw.switchType.mode=='O'" variant="success" @click="manualSwitch(sw)">Manual Switch</b-button>
                      
                           
                       </td>
                    </tr>
                </table>
            </b-card-text>
        </b-card>
         <VarList :board="board" :compact="compact"/>
    </div>
</template>

<script>
    import axios from 'axios';
    import Vue from 'vue'
    import VarList from './VarList.vue'

    export default {
        name: "Board",
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
                VarList
        },
        data() {
            return {
                switch_list: [],
                switch_type_list: [],
                selected_switch : {},
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
                    var self=this;
                    var ws = new WebSocket('ws://' + window.location.host  + '/ws/switch/');
                    
                    ws.onmessage = function(e) {
                        //console.log( "board", e.data);
                        var sw = JSON.parse(e.data);
                        //console.log( e.data,o);
                        if (sw.type=="sw")
                        {
                            console.log( e.data);
                            let idx = self.switch_list.findIndex((x) => x.id === sw.id) ;
                             console.log(  self.switch_list[idx].name);
                            self.switch_list[idx].state = sw.state;
                            self.switch_list[idx].pin_value = sw.pin_value;
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
                this.connect_event();

                axios.get('/api/board_switchs/'+this.board.id).then(
                    response => {
                    this.switch_list = response.data;
                    this.selected_switch = this.switch_list[0];
                    }
                );
              axios.get('/api/switchType/').then(
                    response => {
                         this.switch_type_list = response.data;
                    }
                );
            },
            cmdBoard: function(cmd) {
                   console.log ("cmd"  );
                   axios.get('/api/board/'+this.board.id+"/cmd/"+cmd);
                
            },
           saveBoard: function() {
                   console.log ("save"  );
                   axios.put('/api/board/'+this.board.id, this.board);
                
            },
           newSwitch: function() {
                    console.log ("new"  );
                    this.new_switch ={"name":"default"}    ;
                    axios.post('/api/board_switchs/'+this.board.id, this.new_switch)
                     .then(
                        () => {
                            this.new_switch = "";
                          //  this.boards.push(response.data);
                        }
                    );
            },
            deleteSwitch: function(sw) {
                    console.log ("save" , sw);
                    axios.delete('/api/switch/'+sw.id, sw);
            },
            saveSwitch: function(sw) {
                    console.log ("save" , sw);
                    axios.put('/api/switch/'+sw.id, sw);
            },
            manualSwitch: function(value) {
                //console.log(value);
                     axios.get('/api/switch/'+value.id+"/cmd/toggle").then(
                        response => 
                    {
                        let idx = this.switch_list.findIndex((x) => x.id === value.id) ;
                        Vue.set(this.switch_list,idx,  response.data);
                        console.log(idx,response.data);
                    }
             );
               // selected_switch = value;
            },
            onSelectType: function(sw,sw_type) {
                    console.log ("select" , sw,sw_type);
                let idx = this.switch_list.findIndex((x) => x.id === sw.id) ;
                this.switch_list[idx].switchType = sw_type;
                Vue.set(this.switch_list[idx].switchType,sw_type);
            },
        },
        created() {
        
        },
    }
</script>
