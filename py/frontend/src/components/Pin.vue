<template>
    <div>
        <table>
            <tr>
                <td>
                    PIN 
                 </td>
                 <td>
                    <b>  {{value.PIN}}</b>
                 </td>
                  <td>
                      {{value.MODE}}
                 </td>
                  <td>
                     Start: {{value.START}}
                 </td>
                 <td width="50px">
                   &nbsp;
                 </td>
                 <td>
                   <b> {{value.NAME}}</b>
                 </td>
                  <td>
                       <b-button  variant="success" @click="load(id,value.PIN)">LOAD</b-button>
    
                 </td>
                 <td>
                       <b-button  variant="success" @click="set(id,value.PIN,0)">LOW</b-button>
    
                 </td>
                  <td>
                       <b-button  variant="success" @click="set(id,value.PIN,1)">HI</b-button>
    
                 </td>
            </tr>
        </table>
   
    </div>
</template>

<script>
    import axios from 'axios';
    export default {
        name: "pin",
        props: {
            id: {
                type: String,
                required: true,
            },
            value: {
                type: Object,
                required: true,
            },
        },
         components: {
        },
          methods: {
            load(id,pin){
            
                axios.post('/api/board_api/', {cmd:"read" , id:id, pin: pin }).then( 
                        res => 
                        {
                            console.log (res)
                        }
                );
            },
            set(id,pin,v){
            
             axios.post('/api/board_api/', {cmd:"write",id:id,pin: pin, val:v});
            }
        },
       
    }
</script>
