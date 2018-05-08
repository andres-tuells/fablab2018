<template>
  <v-flex xs12 sm6 offset-sm3>
      <v-card>
        <v-toolbar color="light-blue" dark>
          <v-toolbar-title inset>Serial Port Data</v-toolbar-title>
        </v-toolbar>
      </v-card>
      <v-card>
       <v-btn small color="primary" @click="clear">Clear</v-btn>
      </v-card>
      <v-card>
        <v-text-field
          @keydown.enter="sendMessage"
          v-model="message"
          label="Send"
          value=""
        ></v-text-field>
      </v-card>
      <v-card>
        <v-data-table
          :items="messages"
          hide-actions
          item-key="name"
        >
          <template slot="items" slot-scope="props">
            <tr>
              <td :class="props.item.type" v-text="props.item.content"></td>
            </tr>
          </template>
        </v-data-table>
      </v-card>
    </v-flex>
</template>

<script>
import { mapGetters } from 'vuex'; // eslint-disable-line no-unused-vars

export default {
  created() {
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
    clear() {
      this.$store.dispatch('Serial/clearMessages');
    },
    sendMessage() {
      this.$store.dispatch('Serial/send', this.message);
      this.message = '';
    },
  },
  computed: {
    ports() {
      return this.$store.getters['Serial/list']();
    },
    messages() {
      return this.$store.getters['Serial/reverseMessages']();
    },
    enabled() {
      return this.$store.state.Serial.portAddress == null;
    },
  },
  data() {
    return {
      message: '',
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
.sended {
  color: green;
}
.received {
  color: white;
}
</style>
