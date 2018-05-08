<template>
  <v-layout column justify-center>
    <h3>Control servo angle</h3>
    <v-card>
      <v-card-text>
        <v-slider v-model="angle" :min="0" :max="180" step="0"></v-slider>
      </v-card-text>
    </v-card>
    <v-card>
      &nbsp;
    </v-card>
    <v-card>
      <v-btn small color="primary" @click="move">Move</v-btn>
      Angle: <span v-text="receivedAngle"></span>
    </v-card> 
  </v-layout>
</template>


<script>
import { mapGetters } from 'vuex'; // eslint-disable-line no-unused-vars
import { interval } from 'rxjs/observable/interval';

export default {
  created() {
    this.subscription = this.$store.getters['Serial/source']('ANGLE:')
      .subscribe((x) => { this.receivedAngle = x; });
    const source = interval(10000);
    this.intervalSubscriber = source.subscribe(() => this.$store.dispatch('Serial/send', 'ANGLE:'));
  },
  beforeDestroy() {
    this.subscription.unsubscribe();
    this.intervalSubscriber.unsubscribe();
  },
  methods: {
    move() {
      this.$store.dispatch('Serial/send', 'MOVE:');
    },
  },
  computed: {
  },
  data() {
    return {
      angle: 0,
      receivedAngle: 0,
    };
  },
  watch: {
    angle(newValue, oldValue) {
      console.log(`New angle ${newValue}`);
      this.$store.dispatch('Serial/send', `MOVETO:${newValue}`);
    },
  },
  filters: {
  },
};
</script>
