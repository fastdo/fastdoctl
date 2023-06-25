<template>
    <StepProgress :step="2" class="my-2"></StepProgress>

    <h1 class="text-2xl text-center pt-4">注册变量</h1>

    <div class="hero">
        <div class="hero-content">
            <table class="table table-xs">
                <tr v-for="(varval, varname) in envInfo.envvars.envvars" :key="varname">
                    <th class="w-40">{{ varname }}</th>
                    <td v-if="varval" class="overflow-auto">{{ varval }}</td><td v-else class="text-error">× <button class="btn btn-xs btn-primary">注册</button></td>
                </tr>
                <tr>
                    <th class="w-40">FASTDO_BASE</th>
                    <td v-if="envInfo.package.base" class="overflow-auto"></td>
                </tr>
                <tr>
                    <th class="w-40">FASTDO_INCLUDE</th>
                    <td v-if="envInfo.package.include" class="overflow-auto"></td>
                </tr>
            </table>
        </div>
    </div>

    <div class="flex justify-center mb-2">
        <div class="join">
            <button class="btn join-item" @click="prevStep()">上一步</button>
            <button class="btn btn-primary join-item" :disabled="!envInfoStore.envCheckNext" @click="nextStep()">下一步</button>
        </div>
    </div>

</template>

<script setup lang="ts">
import { useRoute, useRouter } from 'vue-router';
import { useEnvInfoStore } from '../stores/EnvInfoStore';
import StepProgress from '../components/StepProgress.vue';

const router  = useRouter();
const envInfoStore = useEnvInfoStore();
const envInfo = useEnvInfoStore().envInfo;

function prevStep() {
    router.push( { path: 'envcheck' } );
}

function nextStep() {
    envInfoStore.fetchData();
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
