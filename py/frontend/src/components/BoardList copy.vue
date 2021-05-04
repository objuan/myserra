<template>
  <div>
  
   <h2>Board List</h2>
    <div >
      <Board v-for="(board, index) in boards" :key="index" 
            :name="board.name" />
    </div>
    <h2>Add a New Board</h2>
    <form @submit.prevent="addBoard">
      <textarea v-model="newBoard" placeholder="Board name...">
      </textarea>
      <button class="btn btn-primary" > Add Board</button>

      <b-button>Button</b-button>
    </form>
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
