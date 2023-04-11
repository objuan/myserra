<template>
  <div>

  <table border=0 style="width:100%">
    <tr valign="top">
      <tr>
    </tr>
  </table>

    <b-card  header="Board Test" >
             <b-card-text>
     
          <b-tabs content-class="mt-3">
              <b-tab v-for="(board, index) in this.board_config" :key="index"  :title="board.ID" >
                 <table witdh="100%">
                        <tr v-for="(pin, idx1) in board['PINS']" :key="idx1" >
                          <td>
                              <Pin :id="board.ID" :value="pin"></Pin>
                            </td>
                        </tr>
                  </table>
                  
              </b-tab>
          </b-tabs>
          </b-card-text>
    </b-card>

   
    
  </div>

</template>

<script>
    import axios from 'axios';
    import Pin from './Pin.vue'

    export default {
        name: "board_test",
        props: {
           
        },
        
        components: {
          Pin
        },
        data() {
            return {
                 board_config: {  }
            };
        },
       
        methods: {
            loadConfig: function() {
            axios.get('/api/config/').then(
              response => {
             //   console.log("..",response.data);
                this.board_config = response.data;
              }
            );
           
          },
       
            getPins(idx){
            
              return this.board_config[idx]["PINS"];
            }
        },
       created() {
          this.loadConfig();
        },
    }
</script>

