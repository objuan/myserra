<template>
  <div>
  <h2>Log</h2>
  <table border=1 style="width:100%">

                    <tr>
                        <td>time</td>
                        <td>name</td>
                        <td>level</td>
                        <td>message</td>
                      
                    </tr>
                    <tr v-for="(msg, index) in messages" :key="index">
                        <td>{{msg.time}}</td>
                        <td>{{msg.name}}</td>
                        <td>{{msg.level}}</td>
                        <td>{{msg.message}}</td>
                  </tr> 
  </table>

 
  </div>
</template>

<script>

//import axios from 'axios';




export default {
  name: 'Log',
  components: {

  },
  data() {
    return {
      messages: [],
    };
  },
  methods: {
  
    connect_log: function() {
      var ws = new WebSocket('ws://'
                + window.location.host
                + '/ws/log/');

      var self=this;

      ws.onopen =  function() {
        // subscribe to some channels
        ws.send(JSON.stringify({
            //.... some message the I must send when I connect ....
        }));
      };

      ws.onmessage = function(e) {
        console.log( e.data);
        var msg = JSON.parse(e.data);
        console.log( self,msg);
        self.messages.push(msg)
      };

      ws.onclose = function(e) {
        console.log('Socket is closed. Reconnect will be attempted in 1 second.', e.reason);
        setTimeout(function() {
          self.connect_log();
        }, 1000);
      };

      ws.onerror = function(err) {
        console.error('Socket encountered error: ', err.message, 'Closing socket');
        ws.close();
      };
    }
  },
  created() {
    
    this.connect_log();
  },
}
</script>
