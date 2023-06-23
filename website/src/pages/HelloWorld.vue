<script setup lang="ts">
import { ref, reactive } from 'vue'
import axios from 'axios'

defineProps<{ msg: string }>()
defineEmits<{
    (event: 'pointerenter') : void
    (event: 'poinetrleave') : void
}>()

const count = ref(0)

const envInfo = reactive( {
    os: ''
} )

axios.get('http://localhost:16060/api/get_os_info').then( ( value ) => {
    //console.log(value.data)
    envInfo.os = value.data.os
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
            <li class="self-center text-2xl whitespace-nowrap">状态</li>
            <li class="self-center text-2xl whitespace-nowrap">安装</li>
            <li class="self-center text-2xl whitespace-nowrap">更新</li>
            <li class="self-center text-2xl whitespace-nowrap">卸载</li>
        </ul>
    </nav>

    <div class="container text-amber-400 stroke-indigo-400 fill-indigo-400 w-60 h-60 border-8 border-indigo-400 mx-auto my-4 p-8 rounded-full shadow-md">
        <svg class="w-full h-full" version="1.1" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 480 480">
        <!-- <rect x="0" y="0" rx="15%" ry="15%" width="480" height="480" /> -->
        <path d="M 65 68 q 650 -50 10 350" stroke-width="60" fill="none" />
        <path d="M 159 260 l 240 30" stroke-width="60" fill="none" />
        </svg>
    </div>

    <div class="border-2 mx-2 p-4 rounded-lg">
        <h1 class="text-2xl text-center">环境检测</h1>
        <table class="border-collapse w-full table-fixed">
        <tr class="border-b">
            <td class="w-1/4">操作系统</td>
            <td>{{envInfo.os}}</td>
        </tr>
        </table>
    </div>
</template>

<style scoped>

</style>
