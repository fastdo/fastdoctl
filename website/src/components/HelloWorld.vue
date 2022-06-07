<script setup lang="ts">
import { ref } from 'vue'

defineProps<{ msg: string }>()

const count = ref(0)
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

    <div class="text-2xl border-2 mx-2 p-4 rounded-lg">环境检测</div>
</template>

<style scoped>

</style>
