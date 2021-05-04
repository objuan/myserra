<template>
  <div>
  <h2>Centralina</h2>
  <table border=1 style="width:100%">
    <tr valign="top">
        <td style="width:100px">
            <b-dropdown id="dropdown-1" :text="selected_board.name" class="m-md-2" style="width:100px">
              <b-dropdown-item @click="onSelectBoard(board)" v-for="(board, index) in boards" :key="index" 
                      >{{board.name}}</b-dropdown-item>
            </b-dropdown>
        </td>
        <td>
            <Board :board="selected_board" />
       </td>
    </tr>
  </table>

  </div>
</template>

<script>
//import HelloWorld from './components/HelloWorld.vue'
//import BoardList from './BoardList.vue'
import axios from 'axios';
import Board from './Board.vue';

export default {
  name: 'Centralina',
  components: {
   // HelloWorld,
  //  BoardList,
    Board
  },
  data() {
    return {
      boards: [],
      selected_board : {},
      newBoard: "",
    };
  },
  methods: {
     loadBoards: function() {
      axios.get('/api/board/').then(
        response => {
          this.boards = response.data;
          this.selected_board = this.boards[0];
        }
      );
    },
    onSelectBoard: function(board) {
      this.selected_board = board;
    }
  },
  created() {
    this.loadBoards();
  },
}
</script>
