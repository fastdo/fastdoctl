<template>
    <StepProgress :step="3" class="my-2"></StepProgress>

    <h1 class="text-2xl text-center pt-4">修改配置</h1>

    <div class="container mx-auto">
        <div class="col">
            <h3>Nginx配置</h3>
        </div>
    </div>

    <div class="flex justify-center mb-2">
        <div class="join">
            <button class="btn join-item" @click="prevStep()">上一步</button>
            <button class="btn btn-primary join-item" :disabled="!envInfo.envvars.check" @click="nextStep()">下一步</button>
        </div>
    </div>

</template>

<script setup lang="ts">
import { useRoute, useRouter } from 'vue-router';
import { useEnvInfoStore } from '../stores/EnvInfoStore';
import StepProgress from '../components/StepProgress.vue';
import ErrorBadge from '../components/ErrorBadge.vue';

const router  = useRouter();
const envInfoStore = useEnvInfoStore();
const envInfo = useEnvInfoStore().envInfo;

function prevStep() {
    router.push( { path: 'envvars' } );
}

function nextStep() {
    //router.push( { path: 'modifyconfig' } );
}

function registerVars() {
    envInfoStore.registerVars();
}

</script>

<style lang="scss" scoped>
.table {
    @apply border-collapse w-full table-fixed;
    tr {
        @apply border-b align-top;
        td {
            @apply break-words p-1;
        }
    }
}

</style>
