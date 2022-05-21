<script setup lang="ts">
import { ref } from 'vue'

defineProps<{ msg: string }>()

const count = ref(0)
</script>

<template>
    <nav class="
        bg-slate-100
        py-2
    ">
        "{{ count }}"
    </nav>
</template>

<style scoped>

</style>
