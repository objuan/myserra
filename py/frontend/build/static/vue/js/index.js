/******/ (function(modules) { // webpackBootstrap
/******/ 	// install a JSONP callback for chunk loading
/******/ 	function webpackJsonpCallback(data) {
/******/ 		var chunkIds = data[0];
/******/ 		var moreModules = data[1];
/******/ 		var executeModules = data[2];
/******/
/******/ 		// add "moreModules" to the modules object,
/******/ 		// then flag all "chunkIds" as loaded and fire callback
/******/ 		var moduleId, chunkId, i = 0, resolves = [];
/******/ 		for(;i < chunkIds.length; i++) {
/******/ 			chunkId = chunkIds[i];
/******/ 			if(Object.prototype.hasOwnProperty.call(installedChunks, chunkId) && installedChunks[chunkId]) {
/******/ 				resolves.push(installedChunks[chunkId][0]);
/******/ 			}
/******/ 			installedChunks[chunkId] = 0;
/******/ 		}
/******/ 		for(moduleId in moreModules) {
/******/ 			if(Object.prototype.hasOwnProperty.call(moreModules, moduleId)) {
/******/ 				modules[moduleId] = moreModules[moduleId];
/******/ 			}
/******/ 		}
/******/ 		if(parentJsonpFunction) parentJsonpFunction(data);
/******/
/******/ 		while(resolves.length) {
/******/ 			resolves.shift()();
/******/ 		}
/******/
/******/ 		// add entry modules from loaded chunk to deferred list
/******/ 		deferredModules.push.apply(deferredModules, executeModules || []);
/******/
/******/ 		// run deferred modules when all chunks ready
/******/ 		return checkDeferredModules();
/******/ 	};
/******/ 	function checkDeferredModules() {
/******/ 		var result;
/******/ 		for(var i = 0; i < deferredModules.length; i++) {
/******/ 			var deferredModule = deferredModules[i];
/******/ 			var fulfilled = true;
/******/ 			for(var j = 1; j < deferredModule.length; j++) {
/******/ 				var depId = deferredModule[j];
/******/ 				if(installedChunks[depId] !== 0) fulfilled = false;
/******/ 			}
/******/ 			if(fulfilled) {
/******/ 				deferredModules.splice(i--, 1);
/******/ 				result = __webpack_require__(__webpack_require__.s = deferredModule[0]);
/******/ 			}
/******/ 		}
/******/
/******/ 		return result;
/******/ 	}
/******/
/******/ 	// The module cache
/******/ 	var installedModules = {};
/******/
/******/ 	// object to store loaded and loading chunks
/******/ 	// undefined = chunk not loaded, null = chunk preloaded/prefetched
/******/ 	// Promise = chunk loading, 0 = chunk loaded
/******/ 	var installedChunks = {
/******/ 		"index": 0
/******/ 	};
/******/
/******/ 	var deferredModules = [];
/******/
/******/ 	// The require function
/******/ 	function __webpack_require__(moduleId) {
/******/
/******/ 		// Check if module is in cache
/******/ 		if(installedModules[moduleId]) {
/******/ 			return installedModules[moduleId].exports;
/******/ 		}
/******/ 		// Create a new module (and put it into the cache)
/******/ 		var module = installedModules[moduleId] = {
/******/ 			i: moduleId,
/******/ 			l: false,
/******/ 			exports: {}
/******/ 		};
/******/
/******/ 		// Execute the module function
/******/ 		modules[moduleId].call(module.exports, module, module.exports, __webpack_require__);
/******/
/******/ 		// Flag the module as loaded
/******/ 		module.l = true;
/******/
/******/ 		// Return the exports of the module
/******/ 		return module.exports;
/******/ 	}
/******/
/******/
/******/ 	// expose the modules object (__webpack_modules__)
/******/ 	__webpack_require__.m = modules;
/******/
/******/ 	// expose the module cache
/******/ 	__webpack_require__.c = installedModules;
/******/
/******/ 	// define getter function for harmony exports
/******/ 	__webpack_require__.d = function(exports, name, getter) {
/******/ 		if(!__webpack_require__.o(exports, name)) {
/******/ 			Object.defineProperty(exports, name, { enumerable: true, get: getter });
/******/ 		}
/******/ 	};
/******/
/******/ 	// define __esModule on exports
/******/ 	__webpack_require__.r = function(exports) {
/******/ 		if(typeof Symbol !== 'undefined' && Symbol.toStringTag) {
/******/ 			Object.defineProperty(exports, Symbol.toStringTag, { value: 'Module' });
/******/ 		}
/******/ 		Object.defineProperty(exports, '__esModule', { value: true });
/******/ 	};
/******/
/******/ 	// create a fake namespace object
/******/ 	// mode & 1: value is a module id, require it
/******/ 	// mode & 2: merge all properties of value into the ns
/******/ 	// mode & 4: return value when already ns object
/******/ 	// mode & 8|1: behave like require
/******/ 	__webpack_require__.t = function(value, mode) {
/******/ 		if(mode & 1) value = __webpack_require__(value);
/******/ 		if(mode & 8) return value;
/******/ 		if((mode & 4) && typeof value === 'object' && value && value.__esModule) return value;
/******/ 		var ns = Object.create(null);
/******/ 		__webpack_require__.r(ns);
/******/ 		Object.defineProperty(ns, 'default', { enumerable: true, value: value });
/******/ 		if(mode & 2 && typeof value != 'string') for(var key in value) __webpack_require__.d(ns, key, function(key) { return value[key]; }.bind(null, key));
/******/ 		return ns;
/******/ 	};
/******/
/******/ 	// getDefaultExport function for compatibility with non-harmony modules
/******/ 	__webpack_require__.n = function(module) {
/******/ 		var getter = module && module.__esModule ?
/******/ 			function getDefault() { return module['default']; } :
/******/ 			function getModuleExports() { return module; };
/******/ 		__webpack_require__.d(getter, 'a', getter);
/******/ 		return getter;
/******/ 	};
/******/
/******/ 	// Object.prototype.hasOwnProperty.call
/******/ 	__webpack_require__.o = function(object, property) { return Object.prototype.hasOwnProperty.call(object, property); };
/******/
/******/ 	// __webpack_public_path__
/******/ 	__webpack_require__.p = "/static/vue/";
/******/
/******/ 	var jsonpArray = window["webpackJsonp"] = window["webpackJsonp"] || [];
/******/ 	var oldJsonpFunction = jsonpArray.push.bind(jsonpArray);
/******/ 	jsonpArray.push = webpackJsonpCallback;
/******/ 	jsonpArray = jsonpArray.slice();
/******/ 	for(var i = 0; i < jsonpArray.length; i++) webpackJsonpCallback(jsonpArray[i]);
/******/ 	var parentJsonpFunction = oldJsonpFunction;
/******/
/******/
/******/ 	// add entry module to deferred list
/******/ 	deferredModules.push([0,"chunk-vendors"]);
/******/ 	// run deferred modules when ready
/******/ 	return checkDeferredModules();
/******/ })
/************************************************************************/
/******/ ({

/***/ "./node_modules/cache-loader/dist/cjs.js?!./node_modules/babel-loader/lib/index.js!./node_modules/cache-loader/dist/cjs.js?!./node_modules/vue-loader/lib/index.js?!./src/App.vue?vue&type=script&lang=js&":
/*!*************************************************************************************************************************************************************************************************************************************!*\
  !*** ./node_modules/cache-loader/dist/cjs.js??ref--12-0!./node_modules/babel-loader/lib!./node_modules/cache-loader/dist/cjs.js??ref--0-0!./node_modules/vue-loader/lib??vue-loader-options!./src/App.vue?vue&type=script&lang=js& ***!
  \*************************************************************************************************************************************************************************************************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
eval("__webpack_require__.r(__webpack_exports__);\n/* harmony import */ var vue__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! vue */ \"./node_modules/vue/dist/vue.runtime.esm.js\");\n/* harmony import */ var bootstrap_vue__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! bootstrap-vue */ \"./node_modules/bootstrap-vue/esm/index.js\");\n/* harmony import */ var bootstrap_dist_css_bootstrap_css__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! bootstrap/dist/css/bootstrap.css */ \"./node_modules/bootstrap/dist/css/bootstrap.css\");\n/* harmony import */ var bootstrap_dist_css_bootstrap_css__WEBPACK_IMPORTED_MODULE_2___default = /*#__PURE__*/__webpack_require__.n(bootstrap_dist_css_bootstrap_css__WEBPACK_IMPORTED_MODULE_2__);\n/* harmony import */ var bootstrap_vue_dist_bootstrap_vue_css__WEBPACK_IMPORTED_MODULE_3__ = __webpack_require__(/*! bootstrap-vue/dist/bootstrap-vue.css */ \"./node_modules/bootstrap-vue/dist/bootstrap-vue.css\");\n/* harmony import */ var bootstrap_vue_dist_bootstrap_vue_css__WEBPACK_IMPORTED_MODULE_3___default = /*#__PURE__*/__webpack_require__.n(bootstrap_vue_dist_bootstrap_vue_css__WEBPACK_IMPORTED_MODULE_3__);\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//import HelloWorld from './components/HelloWorld.vue'\n//import BoardList from './components/BoardList.vue'\n\n // Import Bootstrap an BootstrapVue CSS files (order is important)\n\n\n //import Log from './components/Log.vue'\n// Make BootstrapVue available throughout your project\n\nvue__WEBPACK_IMPORTED_MODULE_0__[\"default\"].use(bootstrap_vue__WEBPACK_IMPORTED_MODULE_1__[\"BootstrapVue\"]); // Optionally install the BootstrapVue icon components plugin\n\nvue__WEBPACK_IMPORTED_MODULE_0__[\"default\"].use(bootstrap_vue__WEBPACK_IMPORTED_MODULE_1__[\"IconsPlugin\"]);\n/* harmony default export */ __webpack_exports__[\"default\"] = ({\n  name: 'App',\n  components: {//  Log\n  },\n  data: function data() {\n    return {\n      board_state: \"............\"\n    };\n  },\n  methods: {\n    connect_event: function connect_event() {\n      var ws = new WebSocket('ws://' + window.location.host + '/ws/event/');\n      var self = this;\n\n      ws.onopen = function (e) {\n        console.log(\"Socket open\", e);\n      };\n\n      ws.onmessage = function (e) {\n        //console.log( e.data);\n        var o = JSON.parse(e.data); //console.log( e.data,o);\n\n        if (o.type == \"connect\") self.board_state = o.msg;\n      };\n\n      ws.onclose = function (e) {\n        console.log('Socket is closed. Reconnect will be attempted in 1 second.', e.reason);\n        setTimeout(function () {\n          self.connect_event();\n        }, 1000);\n      };\n\n      ws.onerror = function (err) {\n        console.error('Socket encountered error: ', err.message, 'Closing socket');\n        ws.close();\n      };\n    }\n  },\n  created: function created() {\n    this.connect_event();\n  }\n}); // =======\n\n//# sourceURL=webpack:///./src/App.vue?./node_modules/cache-loader/dist/cjs.js??ref--12-0!./node_modules/babel-loader/lib!./node_modules/cache-loader/dist/cjs.js??ref--0-0!./node_modules/vue-loader/lib??vue-loader-options");

/***/ }),

/***/ "./node_modules/cache-loader/dist/cjs.js?!./node_modules/babel-loader/lib/index.js!./node_modules/cache-loader/dist/cjs.js?!./node_modules/vue-loader/lib/index.js?!./src/components/Board.vue?vue&type=script&lang=js&":
/*!**************************************************************************************************************************************************************************************************************************************************!*\
  !*** ./node_modules/cache-loader/dist/cjs.js??ref--12-0!./node_modules/babel-loader/lib!./node_modules/cache-loader/dist/cjs.js??ref--0-0!./node_modules/vue-loader/lib??vue-loader-options!./src/components/Board.vue?vue&type=script&lang=js& ***!
  \**************************************************************************************************************************************************************************************************************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
eval("__webpack_require__.r(__webpack_exports__);\n/* harmony import */ var core_js_modules_es_array_find_index_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! core-js/modules/es.array.find-index.js */ \"./node_modules/core-js/modules/es.array.find-index.js\");\n/* harmony import */ var core_js_modules_es_array_find_index_js__WEBPACK_IMPORTED_MODULE_0___default = /*#__PURE__*/__webpack_require__.n(core_js_modules_es_array_find_index_js__WEBPACK_IMPORTED_MODULE_0__);\n/* harmony import */ var axios__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! axios */ \"./node_modules/axios/index.js\");\n/* harmony import */ var axios__WEBPACK_IMPORTED_MODULE_1___default = /*#__PURE__*/__webpack_require__.n(axios__WEBPACK_IMPORTED_MODULE_1__);\n/* harmony import */ var vue__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! vue */ \"./node_modules/vue/dist/vue.runtime.esm.js\");\n\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n\n\n/* harmony default export */ __webpack_exports__[\"default\"] = ({\n  name: \"Board\",\n  props: {\n    board: {\n      type: Object,\n      required: true\n    }\n  },\n  components: {},\n  data: function data() {\n    return {\n      switch_list: [],\n      switch_type_list: [],\n      selected_switch: {}\n    };\n  },\n  watch: {\n    board: {\n      immediate: true,\n      handler: function handler() {\n        if (this.board.id) this.load();\n      }\n    }\n  },\n  methods: {\n    connect_event: function connect_event() {\n      var ws = new WebSocket('ws://' + window.location.host + '/ws/event/');\n      var self = this;\n\n      ws.onmessage = function (e) {\n        //console.log( \"board\", e.data);\n        var sw = JSON.parse(e.data); //console.log( e.data,o);\n\n        if (sw.type == \"sw\") {\n          console.log(e.data);\n          var idx = self.switch_list.findIndex(function (x) {\n            return x.id === sw.id;\n          });\n          self.switch_list[idx].state = sw.state;\n          self.switch_list[idx].pin_value = sw.pin_value;\n        }\n      };\n\n      ws.onclose = function () {\n        setTimeout(function () {\n          self.connect_event();\n        }, 1000);\n      };\n\n      ws.onerror = function () {\n        ws.close();\n      };\n    },\n    load: function load() {\n      var _this = this;\n\n      //console.log(this.board);\n      axios__WEBPACK_IMPORTED_MODULE_1___default.a.get('/api/board_switchs/' + this.board.id).then(function (response) {\n        _this.switch_list = response.data;\n        _this.selected_switch = _this.switch_list[0];\n      });\n      axios__WEBPACK_IMPORTED_MODULE_1___default.a.get('/api/switchType/').then(function (response) {\n        _this.switch_type_list = response.data;\n      });\n    },\n    cmdBoard: function cmdBoard(cmd) {\n      console.log(\"cmd\");\n      axios__WEBPACK_IMPORTED_MODULE_1___default.a.get('/api/board/' + this.board.id + \"/cmd/\" + cmd);\n    },\n    saveBoard: function saveBoard() {\n      console.log(\"save\");\n      axios__WEBPACK_IMPORTED_MODULE_1___default.a.put('/api/board/' + this.board.id, this.board);\n    },\n    newSwitch: function newSwitch() {\n      var _this2 = this;\n\n      console.log(\"new\");\n      this.new_switch = {\n        \"name\": \"default\"\n      };\n      axios__WEBPACK_IMPORTED_MODULE_1___default.a.post('/api/board_switchs/' + this.board.id, this.new_switch).then(function () {\n        _this2.new_switch = \"\"; //  this.boards.push(response.data);\n      });\n    },\n    deleteSwitch: function deleteSwitch(sw) {\n      console.log(\"save\", sw);\n      axios__WEBPACK_IMPORTED_MODULE_1___default.a.delete('/api/switch/' + sw.id, sw);\n    },\n    saveSwitch: function saveSwitch(sw) {\n      console.log(\"save\", sw);\n      axios__WEBPACK_IMPORTED_MODULE_1___default.a.put('/api/switch/' + sw.id, sw);\n    },\n    manualSwitch: function manualSwitch(value) {\n      var _this3 = this;\n\n      //console.log(value);\n      axios__WEBPACK_IMPORTED_MODULE_1___default.a.get('/api/switch/' + value.id + \"/cmd/toggle\").then(function (response) {\n        var idx = _this3.switch_list.findIndex(function (x) {\n          return x.id === value.id;\n        });\n\n        vue__WEBPACK_IMPORTED_MODULE_2__[\"default\"].set(_this3.switch_list, idx, response.data);\n        console.log(idx, response.data);\n      }); // selected_switch = value;\n    },\n    onSelectType: function onSelectType(sw, sw_type) {\n      console.log(\"select\", sw, sw_type);\n      var idx = this.switch_list.findIndex(function (x) {\n        return x.id === sw.id;\n      });\n      this.switch_list[idx].switchType = sw_type;\n      vue__WEBPACK_IMPORTED_MODULE_2__[\"default\"].set(this.switch_list[idx].switchType, sw_type);\n    }\n  },\n  created: function created() {\n    this.connect_event();\n  }\n});\n\n//# sourceURL=webpack:///./src/components/Board.vue?./node_modules/cache-loader/dist/cjs.js??ref--12-0!./node_modules/babel-loader/lib!./node_modules/cache-loader/dist/cjs.js??ref--0-0!./node_modules/vue-loader/lib??vue-loader-options");

/***/ }),

/***/ "./node_modules/cache-loader/dist/cjs.js?!./node_modules/babel-loader/lib/index.js!./node_modules/cache-loader/dist/cjs.js?!./node_modules/vue-loader/lib/index.js?!./src/components/BoardList.vue?vue&type=script&lang=js&":
/*!******************************************************************************************************************************************************************************************************************************************************!*\
  !*** ./node_modules/cache-loader/dist/cjs.js??ref--12-0!./node_modules/babel-loader/lib!./node_modules/cache-loader/dist/cjs.js??ref--0-0!./node_modules/vue-loader/lib??vue-loader-options!./src/components/BoardList.vue?vue&type=script&lang=js& ***!
  \******************************************************************************************************************************************************************************************************************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
eval("__webpack_require__.r(__webpack_exports__);\n/* harmony import */ var _Board_vue__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./Board.vue */ \"./src/components/Board.vue\");\n/* harmony import */ var axios__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! axios */ \"./node_modules/axios/index.js\");\n/* harmony import */ var axios__WEBPACK_IMPORTED_MODULE_1___default = /*#__PURE__*/__webpack_require__.n(axios__WEBPACK_IMPORTED_MODULE_1__);\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//import HelloWorld from './components/HelloWorld.vue'\n\n\n/* harmony default export */ __webpack_exports__[\"default\"] = ({\n  name: 'BoardList',\n  components: {\n    // HelloWorld,\n    Board: _Board_vue__WEBPACK_IMPORTED_MODULE_0__[\"default\"]\n  },\n  data: function data() {\n    return {\n      boards: [],\n      newBoard: \"\"\n    };\n  },\n  methods: {\n    loadBoards: function loadBoards() {\n      var _this = this;\n\n      axios__WEBPACK_IMPORTED_MODULE_1___default.a.get('/api/board/').then(function (response) {\n        _this.boards = response.data;\n      });\n    },\n    addBoard: function addBoard() {\n      var _this2 = this;\n\n      axios__WEBPACK_IMPORTED_MODULE_1___default.a.post('/api/board/', {\n        name: this.newBoard\n      }).then(function (response) {\n        _this2.newBoard = \"\";\n\n        _this2.boards.push(response.data);\n      });\n    }\n  },\n  created: function created() {\n    this.loadBoards();\n  }\n});\n\n//# sourceURL=webpack:///./src/components/BoardList.vue?./node_modules/cache-loader/dist/cjs.js??ref--12-0!./node_modules/babel-loader/lib!./node_modules/cache-loader/dist/cjs.js??ref--0-0!./node_modules/vue-loader/lib??vue-loader-options");

/***/ }),

/***/ "./node_modules/cache-loader/dist/cjs.js?!./node_modules/babel-loader/lib/index.js!./node_modules/cache-loader/dist/cjs.js?!./node_modules/vue-loader/lib/index.js?!./src/components/Centralina.vue?vue&type=script&lang=js&":
/*!*******************************************************************************************************************************************************************************************************************************************************!*\
  !*** ./node_modules/cache-loader/dist/cjs.js??ref--12-0!./node_modules/babel-loader/lib!./node_modules/cache-loader/dist/cjs.js??ref--0-0!./node_modules/vue-loader/lib??vue-loader-options!./src/components/Centralina.vue?vue&type=script&lang=js& ***!
  \*******************************************************************************************************************************************************************************************************************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
eval("__webpack_require__.r(__webpack_exports__);\n/* harmony import */ var axios__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! axios */ \"./node_modules/axios/index.js\");\n/* harmony import */ var axios__WEBPACK_IMPORTED_MODULE_0___default = /*#__PURE__*/__webpack_require__.n(axios__WEBPACK_IMPORTED_MODULE_0__);\n/* harmony import */ var _Board_vue__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! ./Board.vue */ \"./src/components/Board.vue\");\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//import HelloWorld from './components/HelloWorld.vue'\n//import BoardList from './BoardList.vue'\n\n\n/* harmony default export */ __webpack_exports__[\"default\"] = ({\n  name: 'Centralina',\n  components: {\n    // HelloWorld,\n    //  BoardList,\n    Board: _Board_vue__WEBPACK_IMPORTED_MODULE_1__[\"default\"]\n  },\n  data: function data() {\n    return {\n      boards: [],\n      selected_board: {},\n      newBoard: \"\"\n    };\n  },\n  methods: {\n    loadBoards: function loadBoards() {\n      var _this = this;\n\n      axios__WEBPACK_IMPORTED_MODULE_0___default.a.get('/api/board/').then(function (response) {\n        _this.boards = response.data;\n        _this.selected_board = _this.boards[0];\n      });\n    },\n    onSelectBoard: function onSelectBoard(board) {\n      this.selected_board = board;\n    }\n  },\n  created: function created() {\n    this.loadBoards();\n  }\n});\n\n//# sourceURL=webpack:///./src/components/Centralina.vue?./node_modules/cache-loader/dist/cjs.js??ref--12-0!./node_modules/babel-loader/lib!./node_modules/cache-loader/dist/cjs.js??ref--0-0!./node_modules/vue-loader/lib??vue-loader-options");

/***/ }),

/***/ "./node_modules/cache-loader/dist/cjs.js?!./node_modules/babel-loader/lib/index.js!./node_modules/cache-loader/dist/cjs.js?!./node_modules/vue-loader/lib/index.js?!./src/components/Log.vue?vue&type=script&lang=js&":
/*!************************************************************************************************************************************************************************************************************************************************!*\
  !*** ./node_modules/cache-loader/dist/cjs.js??ref--12-0!./node_modules/babel-loader/lib!./node_modules/cache-loader/dist/cjs.js??ref--0-0!./node_modules/vue-loader/lib??vue-loader-options!./src/components/Log.vue?vue&type=script&lang=js& ***!
  \************************************************************************************************************************************************************************************************************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
eval("__webpack_require__.r(__webpack_exports__);\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//\n//import axios from 'axios';\n/* harmony default export */ __webpack_exports__[\"default\"] = ({\n  name: 'Log',\n  components: {},\n  data: function data() {\n    return {\n      messages: []\n    };\n  },\n  methods: {\n    connect_log: function connect_log() {\n      var ws = new WebSocket('ws://' + window.location.host + '/ws/log/');\n      var self = this;\n\n      ws.onopen = function () {\n        // subscribe to some channels\n        ws.send(JSON.stringify({//.... some message the I must send when I connect ....\n        }));\n      };\n\n      ws.onmessage = function (e) {\n        console.log(e.data);\n        var msg = JSON.parse(e.data);\n        console.log(self, msg);\n        self.messages.push(msg);\n      };\n\n      ws.onclose = function (e) {\n        console.log('Socket is closed. Reconnect will be attempted in 1 second.', e.reason);\n        setTimeout(function () {\n          self.connect_log();\n        }, 1000);\n      };\n\n      ws.onerror = function (err) {\n        console.error('Socket encountered error: ', err.message, 'Closing socket');\n        ws.close();\n      };\n    }\n  },\n  created: function created() {\n    this.connect_log();\n  }\n});\n\n//# sourceURL=webpack:///./src/components/Log.vue?./node_modules/cache-loader/dist/cjs.js??ref--12-0!./node_modules/babel-loader/lib!./node_modules/cache-loader/dist/cjs.js??ref--0-0!./node_modules/vue-loader/lib??vue-loader-options");

/***/ }),

/***/ "./node_modules/cache-loader/dist/cjs.js?{\"cacheDirectory\":\"node_modules/.cache/vue-loader\",\"cacheIdentifier\":\"200e5b7e-vue-loader-template\"}!./node_modules/vue-loader/lib/loaders/templateLoader.js?!./node_modules/cache-loader/dist/cjs.js?!./node_modules/vue-loader/lib/index.js?!./src/App.vue?vue&type=template&id=7ba5bd90&":
/*!*********************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************!*\
  !*** ./node_modules/cache-loader/dist/cjs.js?{"cacheDirectory":"node_modules/.cache/vue-loader","cacheIdentifier":"200e5b7e-vue-loader-template"}!./node_modules/vue-loader/lib/loaders/templateLoader.js??vue-loader-options!./node_modules/cache-loader/dist/cjs.js??ref--0-0!./node_modules/vue-loader/lib??vue-loader-options!./src/App.vue?vue&type=template&id=7ba5bd90& ***!
  \*********************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/
/*! exports provided: render, staticRenderFns */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
eval("__webpack_require__.r(__webpack_exports__);\n/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, \"render\", function() { return render; });\n/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, \"staticRenderFns\", function() { return staticRenderFns; });\nvar render = function() {\n  var _vm = this\n  var _h = _vm.$createElement\n  var _c = _vm._self._c || _h\n  return _c(\n    \"div\",\n    { attrs: { id: \"app\" } },\n    [\n      _c(\n        \"b-navbar\",\n        { attrs: { toggleable: \"lg\", type: \"dark\", variant: \"info\" } },\n        [\n          _c(\"b-navbar-brand\", { attrs: { href: \"#\" } }, [_vm._v(\"MySerra\")]),\n          _c(\"span\", { staticClass: \"btn-success\" }, [\n            _vm._v(\" State: \" + _vm._s(_vm.board_state) + \" \")\n          ]),\n          _c(\"b-navbar-toggle\", { attrs: { target: \"nav-collapse\" } }),\n          _c(\n            \"b-collapse\",\n            { attrs: { id: \"nav-collapse\", \"is-nav\": \"\" } },\n            [\n              _c(\n                \"b-nav\",\n                { attrs: { \"card-header\": \"\", tabs: \"\" } },\n                [\n                  _c(\n                    \"b-nav-item\",\n                    {\n                      attrs: {\n                        to: \"/centralina\",\n                        exact: \"\",\n                        \"exact-active-class\": \"active\"\n                      }\n                    },\n                    [_vm._v(\"Centralina\")]\n                  ),\n                  _c(\n                    \"b-nav-item\",\n                    {\n                      attrs: {\n                        to: \"/boardlist\",\n                        exact: \"\",\n                        \"exact-active-class\": \"active\"\n                      }\n                    },\n                    [_vm._v(\"Boards\")]\n                  ),\n                  _c(\n                    \"b-nav-item\",\n                    {\n                      attrs: {\n                        to: \"/log\",\n                        exact: \"\",\n                        \"exact-active-class\": \"active\"\n                      }\n                    },\n                    [_vm._v(\"Log \")]\n                  ),\n                  _c(\n                    \"b-nav-item\",\n                    {\n                      attrs: {\n                        to: \"/admin/\",\n                        exact: \"\",\n                        \"exact-active-class\": \"active\"\n                      }\n                    },\n                    [_vm._v(\"Admin \")]\n                  )\n                ],\n                1\n              ),\n              _c(\n                \"b-navbar-nav\",\n                { staticClass: \"ml-auto\" },\n                [\n                  _c(\n                    \"b-nav-form\",\n                    [\n                      _c(\"b-form-input\", {\n                        staticClass: \"mr-sm-2\",\n                        attrs: { size: \"sm\", placeholder: \"Search\" }\n                      }),\n                      _c(\n                        \"b-button\",\n                        {\n                          staticClass: \"my-2 my-sm-0\",\n                          attrs: { size: \"sm\", type: \"submit\" }\n                        },\n                        [_vm._v(\"Search\")]\n                      )\n                    ],\n                    1\n                  ),\n                  _c(\n                    \"b-nav-item-dropdown\",\n                    {\n                      attrs: { right: \"\" },\n                      scopedSlots: _vm._u([\n                        {\n                          key: \"button-content\",\n                          fn: function() {\n                            return [_c(\"em\", [_vm._v(\"User\")])]\n                          },\n                          proxy: true\n                        }\n                      ])\n                    },\n                    [\n                      _c(\"b-dropdown-item\", { attrs: { href: \"#\" } }, [\n                        _vm._v(\"Profile\")\n                      ]),\n                      _c(\"b-dropdown-item\", { attrs: { href: \"#\" } }, [\n                        _vm._v(\"Sign Out\")\n                      ])\n                    ],\n                    1\n                  )\n                ],\n                1\n              )\n            ],\n            1\n          )\n        ],\n        1\n      ),\n      _c(\"router-view\")\n    ],\n    1\n  )\n}\nvar staticRenderFns = []\nrender._withStripped = true\n\n\n\n//# sourceURL=webpack:///./src/App.vue?./node_modules/cache-loader/dist/cjs.js?%7B%22cacheDirectory%22:%22node_modules/.cache/vue-loader%22,%22cacheIdentifier%22:%22200e5b7e-vue-loader-template%22%7D!./node_modules/vue-loader/lib/loaders/templateLoader.js??vue-loader-options!./node_modules/cache-loader/dist/cjs.js??ref--0-0!./node_modules/vue-loader/lib??vue-loader-options");

/***/ }),

/***/ "./node_modules/cache-loader/dist/cjs.js?{\"cacheDirectory\":\"node_modules/.cache/vue-loader\",\"cacheIdentifier\":\"200e5b7e-vue-loader-template\"}!./node_modules/vue-loader/lib/loaders/templateLoader.js?!./node_modules/cache-loader/dist/cjs.js?!./node_modules/vue-loader/lib/index.js?!./src/components/Board.vue?vue&type=template&id=e1ee1034&":
/*!**********************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************!*\
  !*** ./node_modules/cache-loader/dist/cjs.js?{"cacheDirectory":"node_modules/.cache/vue-loader","cacheIdentifier":"200e5b7e-vue-loader-template"}!./node_modules/vue-loader/lib/loaders/templateLoader.js??vue-loader-options!./node_modules/cache-loader/dist/cjs.js??ref--0-0!./node_modules/vue-loader/lib??vue-loader-options!./src/components/Board.vue?vue&type=template&id=e1ee1034& ***!
  \**********************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/
/*! exports provided: render, staticRenderFns */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
eval("__webpack_require__.r(__webpack_exports__);\n/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, \"render\", function() { return render; });\n/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, \"staticRenderFns\", function() { return staticRenderFns; });\nvar render = function() {\n  var _vm = this\n  var _h = _vm.$createElement\n  var _c = _vm._self._c || _h\n  return _c(\n    \"div\",\n    [\n      _c(\n        \"b-card\",\n        {\n          staticStyle: { \"max-width\": \"90rem\" },\n          attrs: {\n            header:\n              \"BOARD: \" +\n              _vm.board.id +\n              \" \" +\n              _vm.board.name +\n              \"(\" +\n              _vm.board.description +\n              \") \" +\n              _vm.board.cpu_type\n          }\n        },\n        [\n          _c(\"b-card-text\", [\n            _c(\"table\", [\n              _c(\"tr\", [\n                _c(\n                  \"td\",\n                  [\n                    _c(\n                      \"b-button\",\n                      {\n                        attrs: { variant: \"success\" },\n                        on: {\n                          click: function($event) {\n                            return _vm.newSwitch()\n                          }\n                        }\n                      },\n                      [_vm._v(\"Add Switch\")]\n                    )\n                  ],\n                  1\n                ),\n                _c(\"td\", [_vm._v(\" address \")]),\n                _c(\n                  \"td\",\n                  [\n                    _c(\"b-form-input\", {\n                      attrs: { placeholder: \"Address\", type: \"text\" },\n                      model: {\n                        value: _vm.board.usb_address,\n                        callback: function($$v) {\n                          _vm.$set(_vm.board, \"usb_address\", $$v)\n                        },\n                        expression: \"board.usb_address\"\n                      }\n                    })\n                  ],\n                  1\n                ),\n                _c(\n                  \"td\",\n                  [\n                    _c(\n                      \"b-button\",\n                      {\n                        attrs: { variant: \"success\" },\n                        on: {\n                          click: function($event) {\n                            return _vm.saveBoard()\n                          }\n                        }\n                      },\n                      [_vm._v(\"Set\")]\n                    )\n                  ],\n                  1\n                ),\n                _c(\n                  \"td\",\n                  [\n                    _c(\n                      \"b-button\",\n                      {\n                        attrs: { variant: \"danger\" },\n                        on: {\n                          click: function($event) {\n                            return _vm.cmdBoard(\"restart\")\n                          }\n                        }\n                      },\n                      [_vm._v(\"Restart\")]\n                    ),\n                    _c(\n                      \"b-button\",\n                      {\n                        attrs: { variant: \"danger\" },\n                        on: {\n                          click: function($event) {\n                            return _vm.cmdBoard(\"stop\")\n                          }\n                        }\n                      },\n                      [_vm._v(\"Stop\")]\n                    )\n                  ],\n                  1\n                )\n              ])\n            ]),\n            _c(\n              \"table\",\n              { staticStyle: { width: \"100%\" }, attrs: { border: \"1\" } },\n              [\n                _c(\"tr\", [\n                  _c(\"td\"),\n                  _c(\"td\", [_vm._v(\"ID\")]),\n                  _c(\"td\", [_vm._v(\"name\")]),\n                  _c(\"td\", [_vm._v(\"desc\")]),\n                  _c(\"td\", [_vm._v(\"pin\")]),\n                  _c(\"td\", [_vm._v(\"type\")]),\n                  _c(\"td\", [_vm._v(\"state\")]),\n                  _c(\"td\"),\n                  _c(\"td\")\n                ]),\n                _vm._l(_vm.switch_list, function(sw, index) {\n                  return _c(\"tr\", { key: index }, [\n                    _c(\n                      \"td\",\n                      [\n                        _c(\n                          \"b-button\",\n                          {\n                            attrs: { variant: \"danger\" },\n                            on: {\n                              click: function($event) {\n                                return _vm.deleteSwitch(sw)\n                              }\n                            }\n                          },\n                          [_vm._v(\"X\")]\n                        )\n                      ],\n                      1\n                    ),\n                    _c(\"td\", [_vm._v(_vm._s(sw.id))]),\n                    _c(\n                      \"td\",\n                      [\n                        _c(\"b-form-input\", {\n                          attrs: { placeholder: \"Enter  name\", type: \"text\" },\n                          model: {\n                            value: sw.name,\n                            callback: function($$v) {\n                              _vm.$set(sw, \"name\", $$v)\n                            },\n                            expression: \"sw.name\"\n                          }\n                        })\n                      ],\n                      1\n                    ),\n                    _c(\n                      \"td\",\n                      [\n                        _c(\"b-form-input\", {\n                          attrs: { placeholder: \"Enter  desc\", type: \"text\" },\n                          model: {\n                            value: sw.description,\n                            callback: function($$v) {\n                              _vm.$set(sw, \"description\", $$v)\n                            },\n                            expression: \"sw.description\"\n                          }\n                        })\n                      ],\n                      1\n                    ),\n                    _c(\n                      \"td\",\n                      [\n                        _c(\"b-form-input\", {\n                          attrs: { placeholder: \"Enter  PIN\", type: \"number\" },\n                          model: {\n                            value: sw.pin,\n                            callback: function($$v) {\n                              _vm.$set(sw, \"pin\", $$v)\n                            },\n                            expression: \"sw.pin\"\n                          }\n                        })\n                      ],\n                      1\n                    ),\n                    _c(\n                      \"td\",\n                      [\n                        _c(\n                          \"b-dropdown\",\n                          {\n                            staticClass: \"m-md-2\",\n                            attrs: { text: sw.switchType.name }\n                          },\n                          _vm._l(_vm.switch_type_list, function(s, index) {\n                            return _c(\n                              \"b-dropdown-item\",\n                              {\n                                key: index,\n                                on: {\n                                  click: function($event) {\n                                    return _vm.onSelectType(sw, s)\n                                  }\n                                }\n                              },\n                              [_vm._v(_vm._s(s.name))]\n                            )\n                          }),\n                          1\n                        )\n                      ],\n                      1\n                    ),\n                    _c(\"td\", { staticClass: \"static\" }, [\n                      _c(\n                        \"p\",\n                        {\n                          class: {\n                            \"bg-success\": sw.state == \"open\",\n                            \"bg-danger\": sw.state != \"open\"\n                          },\n                          staticStyle: { width: \"8rem\" }\n                        },\n                        [\n                          _vm._v(\n                            \" \" +\n                              _vm._s(sw.state) +\n                              \"(\" +\n                              _vm._s(sw.pin_value) +\n                              \") \"\n                          )\n                        ]\n                      )\n                    ]),\n                    _c(\n                      \"td\",\n                      [\n                        _c(\n                          \"b-button\",\n                          {\n                            attrs: { variant: \"success\" },\n                            on: {\n                              click: function($event) {\n                                return _vm.saveSwitch(sw)\n                              }\n                            }\n                          },\n                          [_vm._v(\"Save\")]\n                        )\n                      ],\n                      1\n                    ),\n                    _c(\n                      \"td\",\n                      [\n                        sw.switchType.mode == \"O\"\n                          ? _c(\n                              \"b-button\",\n                              {\n                                attrs: { variant: \"success\" },\n                                on: {\n                                  click: function($event) {\n                                    return _vm.manualSwitch(sw)\n                                  }\n                                }\n                              },\n                              [_vm._v(\"Manual Switch\")]\n                            )\n                          : _vm._e()\n                      ],\n                      1\n                    )\n                  ])\n                })\n              ],\n              2\n            )\n          ])\n        ],\n        1\n      )\n    ],\n    1\n  )\n}\nvar staticRenderFns = []\nrender._withStripped = true\n\n\n\n//# sourceURL=webpack:///./src/components/Board.vue?./node_modules/cache-loader/dist/cjs.js?%7B%22cacheDirectory%22:%22node_modules/.cache/vue-loader%22,%22cacheIdentifier%22:%22200e5b7e-vue-loader-template%22%7D!./node_modules/vue-loader/lib/loaders/templateLoader.js??vue-loader-options!./node_modules/cache-loader/dist/cjs.js??ref--0-0!./node_modules/vue-loader/lib??vue-loader-options");

/***/ }),

/***/ "./node_modules/cache-loader/dist/cjs.js?{\"cacheDirectory\":\"node_modules/.cache/vue-loader\",\"cacheIdentifier\":\"200e5b7e-vue-loader-template\"}!./node_modules/vue-loader/lib/loaders/templateLoader.js?!./node_modules/cache-loader/dist/cjs.js?!./node_modules/vue-loader/lib/index.js?!./src/components/BoardList.vue?vue&type=template&id=2add92b8&":
/*!**************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************!*\
  !*** ./node_modules/cache-loader/dist/cjs.js?{"cacheDirectory":"node_modules/.cache/vue-loader","cacheIdentifier":"200e5b7e-vue-loader-template"}!./node_modules/vue-loader/lib/loaders/templateLoader.js??vue-loader-options!./node_modules/cache-loader/dist/cjs.js??ref--0-0!./node_modules/vue-loader/lib??vue-loader-options!./src/components/BoardList.vue?vue&type=template&id=2add92b8& ***!
  \**************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/
/*! exports provided: render, staticRenderFns */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
eval("__webpack_require__.r(__webpack_exports__);\n/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, \"render\", function() { return render; });\n/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, \"staticRenderFns\", function() { return staticRenderFns; });\nvar render = function() {\n  var _vm = this\n  var _h = _vm.$createElement\n  var _c = _vm._self._c || _h\n  return _c(\n    \"div\",\n    [\n      _c(\n        \"b-card\",\n        {\n          staticClass: \"mb-2\",\n          staticStyle: { \"max-width\": \"20rem\" },\n          attrs: { title: \"Board List\" }\n        },\n        [\n          _c(\"b-card-text\", [\n            _c(\n              \"div\",\n              _vm._l(_vm.boards, function(board, index) {\n                return _c(\"Board\", { key: index, attrs: { board: board } })\n              }),\n              1\n            )\n          ])\n        ],\n        1\n      )\n    ],\n    1\n  )\n}\nvar staticRenderFns = []\nrender._withStripped = true\n\n\n\n//# sourceURL=webpack:///./src/components/BoardList.vue?./node_modules/cache-loader/dist/cjs.js?%7B%22cacheDirectory%22:%22node_modules/.cache/vue-loader%22,%22cacheIdentifier%22:%22200e5b7e-vue-loader-template%22%7D!./node_modules/vue-loader/lib/loaders/templateLoader.js??vue-loader-options!./node_modules/cache-loader/dist/cjs.js??ref--0-0!./node_modules/vue-loader/lib??vue-loader-options");

/***/ }),

/***/ "./node_modules/cache-loader/dist/cjs.js?{\"cacheDirectory\":\"node_modules/.cache/vue-loader\",\"cacheIdentifier\":\"200e5b7e-vue-loader-template\"}!./node_modules/vue-loader/lib/loaders/templateLoader.js?!./node_modules/cache-loader/dist/cjs.js?!./node_modules/vue-loader/lib/index.js?!./src/components/Centralina.vue?vue&type=template&id=2adb58f7&":
/*!***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************!*\
  !*** ./node_modules/cache-loader/dist/cjs.js?{"cacheDirectory":"node_modules/.cache/vue-loader","cacheIdentifier":"200e5b7e-vue-loader-template"}!./node_modules/vue-loader/lib/loaders/templateLoader.js??vue-loader-options!./node_modules/cache-loader/dist/cjs.js??ref--0-0!./node_modules/vue-loader/lib??vue-loader-options!./src/components/Centralina.vue?vue&type=template&id=2adb58f7& ***!
  \***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/
/*! exports provided: render, staticRenderFns */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
eval("__webpack_require__.r(__webpack_exports__);\n/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, \"render\", function() { return render; });\n/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, \"staticRenderFns\", function() { return staticRenderFns; });\nvar render = function() {\n  var _vm = this\n  var _h = _vm.$createElement\n  var _c = _vm._self._c || _h\n  return _c(\"div\", [\n    _c(\"h2\", [_vm._v(\"Centralina\")]),\n    _c(\"table\", { staticStyle: { width: \"100%\" }, attrs: { border: \"1\" } }, [\n      _c(\"tr\", { attrs: { valign: \"top\" } }, [\n        _c(\n          \"td\",\n          { staticStyle: { width: \"100px\" } },\n          [\n            _c(\n              \"b-dropdown\",\n              {\n                staticClass: \"m-md-2\",\n                staticStyle: { width: \"100px\" },\n                attrs: { id: \"dropdown-1\", text: _vm.selected_board.name }\n              },\n              _vm._l(_vm.boards, function(board, index) {\n                return _c(\n                  \"b-dropdown-item\",\n                  {\n                    key: index,\n                    on: {\n                      click: function($event) {\n                        return _vm.onSelectBoard(board)\n                      }\n                    }\n                  },\n                  [_vm._v(_vm._s(board.name))]\n                )\n              }),\n              1\n            )\n          ],\n          1\n        ),\n        _c(\"td\", [_c(\"Board\", { attrs: { board: _vm.selected_board } })], 1)\n      ])\n    ])\n  ])\n}\nvar staticRenderFns = []\nrender._withStripped = true\n\n\n\n//# sourceURL=webpack:///./src/components/Centralina.vue?./node_modules/cache-loader/dist/cjs.js?%7B%22cacheDirectory%22:%22node_modules/.cache/vue-loader%22,%22cacheIdentifier%22:%22200e5b7e-vue-loader-template%22%7D!./node_modules/vue-loader/lib/loaders/templateLoader.js??vue-loader-options!./node_modules/cache-loader/dist/cjs.js??ref--0-0!./node_modules/vue-loader/lib??vue-loader-options");

/***/ }),

/***/ "./node_modules/cache-loader/dist/cjs.js?{\"cacheDirectory\":\"node_modules/.cache/vue-loader\",\"cacheIdentifier\":\"200e5b7e-vue-loader-template\"}!./node_modules/vue-loader/lib/loaders/templateLoader.js?!./node_modules/cache-loader/dist/cjs.js?!./node_modules/vue-loader/lib/index.js?!./src/components/Log.vue?vue&type=template&id=12f38744&":
/*!********************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************!*\
  !*** ./node_modules/cache-loader/dist/cjs.js?{"cacheDirectory":"node_modules/.cache/vue-loader","cacheIdentifier":"200e5b7e-vue-loader-template"}!./node_modules/vue-loader/lib/loaders/templateLoader.js??vue-loader-options!./node_modules/cache-loader/dist/cjs.js??ref--0-0!./node_modules/vue-loader/lib??vue-loader-options!./src/components/Log.vue?vue&type=template&id=12f38744& ***!
  \********************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/
/*! exports provided: render, staticRenderFns */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
eval("__webpack_require__.r(__webpack_exports__);\n/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, \"render\", function() { return render; });\n/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, \"staticRenderFns\", function() { return staticRenderFns; });\nvar render = function() {\n  var _vm = this\n  var _h = _vm.$createElement\n  var _c = _vm._self._c || _h\n  return _c(\"div\", [\n    _c(\"h2\", [_vm._v(\"Log\")]),\n    _c(\n      \"table\",\n      { staticStyle: { width: \"100%\" }, attrs: { border: \"1\" } },\n      [\n        _vm._m(0),\n        _vm._l(_vm.messages, function(msg, index) {\n          return _c(\"tr\", { key: index }, [\n            _c(\"td\", [_vm._v(_vm._s(msg.time))]),\n            _c(\"td\", [_vm._v(_vm._s(msg.name))]),\n            _c(\"td\", [_vm._v(_vm._s(msg.level))]),\n            _c(\"td\", [_vm._v(_vm._s(msg.message))])\n          ])\n        })\n      ],\n      2\n    )\n  ])\n}\nvar staticRenderFns = [\n  function() {\n    var _vm = this\n    var _h = _vm.$createElement\n    var _c = _vm._self._c || _h\n    return _c(\"tr\", [\n      _c(\"td\", [_vm._v(\"time\")]),\n      _c(\"td\", [_vm._v(\"name\")]),\n      _c(\"td\", [_vm._v(\"level\")]),\n      _c(\"td\", [_vm._v(\"message\")])\n    ])\n  }\n]\nrender._withStripped = true\n\n\n\n//# sourceURL=webpack:///./src/components/Log.vue?./node_modules/cache-loader/dist/cjs.js?%7B%22cacheDirectory%22:%22node_modules/.cache/vue-loader%22,%22cacheIdentifier%22:%22200e5b7e-vue-loader-template%22%7D!./node_modules/vue-loader/lib/loaders/templateLoader.js??vue-loader-options!./node_modules/cache-loader/dist/cjs.js??ref--0-0!./node_modules/vue-loader/lib??vue-loader-options");

/***/ }),

/***/ "./node_modules/css-loader/dist/cjs.js?!./node_modules/vue-loader/lib/loaders/stylePostLoader.js!./node_modules/postcss-loader/src/index.js?!./node_modules/cache-loader/dist/cjs.js?!./node_modules/vue-loader/lib/index.js?!./src/App.vue?vue&type=style&index=0&lang=css&":
/*!*******************************************************************************************************************************************************************************************************************************************************************************************************************************!*\
  !*** ./node_modules/css-loader/dist/cjs.js??ref--6-oneOf-1-1!./node_modules/vue-loader/lib/loaders/stylePostLoader.js!./node_modules/postcss-loader/src??ref--6-oneOf-1-2!./node_modules/cache-loader/dist/cjs.js??ref--0-0!./node_modules/vue-loader/lib??vue-loader-options!./src/App.vue?vue&type=style&index=0&lang=css& ***!
  \*******************************************************************************************************************************************************************************************************************************************************************************************************************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

eval("// Imports\nvar ___CSS_LOADER_API_IMPORT___ = __webpack_require__(/*! ../node_modules/css-loader/dist/runtime/api.js */ \"./node_modules/css-loader/dist/runtime/api.js\");\nexports = ___CSS_LOADER_API_IMPORT___(false);\n// Module\nexports.push([module.i, \"\\n#app {\\n  font-family: Avenir, Helvetica, Arial, sans-serif;\\n  -webkit-font-smoothing: antialiased;\\n  -moz-osx-font-smoothing: grayscale;\\n  text-align: center;\\n  color: #2c3e50;\\n  margin-top: 60px;\\n}\\n\\n\", \"\"]);\n// Exports\nmodule.exports = exports;\n\n\n//# sourceURL=webpack:///./src/App.vue?./node_modules/css-loader/dist/cjs.js??ref--6-oneOf-1-1!./node_modules/vue-loader/lib/loaders/stylePostLoader.js!./node_modules/postcss-loader/src??ref--6-oneOf-1-2!./node_modules/cache-loader/dist/cjs.js??ref--0-0!./node_modules/vue-loader/lib??vue-loader-options");

/***/ }),

/***/ "./node_modules/vue-style-loader/index.js?!./node_modules/css-loader/dist/cjs.js?!./node_modules/vue-loader/lib/loaders/stylePostLoader.js!./node_modules/postcss-loader/src/index.js?!./node_modules/cache-loader/dist/cjs.js?!./node_modules/vue-loader/lib/index.js?!./src/App.vue?vue&type=style&index=0&lang=css&":
/*!*********************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************!*\
  !*** ./node_modules/vue-style-loader??ref--6-oneOf-1-0!./node_modules/css-loader/dist/cjs.js??ref--6-oneOf-1-1!./node_modules/vue-loader/lib/loaders/stylePostLoader.js!./node_modules/postcss-loader/src??ref--6-oneOf-1-2!./node_modules/cache-loader/dist/cjs.js??ref--0-0!./node_modules/vue-loader/lib??vue-loader-options!./src/App.vue?vue&type=style&index=0&lang=css& ***!
  \*********************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

eval("// style-loader: Adds some css to the DOM by adding a <style> tag\n\n// load the styles\nvar content = __webpack_require__(/*! !../node_modules/css-loader/dist/cjs.js??ref--6-oneOf-1-1!../node_modules/vue-loader/lib/loaders/stylePostLoader.js!../node_modules/postcss-loader/src??ref--6-oneOf-1-2!../node_modules/cache-loader/dist/cjs.js??ref--0-0!../node_modules/vue-loader/lib??vue-loader-options!./App.vue?vue&type=style&index=0&lang=css& */ \"./node_modules/css-loader/dist/cjs.js?!./node_modules/vue-loader/lib/loaders/stylePostLoader.js!./node_modules/postcss-loader/src/index.js?!./node_modules/cache-loader/dist/cjs.js?!./node_modules/vue-loader/lib/index.js?!./src/App.vue?vue&type=style&index=0&lang=css&\");\nif(content.__esModule) content = content.default;\nif(typeof content === 'string') content = [[module.i, content, '']];\nif(content.locals) module.exports = content.locals;\n// add the styles to the DOM\nvar add = __webpack_require__(/*! ../node_modules/vue-style-loader/lib/addStylesClient.js */ \"./node_modules/vue-style-loader/lib/addStylesClient.js\").default\nvar update = add(\"fa1ef42a\", content, false, {\"sourceMap\":false,\"shadowMode\":false});\n// Hot Module Replacement\nif(false) {}\n\n//# sourceURL=webpack:///./src/App.vue?./node_modules/vue-style-loader??ref--6-oneOf-1-0!./node_modules/css-loader/dist/cjs.js??ref--6-oneOf-1-1!./node_modules/vue-loader/lib/loaders/stylePostLoader.js!./node_modules/postcss-loader/src??ref--6-oneOf-1-2!./node_modules/cache-loader/dist/cjs.js??ref--0-0!./node_modules/vue-loader/lib??vue-loader-options");

/***/ }),

/***/ "./src/App.vue":
/*!*********************!*\
  !*** ./src/App.vue ***!
  \*********************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
eval("__webpack_require__.r(__webpack_exports__);\n/* harmony import */ var _App_vue_vue_type_template_id_7ba5bd90___WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./App.vue?vue&type=template&id=7ba5bd90& */ \"./src/App.vue?vue&type=template&id=7ba5bd90&\");\n/* harmony import */ var _App_vue_vue_type_script_lang_js___WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! ./App.vue?vue&type=script&lang=js& */ \"./src/App.vue?vue&type=script&lang=js&\");\n/* empty/unused harmony star reexport *//* harmony import */ var _App_vue_vue_type_style_index_0_lang_css___WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! ./App.vue?vue&type=style&index=0&lang=css& */ \"./src/App.vue?vue&type=style&index=0&lang=css&\");\n/* harmony import */ var _node_modules_vue_loader_lib_runtime_componentNormalizer_js__WEBPACK_IMPORTED_MODULE_3__ = __webpack_require__(/*! ../node_modules/vue-loader/lib/runtime/componentNormalizer.js */ \"./node_modules/vue-loader/lib/runtime/componentNormalizer.js\");\n\n\n\n\n\n\n/* normalize component */\n\nvar component = Object(_node_modules_vue_loader_lib_runtime_componentNormalizer_js__WEBPACK_IMPORTED_MODULE_3__[\"default\"])(\n  _App_vue_vue_type_script_lang_js___WEBPACK_IMPORTED_MODULE_1__[\"default\"],\n  _App_vue_vue_type_template_id_7ba5bd90___WEBPACK_IMPORTED_MODULE_0__[\"render\"],\n  _App_vue_vue_type_template_id_7ba5bd90___WEBPACK_IMPORTED_MODULE_0__[\"staticRenderFns\"],\n  false,\n  null,\n  null,\n  null\n  \n)\n\n/* hot reload */\nif (false) { var api; }\ncomponent.options.__file = \"src/App.vue\"\n/* harmony default export */ __webpack_exports__[\"default\"] = (component.exports);\n\n//# sourceURL=webpack:///./src/App.vue?");

/***/ }),

/***/ "./src/App.vue?vue&type=script&lang=js&":
/*!**********************************************!*\
  !*** ./src/App.vue?vue&type=script&lang=js& ***!
  \**********************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
eval("__webpack_require__.r(__webpack_exports__);\n/* harmony import */ var _node_modules_cache_loader_dist_cjs_js_ref_12_0_node_modules_babel_loader_lib_index_js_node_modules_cache_loader_dist_cjs_js_ref_0_0_node_modules_vue_loader_lib_index_js_vue_loader_options_App_vue_vue_type_script_lang_js___WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! -!../node_modules/cache-loader/dist/cjs.js??ref--12-0!../node_modules/babel-loader/lib!../node_modules/cache-loader/dist/cjs.js??ref--0-0!../node_modules/vue-loader/lib??vue-loader-options!./App.vue?vue&type=script&lang=js& */ \"./node_modules/cache-loader/dist/cjs.js?!./node_modules/babel-loader/lib/index.js!./node_modules/cache-loader/dist/cjs.js?!./node_modules/vue-loader/lib/index.js?!./src/App.vue?vue&type=script&lang=js&\");\n/* empty/unused harmony star reexport */ /* harmony default export */ __webpack_exports__[\"default\"] = (_node_modules_cache_loader_dist_cjs_js_ref_12_0_node_modules_babel_loader_lib_index_js_node_modules_cache_loader_dist_cjs_js_ref_0_0_node_modules_vue_loader_lib_index_js_vue_loader_options_App_vue_vue_type_script_lang_js___WEBPACK_IMPORTED_MODULE_0__[\"default\"]); \n\n//# sourceURL=webpack:///./src/App.vue?");

/***/ }),

/***/ "./src/App.vue?vue&type=style&index=0&lang=css&":
/*!******************************************************!*\
  !*** ./src/App.vue?vue&type=style&index=0&lang=css& ***!
  \******************************************************/
/*! no static exports found */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
eval("__webpack_require__.r(__webpack_exports__);\n/* harmony import */ var _node_modules_vue_style_loader_index_js_ref_6_oneOf_1_0_node_modules_css_loader_dist_cjs_js_ref_6_oneOf_1_1_node_modules_vue_loader_lib_loaders_stylePostLoader_js_node_modules_postcss_loader_src_index_js_ref_6_oneOf_1_2_node_modules_cache_loader_dist_cjs_js_ref_0_0_node_modules_vue_loader_lib_index_js_vue_loader_options_App_vue_vue_type_style_index_0_lang_css___WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! -!../node_modules/vue-style-loader??ref--6-oneOf-1-0!../node_modules/css-loader/dist/cjs.js??ref--6-oneOf-1-1!../node_modules/vue-loader/lib/loaders/stylePostLoader.js!../node_modules/postcss-loader/src??ref--6-oneOf-1-2!../node_modules/cache-loader/dist/cjs.js??ref--0-0!../node_modules/vue-loader/lib??vue-loader-options!./App.vue?vue&type=style&index=0&lang=css& */ \"./node_modules/vue-style-loader/index.js?!./node_modules/css-loader/dist/cjs.js?!./node_modules/vue-loader/lib/loaders/stylePostLoader.js!./node_modules/postcss-loader/src/index.js?!./node_modules/cache-loader/dist/cjs.js?!./node_modules/vue-loader/lib/index.js?!./src/App.vue?vue&type=style&index=0&lang=css&\");\n/* harmony import */ var _node_modules_vue_style_loader_index_js_ref_6_oneOf_1_0_node_modules_css_loader_dist_cjs_js_ref_6_oneOf_1_1_node_modules_vue_loader_lib_loaders_stylePostLoader_js_node_modules_postcss_loader_src_index_js_ref_6_oneOf_1_2_node_modules_cache_loader_dist_cjs_js_ref_0_0_node_modules_vue_loader_lib_index_js_vue_loader_options_App_vue_vue_type_style_index_0_lang_css___WEBPACK_IMPORTED_MODULE_0___default = /*#__PURE__*/__webpack_require__.n(_node_modules_vue_style_loader_index_js_ref_6_oneOf_1_0_node_modules_css_loader_dist_cjs_js_ref_6_oneOf_1_1_node_modules_vue_loader_lib_loaders_stylePostLoader_js_node_modules_postcss_loader_src_index_js_ref_6_oneOf_1_2_node_modules_cache_loader_dist_cjs_js_ref_0_0_node_modules_vue_loader_lib_index_js_vue_loader_options_App_vue_vue_type_style_index_0_lang_css___WEBPACK_IMPORTED_MODULE_0__);\n/* harmony reexport (unknown) */ for(var __WEBPACK_IMPORT_KEY__ in _node_modules_vue_style_loader_index_js_ref_6_oneOf_1_0_node_modules_css_loader_dist_cjs_js_ref_6_oneOf_1_1_node_modules_vue_loader_lib_loaders_stylePostLoader_js_node_modules_postcss_loader_src_index_js_ref_6_oneOf_1_2_node_modules_cache_loader_dist_cjs_js_ref_0_0_node_modules_vue_loader_lib_index_js_vue_loader_options_App_vue_vue_type_style_index_0_lang_css___WEBPACK_IMPORTED_MODULE_0__) if([\"default\"].indexOf(__WEBPACK_IMPORT_KEY__) < 0) (function(key) { __webpack_require__.d(__webpack_exports__, key, function() { return _node_modules_vue_style_loader_index_js_ref_6_oneOf_1_0_node_modules_css_loader_dist_cjs_js_ref_6_oneOf_1_1_node_modules_vue_loader_lib_loaders_stylePostLoader_js_node_modules_postcss_loader_src_index_js_ref_6_oneOf_1_2_node_modules_cache_loader_dist_cjs_js_ref_0_0_node_modules_vue_loader_lib_index_js_vue_loader_options_App_vue_vue_type_style_index_0_lang_css___WEBPACK_IMPORTED_MODULE_0__[key]; }) }(__WEBPACK_IMPORT_KEY__));\n\n\n//# sourceURL=webpack:///./src/App.vue?");

/***/ }),

/***/ "./src/App.vue?vue&type=template&id=7ba5bd90&":
/*!****************************************************!*\
  !*** ./src/App.vue?vue&type=template&id=7ba5bd90& ***!
  \****************************************************/
/*! exports provided: render, staticRenderFns */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
eval("__webpack_require__.r(__webpack_exports__);\n/* harmony import */ var _node_modules_cache_loader_dist_cjs_js_cacheDirectory_node_modules_cache_vue_loader_cacheIdentifier_200e5b7e_vue_loader_template_node_modules_vue_loader_lib_loaders_templateLoader_js_vue_loader_options_node_modules_cache_loader_dist_cjs_js_ref_0_0_node_modules_vue_loader_lib_index_js_vue_loader_options_App_vue_vue_type_template_id_7ba5bd90___WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! -!../node_modules/cache-loader/dist/cjs.js?{\"cacheDirectory\":\"node_modules/.cache/vue-loader\",\"cacheIdentifier\":\"200e5b7e-vue-loader-template\"}!../node_modules/vue-loader/lib/loaders/templateLoader.js??vue-loader-options!../node_modules/cache-loader/dist/cjs.js??ref--0-0!../node_modules/vue-loader/lib??vue-loader-options!./App.vue?vue&type=template&id=7ba5bd90& */ \"./node_modules/cache-loader/dist/cjs.js?{\\\"cacheDirectory\\\":\\\"node_modules/.cache/vue-loader\\\",\\\"cacheIdentifier\\\":\\\"200e5b7e-vue-loader-template\\\"}!./node_modules/vue-loader/lib/loaders/templateLoader.js?!./node_modules/cache-loader/dist/cjs.js?!./node_modules/vue-loader/lib/index.js?!./src/App.vue?vue&type=template&id=7ba5bd90&\");\n/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, \"render\", function() { return _node_modules_cache_loader_dist_cjs_js_cacheDirectory_node_modules_cache_vue_loader_cacheIdentifier_200e5b7e_vue_loader_template_node_modules_vue_loader_lib_loaders_templateLoader_js_vue_loader_options_node_modules_cache_loader_dist_cjs_js_ref_0_0_node_modules_vue_loader_lib_index_js_vue_loader_options_App_vue_vue_type_template_id_7ba5bd90___WEBPACK_IMPORTED_MODULE_0__[\"render\"]; });\n\n/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, \"staticRenderFns\", function() { return _node_modules_cache_loader_dist_cjs_js_cacheDirectory_node_modules_cache_vue_loader_cacheIdentifier_200e5b7e_vue_loader_template_node_modules_vue_loader_lib_loaders_templateLoader_js_vue_loader_options_node_modules_cache_loader_dist_cjs_js_ref_0_0_node_modules_vue_loader_lib_index_js_vue_loader_options_App_vue_vue_type_template_id_7ba5bd90___WEBPACK_IMPORTED_MODULE_0__[\"staticRenderFns\"]; });\n\n\n\n//# sourceURL=webpack:///./src/App.vue?");

/***/ }),

/***/ "./src/components/Board.vue":
/*!**********************************!*\
  !*** ./src/components/Board.vue ***!
  \**********************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
eval("__webpack_require__.r(__webpack_exports__);\n/* harmony import */ var _Board_vue_vue_type_template_id_e1ee1034___WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./Board.vue?vue&type=template&id=e1ee1034& */ \"./src/components/Board.vue?vue&type=template&id=e1ee1034&\");\n/* harmony import */ var _Board_vue_vue_type_script_lang_js___WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! ./Board.vue?vue&type=script&lang=js& */ \"./src/components/Board.vue?vue&type=script&lang=js&\");\n/* empty/unused harmony star reexport *//* harmony import */ var _node_modules_vue_loader_lib_runtime_componentNormalizer_js__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! ../../node_modules/vue-loader/lib/runtime/componentNormalizer.js */ \"./node_modules/vue-loader/lib/runtime/componentNormalizer.js\");\n\n\n\n\n\n/* normalize component */\n\nvar component = Object(_node_modules_vue_loader_lib_runtime_componentNormalizer_js__WEBPACK_IMPORTED_MODULE_2__[\"default\"])(\n  _Board_vue_vue_type_script_lang_js___WEBPACK_IMPORTED_MODULE_1__[\"default\"],\n  _Board_vue_vue_type_template_id_e1ee1034___WEBPACK_IMPORTED_MODULE_0__[\"render\"],\n  _Board_vue_vue_type_template_id_e1ee1034___WEBPACK_IMPORTED_MODULE_0__[\"staticRenderFns\"],\n  false,\n  null,\n  null,\n  null\n  \n)\n\n/* hot reload */\nif (false) { var api; }\ncomponent.options.__file = \"src/components/Board.vue\"\n/* harmony default export */ __webpack_exports__[\"default\"] = (component.exports);\n\n//# sourceURL=webpack:///./src/components/Board.vue?");

/***/ }),

/***/ "./src/components/Board.vue?vue&type=script&lang=js&":
/*!***********************************************************!*\
  !*** ./src/components/Board.vue?vue&type=script&lang=js& ***!
  \***********************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
eval("__webpack_require__.r(__webpack_exports__);\n/* harmony import */ var _node_modules_cache_loader_dist_cjs_js_ref_12_0_node_modules_babel_loader_lib_index_js_node_modules_cache_loader_dist_cjs_js_ref_0_0_node_modules_vue_loader_lib_index_js_vue_loader_options_Board_vue_vue_type_script_lang_js___WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! -!../../node_modules/cache-loader/dist/cjs.js??ref--12-0!../../node_modules/babel-loader/lib!../../node_modules/cache-loader/dist/cjs.js??ref--0-0!../../node_modules/vue-loader/lib??vue-loader-options!./Board.vue?vue&type=script&lang=js& */ \"./node_modules/cache-loader/dist/cjs.js?!./node_modules/babel-loader/lib/index.js!./node_modules/cache-loader/dist/cjs.js?!./node_modules/vue-loader/lib/index.js?!./src/components/Board.vue?vue&type=script&lang=js&\");\n/* empty/unused harmony star reexport */ /* harmony default export */ __webpack_exports__[\"default\"] = (_node_modules_cache_loader_dist_cjs_js_ref_12_0_node_modules_babel_loader_lib_index_js_node_modules_cache_loader_dist_cjs_js_ref_0_0_node_modules_vue_loader_lib_index_js_vue_loader_options_Board_vue_vue_type_script_lang_js___WEBPACK_IMPORTED_MODULE_0__[\"default\"]); \n\n//# sourceURL=webpack:///./src/components/Board.vue?");

/***/ }),

/***/ "./src/components/Board.vue?vue&type=template&id=e1ee1034&":
/*!*****************************************************************!*\
  !*** ./src/components/Board.vue?vue&type=template&id=e1ee1034& ***!
  \*****************************************************************/
/*! exports provided: render, staticRenderFns */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
eval("__webpack_require__.r(__webpack_exports__);\n/* harmony import */ var _node_modules_cache_loader_dist_cjs_js_cacheDirectory_node_modules_cache_vue_loader_cacheIdentifier_200e5b7e_vue_loader_template_node_modules_vue_loader_lib_loaders_templateLoader_js_vue_loader_options_node_modules_cache_loader_dist_cjs_js_ref_0_0_node_modules_vue_loader_lib_index_js_vue_loader_options_Board_vue_vue_type_template_id_e1ee1034___WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! -!../../node_modules/cache-loader/dist/cjs.js?{\"cacheDirectory\":\"node_modules/.cache/vue-loader\",\"cacheIdentifier\":\"200e5b7e-vue-loader-template\"}!../../node_modules/vue-loader/lib/loaders/templateLoader.js??vue-loader-options!../../node_modules/cache-loader/dist/cjs.js??ref--0-0!../../node_modules/vue-loader/lib??vue-loader-options!./Board.vue?vue&type=template&id=e1ee1034& */ \"./node_modules/cache-loader/dist/cjs.js?{\\\"cacheDirectory\\\":\\\"node_modules/.cache/vue-loader\\\",\\\"cacheIdentifier\\\":\\\"200e5b7e-vue-loader-template\\\"}!./node_modules/vue-loader/lib/loaders/templateLoader.js?!./node_modules/cache-loader/dist/cjs.js?!./node_modules/vue-loader/lib/index.js?!./src/components/Board.vue?vue&type=template&id=e1ee1034&\");\n/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, \"render\", function() { return _node_modules_cache_loader_dist_cjs_js_cacheDirectory_node_modules_cache_vue_loader_cacheIdentifier_200e5b7e_vue_loader_template_node_modules_vue_loader_lib_loaders_templateLoader_js_vue_loader_options_node_modules_cache_loader_dist_cjs_js_ref_0_0_node_modules_vue_loader_lib_index_js_vue_loader_options_Board_vue_vue_type_template_id_e1ee1034___WEBPACK_IMPORTED_MODULE_0__[\"render\"]; });\n\n/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, \"staticRenderFns\", function() { return _node_modules_cache_loader_dist_cjs_js_cacheDirectory_node_modules_cache_vue_loader_cacheIdentifier_200e5b7e_vue_loader_template_node_modules_vue_loader_lib_loaders_templateLoader_js_vue_loader_options_node_modules_cache_loader_dist_cjs_js_ref_0_0_node_modules_vue_loader_lib_index_js_vue_loader_options_Board_vue_vue_type_template_id_e1ee1034___WEBPACK_IMPORTED_MODULE_0__[\"staticRenderFns\"]; });\n\n\n\n//# sourceURL=webpack:///./src/components/Board.vue?");

/***/ }),

/***/ "./src/components/BoardList.vue":
/*!**************************************!*\
  !*** ./src/components/BoardList.vue ***!
  \**************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
eval("__webpack_require__.r(__webpack_exports__);\n/* harmony import */ var _BoardList_vue_vue_type_template_id_2add92b8___WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./BoardList.vue?vue&type=template&id=2add92b8& */ \"./src/components/BoardList.vue?vue&type=template&id=2add92b8&\");\n/* harmony import */ var _BoardList_vue_vue_type_script_lang_js___WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! ./BoardList.vue?vue&type=script&lang=js& */ \"./src/components/BoardList.vue?vue&type=script&lang=js&\");\n/* empty/unused harmony star reexport *//* harmony import */ var _node_modules_vue_loader_lib_runtime_componentNormalizer_js__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! ../../node_modules/vue-loader/lib/runtime/componentNormalizer.js */ \"./node_modules/vue-loader/lib/runtime/componentNormalizer.js\");\n\n\n\n\n\n/* normalize component */\n\nvar component = Object(_node_modules_vue_loader_lib_runtime_componentNormalizer_js__WEBPACK_IMPORTED_MODULE_2__[\"default\"])(\n  _BoardList_vue_vue_type_script_lang_js___WEBPACK_IMPORTED_MODULE_1__[\"default\"],\n  _BoardList_vue_vue_type_template_id_2add92b8___WEBPACK_IMPORTED_MODULE_0__[\"render\"],\n  _BoardList_vue_vue_type_template_id_2add92b8___WEBPACK_IMPORTED_MODULE_0__[\"staticRenderFns\"],\n  false,\n  null,\n  null,\n  null\n  \n)\n\n/* hot reload */\nif (false) { var api; }\ncomponent.options.__file = \"src/components/BoardList.vue\"\n/* harmony default export */ __webpack_exports__[\"default\"] = (component.exports);\n\n//# sourceURL=webpack:///./src/components/BoardList.vue?");

/***/ }),

/***/ "./src/components/BoardList.vue?vue&type=script&lang=js&":
/*!***************************************************************!*\
  !*** ./src/components/BoardList.vue?vue&type=script&lang=js& ***!
  \***************************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
eval("__webpack_require__.r(__webpack_exports__);\n/* harmony import */ var _node_modules_cache_loader_dist_cjs_js_ref_12_0_node_modules_babel_loader_lib_index_js_node_modules_cache_loader_dist_cjs_js_ref_0_0_node_modules_vue_loader_lib_index_js_vue_loader_options_BoardList_vue_vue_type_script_lang_js___WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! -!../../node_modules/cache-loader/dist/cjs.js??ref--12-0!../../node_modules/babel-loader/lib!../../node_modules/cache-loader/dist/cjs.js??ref--0-0!../../node_modules/vue-loader/lib??vue-loader-options!./BoardList.vue?vue&type=script&lang=js& */ \"./node_modules/cache-loader/dist/cjs.js?!./node_modules/babel-loader/lib/index.js!./node_modules/cache-loader/dist/cjs.js?!./node_modules/vue-loader/lib/index.js?!./src/components/BoardList.vue?vue&type=script&lang=js&\");\n/* empty/unused harmony star reexport */ /* harmony default export */ __webpack_exports__[\"default\"] = (_node_modules_cache_loader_dist_cjs_js_ref_12_0_node_modules_babel_loader_lib_index_js_node_modules_cache_loader_dist_cjs_js_ref_0_0_node_modules_vue_loader_lib_index_js_vue_loader_options_BoardList_vue_vue_type_script_lang_js___WEBPACK_IMPORTED_MODULE_0__[\"default\"]); \n\n//# sourceURL=webpack:///./src/components/BoardList.vue?");

/***/ }),

/***/ "./src/components/BoardList.vue?vue&type=template&id=2add92b8&":
/*!*********************************************************************!*\
  !*** ./src/components/BoardList.vue?vue&type=template&id=2add92b8& ***!
  \*********************************************************************/
/*! exports provided: render, staticRenderFns */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
eval("__webpack_require__.r(__webpack_exports__);\n/* harmony import */ var _node_modules_cache_loader_dist_cjs_js_cacheDirectory_node_modules_cache_vue_loader_cacheIdentifier_200e5b7e_vue_loader_template_node_modules_vue_loader_lib_loaders_templateLoader_js_vue_loader_options_node_modules_cache_loader_dist_cjs_js_ref_0_0_node_modules_vue_loader_lib_index_js_vue_loader_options_BoardList_vue_vue_type_template_id_2add92b8___WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! -!../../node_modules/cache-loader/dist/cjs.js?{\"cacheDirectory\":\"node_modules/.cache/vue-loader\",\"cacheIdentifier\":\"200e5b7e-vue-loader-template\"}!../../node_modules/vue-loader/lib/loaders/templateLoader.js??vue-loader-options!../../node_modules/cache-loader/dist/cjs.js??ref--0-0!../../node_modules/vue-loader/lib??vue-loader-options!./BoardList.vue?vue&type=template&id=2add92b8& */ \"./node_modules/cache-loader/dist/cjs.js?{\\\"cacheDirectory\\\":\\\"node_modules/.cache/vue-loader\\\",\\\"cacheIdentifier\\\":\\\"200e5b7e-vue-loader-template\\\"}!./node_modules/vue-loader/lib/loaders/templateLoader.js?!./node_modules/cache-loader/dist/cjs.js?!./node_modules/vue-loader/lib/index.js?!./src/components/BoardList.vue?vue&type=template&id=2add92b8&\");\n/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, \"render\", function() { return _node_modules_cache_loader_dist_cjs_js_cacheDirectory_node_modules_cache_vue_loader_cacheIdentifier_200e5b7e_vue_loader_template_node_modules_vue_loader_lib_loaders_templateLoader_js_vue_loader_options_node_modules_cache_loader_dist_cjs_js_ref_0_0_node_modules_vue_loader_lib_index_js_vue_loader_options_BoardList_vue_vue_type_template_id_2add92b8___WEBPACK_IMPORTED_MODULE_0__[\"render\"]; });\n\n/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, \"staticRenderFns\", function() { return _node_modules_cache_loader_dist_cjs_js_cacheDirectory_node_modules_cache_vue_loader_cacheIdentifier_200e5b7e_vue_loader_template_node_modules_vue_loader_lib_loaders_templateLoader_js_vue_loader_options_node_modules_cache_loader_dist_cjs_js_ref_0_0_node_modules_vue_loader_lib_index_js_vue_loader_options_BoardList_vue_vue_type_template_id_2add92b8___WEBPACK_IMPORTED_MODULE_0__[\"staticRenderFns\"]; });\n\n\n\n//# sourceURL=webpack:///./src/components/BoardList.vue?");

/***/ }),

/***/ "./src/components/Centralina.vue":
/*!***************************************!*\
  !*** ./src/components/Centralina.vue ***!
  \***************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
eval("__webpack_require__.r(__webpack_exports__);\n/* harmony import */ var _Centralina_vue_vue_type_template_id_2adb58f7___WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./Centralina.vue?vue&type=template&id=2adb58f7& */ \"./src/components/Centralina.vue?vue&type=template&id=2adb58f7&\");\n/* harmony import */ var _Centralina_vue_vue_type_script_lang_js___WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! ./Centralina.vue?vue&type=script&lang=js& */ \"./src/components/Centralina.vue?vue&type=script&lang=js&\");\n/* empty/unused harmony star reexport *//* harmony import */ var _node_modules_vue_loader_lib_runtime_componentNormalizer_js__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! ../../node_modules/vue-loader/lib/runtime/componentNormalizer.js */ \"./node_modules/vue-loader/lib/runtime/componentNormalizer.js\");\n\n\n\n\n\n/* normalize component */\n\nvar component = Object(_node_modules_vue_loader_lib_runtime_componentNormalizer_js__WEBPACK_IMPORTED_MODULE_2__[\"default\"])(\n  _Centralina_vue_vue_type_script_lang_js___WEBPACK_IMPORTED_MODULE_1__[\"default\"],\n  _Centralina_vue_vue_type_template_id_2adb58f7___WEBPACK_IMPORTED_MODULE_0__[\"render\"],\n  _Centralina_vue_vue_type_template_id_2adb58f7___WEBPACK_IMPORTED_MODULE_0__[\"staticRenderFns\"],\n  false,\n  null,\n  null,\n  null\n  \n)\n\n/* hot reload */\nif (false) { var api; }\ncomponent.options.__file = \"src/components/Centralina.vue\"\n/* harmony default export */ __webpack_exports__[\"default\"] = (component.exports);\n\n//# sourceURL=webpack:///./src/components/Centralina.vue?");

/***/ }),

/***/ "./src/components/Centralina.vue?vue&type=script&lang=js&":
/*!****************************************************************!*\
  !*** ./src/components/Centralina.vue?vue&type=script&lang=js& ***!
  \****************************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
eval("__webpack_require__.r(__webpack_exports__);\n/* harmony import */ var _node_modules_cache_loader_dist_cjs_js_ref_12_0_node_modules_babel_loader_lib_index_js_node_modules_cache_loader_dist_cjs_js_ref_0_0_node_modules_vue_loader_lib_index_js_vue_loader_options_Centralina_vue_vue_type_script_lang_js___WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! -!../../node_modules/cache-loader/dist/cjs.js??ref--12-0!../../node_modules/babel-loader/lib!../../node_modules/cache-loader/dist/cjs.js??ref--0-0!../../node_modules/vue-loader/lib??vue-loader-options!./Centralina.vue?vue&type=script&lang=js& */ \"./node_modules/cache-loader/dist/cjs.js?!./node_modules/babel-loader/lib/index.js!./node_modules/cache-loader/dist/cjs.js?!./node_modules/vue-loader/lib/index.js?!./src/components/Centralina.vue?vue&type=script&lang=js&\");\n/* empty/unused harmony star reexport */ /* harmony default export */ __webpack_exports__[\"default\"] = (_node_modules_cache_loader_dist_cjs_js_ref_12_0_node_modules_babel_loader_lib_index_js_node_modules_cache_loader_dist_cjs_js_ref_0_0_node_modules_vue_loader_lib_index_js_vue_loader_options_Centralina_vue_vue_type_script_lang_js___WEBPACK_IMPORTED_MODULE_0__[\"default\"]); \n\n//# sourceURL=webpack:///./src/components/Centralina.vue?");

/***/ }),

/***/ "./src/components/Centralina.vue?vue&type=template&id=2adb58f7&":
/*!**********************************************************************!*\
  !*** ./src/components/Centralina.vue?vue&type=template&id=2adb58f7& ***!
  \**********************************************************************/
/*! exports provided: render, staticRenderFns */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
eval("__webpack_require__.r(__webpack_exports__);\n/* harmony import */ var _node_modules_cache_loader_dist_cjs_js_cacheDirectory_node_modules_cache_vue_loader_cacheIdentifier_200e5b7e_vue_loader_template_node_modules_vue_loader_lib_loaders_templateLoader_js_vue_loader_options_node_modules_cache_loader_dist_cjs_js_ref_0_0_node_modules_vue_loader_lib_index_js_vue_loader_options_Centralina_vue_vue_type_template_id_2adb58f7___WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! -!../../node_modules/cache-loader/dist/cjs.js?{\"cacheDirectory\":\"node_modules/.cache/vue-loader\",\"cacheIdentifier\":\"200e5b7e-vue-loader-template\"}!../../node_modules/vue-loader/lib/loaders/templateLoader.js??vue-loader-options!../../node_modules/cache-loader/dist/cjs.js??ref--0-0!../../node_modules/vue-loader/lib??vue-loader-options!./Centralina.vue?vue&type=template&id=2adb58f7& */ \"./node_modules/cache-loader/dist/cjs.js?{\\\"cacheDirectory\\\":\\\"node_modules/.cache/vue-loader\\\",\\\"cacheIdentifier\\\":\\\"200e5b7e-vue-loader-template\\\"}!./node_modules/vue-loader/lib/loaders/templateLoader.js?!./node_modules/cache-loader/dist/cjs.js?!./node_modules/vue-loader/lib/index.js?!./src/components/Centralina.vue?vue&type=template&id=2adb58f7&\");\n/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, \"render\", function() { return _node_modules_cache_loader_dist_cjs_js_cacheDirectory_node_modules_cache_vue_loader_cacheIdentifier_200e5b7e_vue_loader_template_node_modules_vue_loader_lib_loaders_templateLoader_js_vue_loader_options_node_modules_cache_loader_dist_cjs_js_ref_0_0_node_modules_vue_loader_lib_index_js_vue_loader_options_Centralina_vue_vue_type_template_id_2adb58f7___WEBPACK_IMPORTED_MODULE_0__[\"render\"]; });\n\n/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, \"staticRenderFns\", function() { return _node_modules_cache_loader_dist_cjs_js_cacheDirectory_node_modules_cache_vue_loader_cacheIdentifier_200e5b7e_vue_loader_template_node_modules_vue_loader_lib_loaders_templateLoader_js_vue_loader_options_node_modules_cache_loader_dist_cjs_js_ref_0_0_node_modules_vue_loader_lib_index_js_vue_loader_options_Centralina_vue_vue_type_template_id_2adb58f7___WEBPACK_IMPORTED_MODULE_0__[\"staticRenderFns\"]; });\n\n\n\n//# sourceURL=webpack:///./src/components/Centralina.vue?");

/***/ }),

/***/ "./src/components/Log.vue":
/*!********************************!*\
  !*** ./src/components/Log.vue ***!
  \********************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
eval("__webpack_require__.r(__webpack_exports__);\n/* harmony import */ var _Log_vue_vue_type_template_id_12f38744___WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./Log.vue?vue&type=template&id=12f38744& */ \"./src/components/Log.vue?vue&type=template&id=12f38744&\");\n/* harmony import */ var _Log_vue_vue_type_script_lang_js___WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! ./Log.vue?vue&type=script&lang=js& */ \"./src/components/Log.vue?vue&type=script&lang=js&\");\n/* empty/unused harmony star reexport *//* harmony import */ var _node_modules_vue_loader_lib_runtime_componentNormalizer_js__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! ../../node_modules/vue-loader/lib/runtime/componentNormalizer.js */ \"./node_modules/vue-loader/lib/runtime/componentNormalizer.js\");\n\n\n\n\n\n/* normalize component */\n\nvar component = Object(_node_modules_vue_loader_lib_runtime_componentNormalizer_js__WEBPACK_IMPORTED_MODULE_2__[\"default\"])(\n  _Log_vue_vue_type_script_lang_js___WEBPACK_IMPORTED_MODULE_1__[\"default\"],\n  _Log_vue_vue_type_template_id_12f38744___WEBPACK_IMPORTED_MODULE_0__[\"render\"],\n  _Log_vue_vue_type_template_id_12f38744___WEBPACK_IMPORTED_MODULE_0__[\"staticRenderFns\"],\n  false,\n  null,\n  null,\n  null\n  \n)\n\n/* hot reload */\nif (false) { var api; }\ncomponent.options.__file = \"src/components/Log.vue\"\n/* harmony default export */ __webpack_exports__[\"default\"] = (component.exports);\n\n//# sourceURL=webpack:///./src/components/Log.vue?");

/***/ }),

/***/ "./src/components/Log.vue?vue&type=script&lang=js&":
/*!*********************************************************!*\
  !*** ./src/components/Log.vue?vue&type=script&lang=js& ***!
  \*********************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
eval("__webpack_require__.r(__webpack_exports__);\n/* harmony import */ var _node_modules_cache_loader_dist_cjs_js_ref_12_0_node_modules_babel_loader_lib_index_js_node_modules_cache_loader_dist_cjs_js_ref_0_0_node_modules_vue_loader_lib_index_js_vue_loader_options_Log_vue_vue_type_script_lang_js___WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! -!../../node_modules/cache-loader/dist/cjs.js??ref--12-0!../../node_modules/babel-loader/lib!../../node_modules/cache-loader/dist/cjs.js??ref--0-0!../../node_modules/vue-loader/lib??vue-loader-options!./Log.vue?vue&type=script&lang=js& */ \"./node_modules/cache-loader/dist/cjs.js?!./node_modules/babel-loader/lib/index.js!./node_modules/cache-loader/dist/cjs.js?!./node_modules/vue-loader/lib/index.js?!./src/components/Log.vue?vue&type=script&lang=js&\");\n/* empty/unused harmony star reexport */ /* harmony default export */ __webpack_exports__[\"default\"] = (_node_modules_cache_loader_dist_cjs_js_ref_12_0_node_modules_babel_loader_lib_index_js_node_modules_cache_loader_dist_cjs_js_ref_0_0_node_modules_vue_loader_lib_index_js_vue_loader_options_Log_vue_vue_type_script_lang_js___WEBPACK_IMPORTED_MODULE_0__[\"default\"]); \n\n//# sourceURL=webpack:///./src/components/Log.vue?");

/***/ }),

/***/ "./src/components/Log.vue?vue&type=template&id=12f38744&":
/*!***************************************************************!*\
  !*** ./src/components/Log.vue?vue&type=template&id=12f38744& ***!
  \***************************************************************/
/*! exports provided: render, staticRenderFns */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
eval("__webpack_require__.r(__webpack_exports__);\n/* harmony import */ var _node_modules_cache_loader_dist_cjs_js_cacheDirectory_node_modules_cache_vue_loader_cacheIdentifier_200e5b7e_vue_loader_template_node_modules_vue_loader_lib_loaders_templateLoader_js_vue_loader_options_node_modules_cache_loader_dist_cjs_js_ref_0_0_node_modules_vue_loader_lib_index_js_vue_loader_options_Log_vue_vue_type_template_id_12f38744___WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! -!../../node_modules/cache-loader/dist/cjs.js?{\"cacheDirectory\":\"node_modules/.cache/vue-loader\",\"cacheIdentifier\":\"200e5b7e-vue-loader-template\"}!../../node_modules/vue-loader/lib/loaders/templateLoader.js??vue-loader-options!../../node_modules/cache-loader/dist/cjs.js??ref--0-0!../../node_modules/vue-loader/lib??vue-loader-options!./Log.vue?vue&type=template&id=12f38744& */ \"./node_modules/cache-loader/dist/cjs.js?{\\\"cacheDirectory\\\":\\\"node_modules/.cache/vue-loader\\\",\\\"cacheIdentifier\\\":\\\"200e5b7e-vue-loader-template\\\"}!./node_modules/vue-loader/lib/loaders/templateLoader.js?!./node_modules/cache-loader/dist/cjs.js?!./node_modules/vue-loader/lib/index.js?!./src/components/Log.vue?vue&type=template&id=12f38744&\");\n/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, \"render\", function() { return _node_modules_cache_loader_dist_cjs_js_cacheDirectory_node_modules_cache_vue_loader_cacheIdentifier_200e5b7e_vue_loader_template_node_modules_vue_loader_lib_loaders_templateLoader_js_vue_loader_options_node_modules_cache_loader_dist_cjs_js_ref_0_0_node_modules_vue_loader_lib_index_js_vue_loader_options_Log_vue_vue_type_template_id_12f38744___WEBPACK_IMPORTED_MODULE_0__[\"render\"]; });\n\n/* harmony reexport (safe) */ __webpack_require__.d(__webpack_exports__, \"staticRenderFns\", function() { return _node_modules_cache_loader_dist_cjs_js_cacheDirectory_node_modules_cache_vue_loader_cacheIdentifier_200e5b7e_vue_loader_template_node_modules_vue_loader_lib_loaders_templateLoader_js_vue_loader_options_node_modules_cache_loader_dist_cjs_js_ref_0_0_node_modules_vue_loader_lib_index_js_vue_loader_options_Log_vue_vue_type_template_id_12f38744___WEBPACK_IMPORTED_MODULE_0__[\"staticRenderFns\"]; });\n\n\n\n//# sourceURL=webpack:///./src/components/Log.vue?");

/***/ }),

/***/ "./src/main.js":
/*!*********************!*\
  !*** ./src/main.js ***!
  \*********************/
/*! no exports provided */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
eval("__webpack_require__.r(__webpack_exports__);\n/* harmony import */ var D_lavoro_myserra_py_frontend_node_modules_core_js_modules_es_array_iterator_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./node_modules/core-js/modules/es.array.iterator.js */ \"./node_modules/core-js/modules/es.array.iterator.js\");\n/* harmony import */ var D_lavoro_myserra_py_frontend_node_modules_core_js_modules_es_array_iterator_js__WEBPACK_IMPORTED_MODULE_0___default = /*#__PURE__*/__webpack_require__.n(D_lavoro_myserra_py_frontend_node_modules_core_js_modules_es_array_iterator_js__WEBPACK_IMPORTED_MODULE_0__);\n/* harmony import */ var D_lavoro_myserra_py_frontend_node_modules_core_js_modules_es_promise_js__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! ./node_modules/core-js/modules/es.promise.js */ \"./node_modules/core-js/modules/es.promise.js\");\n/* harmony import */ var D_lavoro_myserra_py_frontend_node_modules_core_js_modules_es_promise_js__WEBPACK_IMPORTED_MODULE_1___default = /*#__PURE__*/__webpack_require__.n(D_lavoro_myserra_py_frontend_node_modules_core_js_modules_es_promise_js__WEBPACK_IMPORTED_MODULE_1__);\n/* harmony import */ var D_lavoro_myserra_py_frontend_node_modules_core_js_modules_es_object_assign_js__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! ./node_modules/core-js/modules/es.object.assign.js */ \"./node_modules/core-js/modules/es.object.assign.js\");\n/* harmony import */ var D_lavoro_myserra_py_frontend_node_modules_core_js_modules_es_object_assign_js__WEBPACK_IMPORTED_MODULE_2___default = /*#__PURE__*/__webpack_require__.n(D_lavoro_myserra_py_frontend_node_modules_core_js_modules_es_object_assign_js__WEBPACK_IMPORTED_MODULE_2__);\n/* harmony import */ var D_lavoro_myserra_py_frontend_node_modules_core_js_modules_es_promise_finally_js__WEBPACK_IMPORTED_MODULE_3__ = __webpack_require__(/*! ./node_modules/core-js/modules/es.promise.finally.js */ \"./node_modules/core-js/modules/es.promise.finally.js\");\n/* harmony import */ var D_lavoro_myserra_py_frontend_node_modules_core_js_modules_es_promise_finally_js__WEBPACK_IMPORTED_MODULE_3___default = /*#__PURE__*/__webpack_require__.n(D_lavoro_myserra_py_frontend_node_modules_core_js_modules_es_promise_finally_js__WEBPACK_IMPORTED_MODULE_3__);\n/* harmony import */ var vue__WEBPACK_IMPORTED_MODULE_4__ = __webpack_require__(/*! vue */ \"./node_modules/vue/dist/vue.runtime.esm.js\");\n/* harmony import */ var _App_vue__WEBPACK_IMPORTED_MODULE_5__ = __webpack_require__(/*! ./App.vue */ \"./src/App.vue\");\n/* harmony import */ var vue_router__WEBPACK_IMPORTED_MODULE_6__ = __webpack_require__(/*! vue-router */ \"./node_modules/vue-router/dist/vue-router.esm.js\");\n/* harmony import */ var _components_BoardList__WEBPACK_IMPORTED_MODULE_7__ = __webpack_require__(/*! ./components/BoardList */ \"./src/components/BoardList.vue\");\n/* harmony import */ var _components_Centralina__WEBPACK_IMPORTED_MODULE_8__ = __webpack_require__(/*! ./components/Centralina */ \"./src/components/Centralina.vue\");\n/* harmony import */ var _components_Log__WEBPACK_IMPORTED_MODULE_9__ = __webpack_require__(/*! ./components/Log */ \"./src/components/Log.vue\");\n\n\n\n\n\n\n\n\n\n // import some global styles\n//import './styles/style.scss'\n\nvue__WEBPACK_IMPORTED_MODULE_4__[\"default\"].config.productionTip = false;\nvue__WEBPACK_IMPORTED_MODULE_4__[\"default\"].use(vue_router__WEBPACK_IMPORTED_MODULE_6__[\"default\"]);\nvar routes = [{\n  path: '/centralina',\n  alias: '/',\n  component: _components_Centralina__WEBPACK_IMPORTED_MODULE_8__[\"default\"]\n}, {\n  path: '/boardlist',\n  component: _components_BoardList__WEBPACK_IMPORTED_MODULE_7__[\"default\"]\n}, {\n  path: '/log',\n  component: _components_Log__WEBPACK_IMPORTED_MODULE_9__[\"default\"]\n}]; // Create the router instance and pass the `routes` option\n\nvar router = new vue_router__WEBPACK_IMPORTED_MODULE_6__[\"default\"]({\n  mode: 'history',\n  routes: routes\n});\n/*\nnew Vue({\n  render: h => h(App),\n}).$mount('#app')\n*/\n\n/* eslint-disable no-new */\n\nnew vue__WEBPACK_IMPORTED_MODULE_4__[\"default\"]({\n  el: '#app',\n  router: router,\n  render: function render(h) {\n    return h(_App_vue__WEBPACK_IMPORTED_MODULE_5__[\"default\"]);\n  }\n});\n\n//# sourceURL=webpack:///./src/main.js?");

/***/ }),

/***/ 0:
/*!***************************!*\
  !*** multi ./src/main.js ***!
  \***************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

eval("module.exports = __webpack_require__(/*! D:\\lavoro\\myserra\\py\\frontend\\src\\main.js */\"./src/main.js\");\n\n\n//# sourceURL=webpack:///multi_./src/main.js?");

/***/ })

/******/ });