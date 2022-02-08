


    //import axios from 'axios';
    //import Vue from 'vue'
    //import VarList from './VarList.vue'
var varMap={}

export function StartVar()
  {
        console.log("--StartVar--");

        //varMap={}

        //var self=this;
        var ws = new WebSocket('ws://' + window.location.host  + '/ws/var/');
        ws.onmessage = function(e) {
            console.log( "var", e.data,varMap);
            var v = JSON.parse(e.data);
            //console.log( "<<",e.data,v);
            //if (sw.type=="var")
            if (varMap[v.id])
            {
                //console.log(v);
                for(var i =0;i<varMap[v.id].length;i++)
                    varMap[v.id][i](v);
               // let idx = self.var_list.findIndex((x) => x.id === sw.id) ;

              //  console.log("var", idx, self.var_list, e.data);
               // if (idx!=-1)
                //    self.var_list[idx].value = sw.value;
            }
        };

        ws.onclose = function() {
            console.error("ws onclose");
            setTimeout(function() {
                StartVar();
            }, 1000);
        };

        ws.onerror = function() {
            console.error("ws error");
            ws.close();
        };
    }

    export   function RegisterVar(var_id,onMessage)
    {
      //  console.log("register var ",var_id,onMessage);

        if (!varMap[var_id])
        {
            varMap[var_id]= new Array();
        }
        varMap[var_id].push(onMessage);

    }


    var swMap={}

export function StartSwitch()
  {
        console.log("--StartSwitch--");

       // swMap={}

        //var self=this;
        var ws = new WebSocket('ws://' + window.location.host  + '/ws/switch/');
        ws.onmessage = function(e) {
            console.log( "sw", e.data);
            var v = JSON.parse(e.data);
            //console.log( "<<",e.data,v);
            //if (sw.type=="var")
            if (swMap[v.id])
            {
                //console.log(v);
                for(var i =0;i<swMap[v.id].length;i++)
                    swMap[v.id][i](v);
            }
        };

        ws.onclose = function() {
            console.error("ws onclose");
            setTimeout(function() {
                StartSwitch();
            }, 1000);
        };

        ws.onerror = function() {
            console.error("ws onerror");
            ws.close();
        };
    }

    export   function RegisterSwitch(sw_id,onMessage)
    {
       // console.log("register switch ",sw_id,onMessage);

        if (!swMap[sw_id])
        {
            swMap[sw_id]= new Array();
        }
        swMap[sw_id].push(onMessage);

    }

