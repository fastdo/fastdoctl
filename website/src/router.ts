import { createRouter, createWebHashHistory } from 'vue-router';
import EnvCheck from './components/EnvCheck.vue';

export default createRouter( {
    history: createWebHashHistory(),
    routes: [
        { path: '/', component: EnvCheck },
        { path: '/hello', component: () => import('./components/HelloWorld.vue') },
    ]
} );
