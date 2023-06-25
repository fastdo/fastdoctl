<template>
    <div class="flex justify-center">
        <ul class="steps">
            <li class="step" :class="{ 'step-primary': step > 0 }">　环境检测　</li>
            <li class="step" :class="{ 'step-primary': step > 1 }">　注册变量　</li>
            <li class="step" :class="{ 'step-primary': step > 2 }">　修改配置　</li>
            <li class="step" :class="{ 'step-primary': step > 3 }">　运行测试　</li>
        </ul>
    </div>
</template>

<script setup lang="ts">
//import { defineProps } from 'vue';
const props = withDefaults( defineProps<{
    step?: number
}>(), {
    step: 1
} );

</script>

<style scoped>

</style>