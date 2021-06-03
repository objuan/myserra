<template>
<div>

    <b-tabs content-class="mt-3">
        <b-tab title="Monitor" active><p>I'm the first tab</p></b-tab>
        <b-tab title="Settings">
            <div v-if="lab_board">
            <Board :board="lab_board" :compact="true"/>
            </div>
        </b-tab>
    
  </b-tabs>


 </div>
</template>

<script>
    import axios from 'axios';
    import Board from './Board.vue'
   // import GetVarConnection from './common'

    export default {
        name: "lab",
        props: ['ec','ec_k','ph','ph_volt','ph_ref_4','ph_ref_6','temperature','distance','distance_empty'],
        
        components: {
            Board
        },
        data() {
            return {
                 openClass: 'text-success',
                 closeClass: 'text-danger',
        
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
            };
        },
     
        methods: {
             
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

        },
    }
</script>
