import { reactive, computed } from 'vue';
import { defineStore } from 'pinia';
import axios from 'axios';

export const useEnvInfoStore = defineStore( 'EnvInfo', () => {
    const envInfo = reactive( {
        os: {
            name: ''
        },
        fastdo: {
            path: '',
            version: '',
        },
        package: {
            base: null,
            include: null,
            arch: {
                X64D: null,
                X64R: null,
                X86D: null,
                X86R: null
            },
            check: false
        },
        compiler: {
            name: '',
            path: '',
            VSToolsBat64: '',
            VSToolsBat32: '',
            check: false
        },
        envvars: {
            vars: {
                FASTDO_BASE: null,
                FASTDO_INCLUDE: null,
                FASTDO_X64D_BIN: null,
                FASTDO_X64D_LIB: null,
                FASTDO_X64R_BIN: null,
                FASTDO_X64R_LIB: null,
                FASTDO_X86D_BIN: null,
                FASTDO_X86D_LIB: null,
                FASTDO_X86R_BIN: null,
                FASTDO_X86R_LIB: null
            },
            arch: {
                X64D: false,
                X64R: false,
                X86D: false,
                X86R: false
            },
            check: false
        },
    } );

    function fetchData() {
        axios.get('/api/get_compiler_info').then( ( value ) => {
            envInfo.compiler = value.data;
            //console.log(value.data);
        } );
        axios.get('/api/get_fastdo_info').then( ( value ) => {
            envInfo.fastdo = value.data;
            //console.log(value.data);
        } );
        axios.get('/api/get_package_info').then( ( value ) => {
            envInfo.package = value.data;
            //console.log(value.data);
        } );
        axios.get('/api/get_os_info').then( ( value ) => {
            envInfo.os = value.data;
            //console.log(value.data);
        } );
        axios.get('/api/get_envvars_info').then( ( value ) => {
            envInfo.envvars = value.data;
            //console.log(value.data);
        } );
    }

    fetchData();

    const envCheckNext = computed( () => {
        return envInfo.compiler.check && envInfo.package.check;
    } );

    return { envInfo, fetchData, envCheckNext };
} );
