import Vue from 'vue';
import Router from 'vue-router';

Vue.use(Router);

export default new Router({
  routes: [
    {
      path: '/',
      name: 'servo-view',
      component: require('@/components/ServoView'),
    },
    {
      path: '/endpoint',
      name: 'endpoint',
      component: require('@/components/EndPointView'),
    },
    {
      path: '/serial-port',
      name: 'serial-port',
      component: require('@/components/SerialPortView'),
    },
    {
      path: '/settings',
      name: 'settings',
      component: require('@/components/SettingsView'),
    },
    {
      path: '*',
      redirect: '/',
    },
  ],
});
