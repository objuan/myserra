<template>
  <div>
  
   <b-card 
    title="Board List"
    class="mb-2"
  >
    <b-card-text>
     
     <b-tabs content-class="mt-3">
        <b-tab v-for="(board, index) in boards" :key="index"  :title="board.name" >
          <Board :board="board" />
        </b-tab>
    </b-tabs>
    </b-card-text>
  </b-card>

  </div>
</template>

<script>
//import HelloWorld from './components/HelloWorld.vue'
import Board from './Board.vue'
import axios from 'axios';

export default {
  name: 'BoardList',
  components: {
   // HelloWorld,
    Board
  },
  data() {
    return {
      boards: [],
      newBoard: "",
    };
  },
  methods: {
     loadBoards: function() {
      axios.get('/api/board/').then(
        response => {
          this.boards = response.data;
        }
      );
    },
    addBoard: function() {
      axios.post('/api/board/', {name: this.newBoard}).then(
        response => {
          this.newBoard = "";
          this.boards.push(response.data);
        }
      );
    }
  },
  created() {
    this.loadBoards();
  },
}
</script>
