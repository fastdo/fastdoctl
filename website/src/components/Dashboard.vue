<template>
    <!-- <nav class="bg-indigo-500 p-2 text-white">
        <ul class="flex flex-row gap-6 overflow-x-auto">
            <li class="self-center">
                <svg class="w-12 h-12 stroke-white fill-transparent" version="1.1" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 480 480">
                <path d="M 65 68 q 650 -50 10 350" stroke-width="60" fill="none" />
                <path d="M 159 260 l 240 30" stroke-width="60" fill="none" />
                </svg>
            </li>
            <li class="self-center text-2xl whitespace-nowrap">FastDo Control Center</li>
        </ul>
    </nav> -->
    <nav class="navbar bg-primary text-primary-content">
        <div class="flex-none">
            <button class="btn btn-square btn-ghost">
                <svg class="w-12 h-12 stroke-primary-content fill-transparent" version="1.1" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 480 480">
                    <path d="M 65 68 q 650 -50 10 350" stroke-width="60" fill="none" />
                    <path d="M 159 260 l 240 30" stroke-width="60" fill="none" />
                </svg>
            </button>
        </div>
        <div class="flex-1">
            <a class="btn btn-ghost normal-case text-xl">FastDo Control Center</a>
        </div>
    </nav>

    <div class="container text-amber-400 stroke-indigo-400 fill-indigo-400 w-48 h-48 border-8 border-indigo-400 mx-auto my-4 p-8 rounded-full shadow-md">
        <svg class="w-full h-full" version="1.1" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 480 480">
        <!-- <rect x="0" y="0" rx="15%" ry="15%" width="480" height="480" /> -->
        <path d="M 65 68 q 650 -50 10 350" stroke-width="60" fill="none" />
        <path d="M 159 260 l 240 30" stroke-width="60" fill="none" />
        </svg>
    </div>

    <div class="flex justify-center">
        <ul class="steps">
            <li class="step step-primary">　环境检测　</li>
            <li class="step">　注册变量　</li>
            <li class="step">　修改配置　</li>
            <li class="step">　运行测试　</li>
        </ul>
    </div>

    <h1 class="text-2xl text-center pt-4">环境检测</h1>

    <div class="hero bg-base-100">
        <div class="hero-content text-center">
            <table class="table">
            <tr>
                <th class="w-24">操作系统</th>
                <td>{{envInfo.osName}}</td>
            </tr>
            <tr>
                <th>控制依赖</th>
                <td>{{envInfo.fastdo.path}} <div class="badge badge-accent badge-outline">{{envInfo.fastdo.version}}</div></td>
            </tr>
            <tr>
                <th>编译器名</th>
                <td>{{envInfo.compiler.compiler}}</td>
            </tr>
            <tr>
                <th>安装路径</th>
                <td>{{envInfo.compiler.installPath}}</td>
            </tr>
            <tr v-if="envInfo.compiler.VSToolsBat64">
                <th>脚本路径</th>
                <td>{{envInfo.compiler.VSToolsBat64}}</td>
            </tr>
            </table>
        </div>
    </div>

    <div class="flex justify-center">
    <div class="join">
        <button class="btn join-item">上一步</button>
        <button class="btn btn-primary join-item">下一步</button>
    </div>
    </div>

</template>

<script setup lang="ts">
import { ref, reactive } from 'vue'
import axios from 'axios'

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


axios.get('/api/get_compiler_info').then( ( value ) => {
    envInfo.compiler = value.data
    console.log(value.data)
} )
axios.get('/api/get_fastdo_info').then( ( value ) => {
    envInfo.fastdo = value.data
    console.log(value.data)
} )
axios.get('/api/get_os_info').then( ( value ) => {
    envInfo.osName = value.data.os
    console.log(value.data)
} )

</script>

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
