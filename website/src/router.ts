import { createRouter, createWebHashHistory } from 'vue-router';
import EnvCheck from './pages/EnvCheck.vue';

export default createRouter( {
    history: createWebHashHistory(),
    routes: [
        { path: '/', component: EnvCheck },
        { path: '/hello', component: () => import('./pages/HelloWorld.vue') },
    ]
} );
