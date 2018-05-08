<template>
  <v-flex xs12 sm6 offset-sm3>
      <v-card>
        <v-toolbar color="light-blue" dark>
          <v-toolbar-title inset>Settings</v-toolbar-title>
        </v-toolbar>
      </v-card>
      <v-card>
        <h4>Select Port</h4>
        <v-list>
          <v-list-tile v-for="port in ports" v-bind:key="port.comName">                       
            <v-list-tile-content 
              :class="{selected:port.comName==$store.state.Serial.portAddress}"
              v-on:click="changePort( port.comName )"
              >
              <v-list-tile-title>{{ port.comName }} {{ port.manufacturer }}</v-list-tile-title>
            </v-list-tile-content>            
          </v-list-tile>                  
        </v-list>
      </v-card>
      <v-card>
       <v-select
            label="Baud rate"
            @input="handleSelectBaudRate" 
            :items="$store.state.Serial.baudRateOptions"
            :value="$store.state.Serial.baudRate"
          ></v-select>
      </v-card>
    </v-flex>
</template>

<script>
import { mapGetters } from 'vuex'; // eslint-disable-line no-unused-vars

export default {
  async created() {
    this.ports = await this.$store.dispatch('Serial/list');
    console.log(`Ports: ${JSON.stringify(this.ports)}`);
  },
  beforeDestroy() {
  },
  methods: {
    changePort(port) {
      this.$store.dispatch('Serial/updatePort', port);
    },
    handleSelectBaudRate(value) {
      this.$store.dispatch('Serial/updateBaudRate', value);
    },
  },
  computed: {
  },
  data() {
    return {
      ports: [],
    };
  },
  watch: {
  },
  filters: {
  },
};
</script>

<style scoped>
h1 {
  color: #42b983;
}
.selected {
  color: green;
}
</style>
