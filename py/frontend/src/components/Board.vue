<template>
    <div>
    <b-card  :header="'BOARD: '+board.name+'('+board.name+') '+board.cpu_type+' ' + board.usb_address" 
         style="max-width: 90rem;">
            <b-card-text>
                
                <table style="width:100%" border=1>
                    <tr>
                        <td>ID</td>
                        <td>name</td>
                        <td>desc</td>
                        <td>pin</td>
                        <td>onHi</td>
                        <td>type</td>
                        <td>state</td>
                        <td></td>
                        <td></td>
                    </tr>
                    <tr v-for="(sw, index) in switch_list" :key="index">
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
                         <b-form-checkbox v-model="sw.on_hi"  >
                                </b-form-checkbox>
                            </td>
                       <td>
                              <b-dropdown :text="sw.switchType.name" class="m-md-2" >
                                <b-dropdown-item  @click="onSelectType(sw,s)" v-for="(s, index) in switch_type_list" :key="index" 
                                        >{{s.name}}</b-dropdown-item>
                                </b-dropdown>
                       </td>
                       <td>{{sw.state}}</td>
                       <td>
                            <b-button variant="success" @click="saveSwitch(sw)">Save</b-button>
                       </td>
                       <td>
                            <b-button variant="success" @click="manualSwitch(sw)">Manual Switch</b-button>
                       </td>
                    </tr>
                </table>
            </b-card-text>
        </b-card>
    </div>
</template>

<script>
    import axios from 'axios';
    import Vue from 'vue'

    export default {
        name: "Board",
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
                switch_list: [],
                switch_type_list: [],
                selected_switch : {},
            };
        },
        methods: {
            load: function() {
                axios.get('/api/switch/').then(
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
            this.load();
        },
    }
</script>
