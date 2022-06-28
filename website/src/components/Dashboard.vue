<script setup lang="ts">
import { ref, reactive } from 'vue'
import axios from 'axios'

const count = ref(0)

const envInfo = reactive( {
    osName: '',
    fastdo: {
        path: '',
        version: '',
    },
    compiler: {
        compiler: '',
        installPath: '',
        VSToolsBat64: ''
    },
} )

const serverRootUrl = 'http://192.168.138.143:16060'
axios.get( serverRootUrl + '/api/get_compiler_info' ).then( ( value ) => {
    envInfo.compiler = value.data
    console.log( value.data)
} )
axios.get( serverRootUrl + '/api/get_fastdo_info' ).then( ( value ) => {
    envInfo.fastdo = value.data
    console.log( value.data)
} )
axios.get( serverRootUrl + '/api/get_os_info' ).then( ( value ) => {
    envInfo.osName = value.data.os
    console.log( value.data)
} )

</script>

<template>
    <nav class="bg-indigo-500 p-2 text-white">
        <ul class="flex flex-row gap-6 overflow-x-auto">
            <li class="self-center">
                <svg class="w-12 h-12 stroke-white fill-transparent" version="1.1" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 480 480">
                <path d="M 65 68 q 650 -50 10 350" stroke-width="60" fill="none" />
                <path d="M 159 260 l 240 30" stroke-width="60" fill="none" />
                </svg>
            </li>
            <li class="self-center text-2xl whitespace-nowrap">FastDo Control Center</li>
        </ul>
    </nav>

    <div class="container text-amber-400 stroke-indigo-400 fill-indigo-400 w-48 h-48 border-8 border-indigo-400 mx-auto my-4 p-8 rounded-full shadow-md">
        <svg class="w-full h-full" version="1.1" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 480 480">
        <!-- <rect x="0" y="0" rx="15%" ry="15%" width="480" height="480" /> -->
        <path d="M 65 68 q 650 -50 10 350" stroke-width="60" fill="none" />
        <path d="M 159 260 l 240 30" stroke-width="60" fill="none" />
        </svg>
    </div>

    <div class="mx-2 px-4">
        <h1 class="text-2xl text-center pb-2">环境检测</h1>
        <table class="table">
        <tr>
            <td class="w-24">操作系统</td>
            <td>{{envInfo.osName}}</td>
        </tr>
        <tr>
            <td>FastDo包</td>
            <td>{{envInfo.fastdo.path}} ({{envInfo.fastdo.version}})</td>
        </tr>
        <tr>
            <td>编译器名</td>
            <td>{{envInfo.compiler.compiler}}</td>
        </tr>
        <tr>
            <td>安装路径</td>
            <td>{{envInfo.compiler.installPath}}</td>
        </tr>
        <tr v-if="envInfo.compiler.VSToolsBat64">
            <td>脚本路径</td>
            <td>{{envInfo.compiler.VSToolsBat64}}</td>
        </tr>
        </table>
    </div>
</template>

<style scoped>

.table {
    @apply border-collapse w-full table-fixed;
}
.table tr {
    @apply border-b align-top;
}
.table tr td {
    @apply break-words p-1;
}

</style>
