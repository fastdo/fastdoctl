<script setup lang="ts">
import { ref } from 'vue'

defineProps<{ msg: string }>()

const count = ref(0)
</script>

<template>
    <h1>{{ msg }}</h1>

    <p>当前操作系统：Windows 10 x64
    </p>

    <p>See <code>README.md</code> for more information.</p>

    <button type="button" class="btn btn-primary" @click="count++">count is: {{ count }}</button>
    <p>
        Edit
        <code>components/HelloWorld.vue</code> to test hot module replacement.
    </p>
</template>

<style scoped>

</style>
