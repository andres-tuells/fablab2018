<template>
  <v-flex xs12 sm6 offset-sm3>
      <v-card>
        <div class="text-xs-center">
          <v-chip :color="endpoint?'green':'red'" text-color="white">Endpoint</v-chip>
        </div>
      </v-card>

    </v-flex>
</template>

<script>
import { mapGetters } from 'vuex'; // eslint-disable-line no-unused-vars

export default {
  created() {
    this.subscription = this.$store.getters['Serial/source']('ENDPOINT:')
      .subscribe((x) => { this.endpoint = x.indexOf('1') > -1; });
  },
  beforeDestroy() {
    if (this.subscription) this.subscription.unsubscribe();
  },
  methods: {

  },
  computed: {

  },
  data() {
    return {
      endpoint: true,
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
