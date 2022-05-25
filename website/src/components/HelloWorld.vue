<script setup lang="ts">
import { ref } from 'vue'

defineProps<{ msg: string }>()

const count = ref(0)
</script>

<template>
    <nav class="bg-indigo-200 py-2">
        <button class="py-2 px-4 bg-indigo-500 text-white font-semibold rounded-lg shadow-xl">"{{ count }}"</button>
    </nav>
    <!-- <div class="text-center text-5xl font-extrabold leading-none tracking-tight"> -->
    <span class="decoration-clone bg-clip-text text-transparent bg-gradient-to-b from-amber-400 to-red-500">
        Hello,
        world!
    </span>
    <!-- </div> -->



</template>

<style scoped>

</style>
