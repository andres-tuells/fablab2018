<template>
  <div id="app">
    <v-app dark>
      <v-toolbar dark color="teal lighten-3">
        <v-menu>
          <v-btn slot="activator" icon dark>
            <v-icon>menu</v-icon>
          </v-btn>
          <v-list>
            <v-list-tile v-for="(item, i) in items" :key="i" router :to="item.to">
              <v-list-tile-title>{{ item.title }}</v-list-tile-title>
            </v-list-tile>
          </v-list>
        </v-menu>
        <v-toolbar-title class="white--text">Infinite Machine</v-toolbar-title>
        <v-spacer></v-spacer>
        <v-btn icon 
          router
          :to="'/settings'">
            <v-icon>settings</v-icon>
          </v-btn>
        <v-switch
          v-model="connectionStatus"
          color="success"
          hide-details
        ></v-switch>
      </v-toolbar>
      <main>
        <v-content>
          <v-container fluid fill-height>
            <v-slide-y-transition mode="out-in">
              <router-view></router-view>
            </v-slide-y-transition>
          </v-container>
        </v-content>
      </main>
      <v-footer :fixed="fixed" app>
        <v-spacer></v-spacer>
        <span>&copy; Fablab Barcelona 2018</span>
      </v-footer>
    </v-app>
  </div>
</template>

<script>
  export default {
    name: 'app-dashboard',
    data: () => ({
      clipped: false,
      drawer: true,
      fixed: false,
      items: [
        { icon: 'apps', title: 'Servo', to: '/' },
        { icon: 'bubble_chart', title: 'Serial Port', to: '/serial-port' },
        { icon: 'bubble_chart', title: 'Endpoint', to: '/endpoint' },
      ],
      miniVariant: false,
      right: true,
      rightDrawer: false,
      title: 'Infinite Machine',
      connectionStatus: false,
    }),
    methods: {
      connect() {
        this.$store.dispatch('Serial/listen');
      },
      close() {
        this.$store.dispatch('Serial/close');
      },
    },
    watch: {
      connectionStatus(newValue) {
        if (newValue) {
          this.connect();
        } else {
          this.close();
        }
      },
    },
  };
</script>

<style lang="stylus">
  @import './assets/stylus/main.styl'
</style>


<style>
  @import url('https://fonts.googleapis.com/css?family=Roboto:300,400,500,700|Material+Icons');
  /* Global CSS */
</style>
