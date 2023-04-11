<template>
    <div>
    <b-card  :header="'SWITCH: '+value.NAME"  >
            <b-card-text>
                {{value.NAME}}
            </b-card-text>
        </b-card>
    </div>
</template>

<script>
    export default {
        name: "switch",
        props: {
            switch: {
                type: Object,
                required: true,
            },
        },
         components: {
        },
       
    }
</script>
