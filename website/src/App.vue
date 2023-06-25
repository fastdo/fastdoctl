<template>
    <nav class="navbar bg-primary text-primary-content">
        <div class="flex-none">
            <button class="btn btn-square btn-ghost">
                <svg class="w-12 h-12 stroke-white fill-transparent" version="1.1" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 480 480">
                    <path d="M 65 68 q 650 -50 10 350" stroke-width="60" fill="none" />
                    <path d="M 159 260 l 240 30" stroke-width="60" fill="none" />
                </svg>
            </button>
        </div>
        <div class="flex-1">
            <a class="btn btn-ghost normal-case text-xl">FastDo Control Center</a>
        </div>
    </nav>
    <!-- <img alt="Vue logo" src="./assets/favicon128x128.png" /> -->
    <router-view></router-view>
</template>

<script setup lang="ts">
// This starter template is using Vue 3 <script setup> SFCs
// Check out https://vuejs.org/api/sfc-script-setup.html#script-setup

</script>

<style>
#app {
    /* text-align: center; */
    /* margin-top: 60px; */
}
</style>
