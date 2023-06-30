<template>
    <div class="container text-amber-400 stroke-indigo-400 fill-indigo-400 w-48 h-48 border-8 border-indigo-400 mx-auto my-4 p-8 rounded-full shadow-md">
        <svg class="w-full h-full" version="1.1" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 480 480">
        <!-- <rect x="0" y="0" rx="15%" ry="15%" width="480" height="480" /> -->
        <path d="M 65 68 q 650 -50 10 350" stroke-width="60" fill="none" />
        <path d="M 159 260 l 240 30" stroke-width="60" fill="none" />
        </svg>
    </div>

    <StepProgress :step="1"></StepProgress>

    <h1 class="text-2xl text-center pt-4">环境检测</h1>

    <div class="hero bg-base-100">
        <div class="hero-content text-center">
            <table class="table">
            <tr>
                <th class="w-24">操作系统</th>
                <td>{{envInfo.os.name}}</td>
            </tr>
            <tr>
                <th>控制依赖</th>
                <td>{{envInfo.fastdo.path}} <div class="badge badge-accent badge-outline">{{envInfo.fastdo.version}}</div></td>
            </tr>
            <tr>
                <th>包含架构</th>
                <td class="overflow-auto">
                    <div class="form-control flex-row">
                        <label class="label cursor-pointer justify-normal mr-2">
                            <span class="label-text">X64D</span>
                            <input type="checkbox" class="checkbox ml-1" :checked="envInfo.package.arch.X64D != null" />
                        </label>
                        <label class="label cursor-pointer justify-normal mr-2">
                            <span class="label-text">X64R</span>
                            <input type="checkbox" class="checkbox ml-1" :checked="envInfo.package.arch.X64R != null" />
                        </label>
                        <label class="label cursor-pointer justify-normal mr-2">
                            <span class="label-text">X86D</span>
                            <input type="checkbox" class="checkbox ml-1" :checked="envInfo.package.arch.X86D != null" />
                        </label>
                        <label class="label cursor-pointer justify-normal">
                            <span class="label-text">X86R</span>
                            <input type="checkbox" class="checkbox ml-1" :checked="envInfo.package.arch.X86R != null" />
                        </label>
                    </div>
                </td>
            </tr>
            <tr>
                <th>编译器名</th>
                <td>{{envInfo.compiler.name}}</td>
            </tr>
            <tr>
                <th>ＶＳ路径</th>
                <td>{{envInfo.compiler.path}}</td>
            </tr>
            <tr v-if="envInfo.compiler.VSToolsBat64">
                <th>脚本路径</th>
                <td>{{envInfo.compiler.VSToolsBat64}}</td>
            </tr>
            <tr>
                <th>环境变量</th>
                <td class="overflow-auto">
                    <div class="form-control flex-row">
                        <label class="label cursor-pointer justify-normal mr-2">
                            <span class="label-text">X64D</span>
                            <input type="checkbox" class="checkbox checkbox-primary ml-1" :checked="envInfo.envvars.arch.X64D" />
                        </label>
                        <label class="label cursor-pointer justify-normal mr-2">
                            <span class="label-text">X64R</span>
                            <input type="checkbox" class="checkbox checkbox-primary ml-1" :checked="envInfo.envvars.arch.X64R" />
                        </label>
                        <label class="label cursor-pointer justify-normal mr-2">
                            <span class="label-text">X86D</span>
                            <input type="checkbox" class="checkbox checkbox-primary ml-1" :checked="envInfo.envvars.arch.X86D" />
                        </label>
                        <label class="label cursor-pointer justify-normal">
                            <span class="label-text">X86R</span>
                            <input type="checkbox" class="checkbox checkbox-primary ml-1" :checked="envInfo.envvars.arch.X86R" />
                        </label>
                    </div>
                </td>
            </tr>
            <tr>
                <td colspan="2">
                    <table class="table table-xs">
                        <tr v-for="(varval, varname) in envInfo.envvars.vars" :key="varname">
                            <th class="w-40">{{ varname }}</th>
                            <td v-if="varval">{{ varval }}</td><td v-else class="text-error">×</td>
                        </tr>
                    </table>
                </td>
            </tr>
            </table>
        </div>
    </div>

    <div class="flex justify-center mb-2">
        <div class="join">
            <button class="btn btn-primary join-item" :disabled="!envInfoStore.EnvCheckCanNext" @click="nextStep()">下一步</button>
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

function nextStep()
{
    router.push( {
        path: 'envvars',
    } );
    //console.log(envInfoStore.envCheckNext);
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
