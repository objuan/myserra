<template>
    <div>
    <b-card  :header="'SWITCH: '+value.name"  >
            <b-card-text>
                {{value.name}}
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
