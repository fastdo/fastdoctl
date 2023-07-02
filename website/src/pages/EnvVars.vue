<template>
    <StepProgress :step="2" class="my-2"></StepProgress>

    <h1 class="text-2xl text-center pt-4">注册变量</h1>

    <div class="hero">
        <div class="hero-content">
            <table class="table table-xs">
                <tr>
                    <th class="w-40">FASTDO_BASE</th>
                    <td v-if="envInfo.envvars.vars.FASTDO_BASE" class="overflow-auto">{{ envInfo.envvars.vars.FASTDO_BASE }}</td><td v-else class="text-error">×
                    <span v-if="envInfo.package.base" class="badge badge-accent">可注册</span><span v-else class="badge badge-error">不可注册</span></td>
                </tr>
                <tr>
                    <th>FASTDO_INCLUDE</th>
                    <td v-if="envInfo.envvars.vars.FASTDO_INCLUDE" class="overflow-auto">{{ envInfo.envvars.vars.FASTDO_INCLUDE }}</td><td v-else class="text-error">×
                    <span v-if="envInfo.package.include" class="badge badge-accent">可注册</span><span v-else class="badge badge-error">不可注册</span></td>
                </tr>
                <tr>
                    <th>FASTDO_X64D_BIN</th>
                    <td v-if="envInfo.envvars.vars.FASTDO_X64D_BIN" class="overflow-auto">{{ envInfo.envvars.vars.FASTDO_X64D_BIN }}</td><td v-else class="text-error">×
                    <span v-if="envInfo.package.arch.X64D" class="badge badge-accent">可注册</span><span v-else class="badge badge-error">不可注册</span></td>
                </tr>
                <tr>
                    <th>FASTDO_X64D_LIB</th>
                    <td v-if="envInfo.envvars.vars.FASTDO_X64D_LIB" class="overflow-auto">{{ envInfo.envvars.vars.FASTDO_X64D_LIB }}</td><td v-else class="text-error">×
                    <span v-if="envInfo.package.arch.X64D" class="badge badge-accent">可注册</span><span v-else class="badge badge-error">不可注册</span></td>
                </tr>
                <tr>
                    <th>FASTDO_X64R_BIN</th>
                    <td v-if="envInfo.envvars.vars.FASTDO_X64R_BIN" class="overflow-auto">{{ envInfo.envvars.vars.FASTDO_X64R_BIN }}</td><td v-else class="text-error">×
                    <span v-if="envInfo.package.arch.X64R" class="badge badge-accent">可注册</span><span v-else class="badge badge-error">不可注册</span></td>
                </tr>
                <tr>
                    <th>FASTDO_X64R_LIB</th>
                    <td v-if="envInfo.envvars.vars.FASTDO_X64R_LIB" class="overflow-auto">{{ envInfo.envvars.vars.FASTDO_X64R_LIB }}</td><td v-else class="text-error">×
                    <span v-if="envInfo.package.arch.X64R" class="badge badge-accent">可注册</span><span v-else class="badge badge-error">不可注册</span></td>
                </tr>
                <tr>
                    <th>FASTDO_X86D_BIN</th>
                    <td v-if="envInfo.envvars.vars.FASTDO_X86D_BIN" class="overflow-auto">{{ envInfo.envvars.vars.FASTDO_X86D_BIN }}</td><td v-else class="text-error">×
                    <span v-if="envInfo.package.arch.X86D" class="badge badge-accent">可注册</span><span v-else class="badge badge-error">不可注册</span></td>
                </tr>
                <tr>
                    <th>FASTDO_X86D_LIB</th>
                    <td v-if="envInfo.envvars.vars.FASTDO_X86D_LIB" class="overflow-auto">{{ envInfo.envvars.vars.FASTDO_X86D_LIB }}</td><td v-else class="text-error">×
                    <span v-if="envInfo.package.arch.X86D" class="badge badge-accent">可注册</span><span v-else class="badge badge-error">不可注册</span></td>
                </tr>
                <tr>
                    <th>FASTDO_X86R_BIN</th>
                    <td v-if="envInfo.envvars.vars.FASTDO_X86R_BIN" class="overflow-auto">{{ envInfo.envvars.vars.FASTDO_X86R_BIN }}</td><td v-else class="text-error">×
                    <span v-if="envInfo.package.arch.X86R" class="badge badge-accent">可注册</span><span v-else class="badge badge-error">不可注册</span></td>
                </tr>
                <tr>
                    <th>FASTDO_X86R_LIB</th>
                    <td v-if="envInfo.envvars.vars.FASTDO_X86R_LIB" class="overflow-auto">{{ envInfo.envvars.vars.FASTDO_X86R_LIB }}</td><td v-else class="text-error">×
                    <span v-if="envInfo.package.arch.X86R" class="badge badge-accent">可注册</span><span v-else class="badge badge-error">不可注册</span></td>
                </tr>
            </table>
        </div>
    </div>

    <div class="flex justify-center mb-2">
        <div class="join">
            <button class="btn join-item" @click="prevStep()">上一步</button>
            <button class="btn btn-accent join-item" :disabled="!envInfoStore.EnvVarsCanRegister" @click="registerVars()">注册</button>
            <button class="btn btn-primary join-item" :disabled="!envInfoStore.EnvCheckCanNext" @click="nextStep()">下一步</button>
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
    router.push( { path: 'envcheck' } );
}

function nextStep() {
    envInfoStore.fetchData();
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
