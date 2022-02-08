<template>
  <div>
  <table border=0 style="width:100%">
    <tr valign="top">
      <tr>
    </tr>
  </table>


    <b-card header="Semenzario" >
            <b-card-text>
                 <table style="width:100%" border=1>
                    <tr>
                        <td>Temperatura</td>
                        <td>{{ this.sensors.temp }} Gradi</td>
                    </tr>
                      <tr>
                        <td>Umidità Aria</td>
                        <td>{{ this.sensors.humidity }} %</td>
                    </tr>
                      <tr>
                        <td>Umidità Mezzo</td>
                        <td>{{ this.sensors.mois }}</td>
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
        name: "semenzario",
        props: {
             sensors: {
                type: Object,
                required: true,
            },
        },
        
        components: {
            
        },
        data() {
             return {
                countDown : 10
            }
        },
       
        watch: {
            sensors: {
                    immediate: true,
                    handler() {
                      //  this.load();
                    }
                }
        },

      mounted(){
         this.load();
        this.countDownTimer()
        },
        methods: {
            load()
            {
                var self=this;
                axios.get('/api/seme/').then(
                    response => {
                        self.sensors = response.data;

                       //console.log("Load",self.data );

                    }
                );
            },
            
            countDownTimer() {
                setTimeout(() => {
                      this.load();
                        this.countDownTimer();
                       
                  }, 10000)
            }
        },

    }
</script>

