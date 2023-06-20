import { createRouter, createWebHashHistory } from 'vue-router';

let routes = [
    { path: '/', component: () => import('./components/Dashboard.vue') },
    { path: '/hello', component: () => import('./components/HelloWorld.vue') },
];

export default createRouter( {
    history: createWebHashHistory(),
    routes
} );
