import { createApp } from 'vue';
import App from './App.vue';
import { createRouter, createWebHashHistory } from 'vue-router';
import './index.css';

let routes = [
    { path: '/', component: () => import('./components/Dashboard.vue') },
    { path: '/hello', component: () => import('./components/HelloWorld.vue') },
];

const router = createRouter( {
    history: createWebHashHistory(),
    routes
} );

const app = createApp(App);
app.use(router);
app.config.warnHandler = () => null;
app.mount('#app');
