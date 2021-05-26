

<script>
    import axios from 'axios';
    import Vue from 'vue'
    import VarList from './VarList.vue'

    
    function GetVarConnection(onMessage)
    {
        /*
      return function(onMessage) {
          self=this;
          self.onMessage=onMessage;

                    var ws = new WebSocket('ws://' + window.location.host  + '/ws/var/');
                    
                    ws.onmessage = function(e) {
                        var sw = JSON.parse(e.data);
                        self.onMessage(sw);
                    };

                    ws.onclose = function() {
                        setTimeout(function() {
                        self.connect_event();
                        }, 1000);
                    };

                    ws.onerror = function() {
                        ws.close();
                    };
            };
            */
    }
export default GetVarConnection
</script>