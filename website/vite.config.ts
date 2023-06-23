import { defineConfig } from 'vite';
import vue from '@vitejs/plugin-vue';
//import { fileURLToPath, URL } from 'node:url'
const path = require('path');

// https://vitejs.dev/config/
export default defineConfig( {
    plugins: [vue()],
    resolve: {
        alias: {
            //'@': fileURLToPath(new URL('./src', import.meta.url))
            '@': path.resolve( __dirname, './src' )
        }
    },
    server: {
        proxy: {
            '/api': 'http://localhost:16060',
        }
    }
} );
