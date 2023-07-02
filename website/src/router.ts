import { createRouter, createWebHashHistory } from 'vue-router';
import EnvCheck from './pages/EnvCheck.vue';

export default createRouter( {
    history: createWebHashHistory(),
    routes: [
        { path: '/', component: EnvCheck },
        { path: '/envcheck', component: EnvCheck },
        { path: '/envvars', component: () => import('./pages/EnvVars.vue') },
        { path: '/modifyconfig', component: () => import('./pages/ModifyConfig.vue') },
    ]
} );
