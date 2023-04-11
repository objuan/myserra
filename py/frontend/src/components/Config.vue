<template>
  <div>

  <table border=0 style="width:100%">
    <tr valign="top">
      <tr>
    </tr>
  </table>

    <b-card  header="Config" >
            <b-card-text>
                
            </b-card-text>
    </b-card>

    <p style="text-align:left;">
       <!--<vue-json-editor v-model="json" :show-btns="true" :expandedOnStart="true" @json-save="onJsonChange" ></vue-json-editor>-->

      <v-jsoneditor v-model="json" :options="options" :plus="true"  @error="onError" :height="height"></v-jsoneditor>
      <b-button  variant="success" @click="save()">Save</b-button>
              
    </p>
    </div>

</template>

<script>
    import axios from 'axios';
  //  import Vue from 'vue'
   // import VueTimepicker from 'vue2-timepicker'
     //import timedswitch from './TimedSwitch.vue'
    // import lab from './Lab.vue'
   // import GetVarConnection from './common'
    //import vueJsonEditor from 'vue-json-editor'
    import VJsoneditor from 'v-jsoneditor/src/index'

    export default {
        name: "config",
        props: {
           
        },
        
        components: {
          VJsoneditor // vueJsonEditor
               // timedswitch //,lab
        },
        data() {
            return {
                height:"900",
                 options: { mode: 'code' },
                 json: {
                  
                }
            };
        },
       
        methods: {
            loadConfig: function() {
            axios.get('/api/config/').then(
              response => {
                console.log("..",response.data);
                this.json = response.data;
              }
            );
          },
           onJsonChange (value) {
              this.json=value;
              axios.post('/api/config/',  value);
          
          },  
          save () {
             
              axios.post('/api/config/',  this.json);
          
          },
           onError() {
            console.log('error')
          }
        },
       created() {
        this.loadConfig();
        },
    }
</script>

