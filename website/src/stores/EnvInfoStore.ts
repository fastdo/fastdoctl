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

    function registerVars() {
        axios.get('/api/register_vars').then( ( value ) => {

        } );
    }

    // 环境检测页是否可进行下一步
    const EnvCheckCanNext = computed( () => {
        return envInfo.compiler.check && envInfo.package.check;
    } );

    // 变量页面是否能注册变量
    const EnvVarsCanRegister = computed( () => {
        if ( !envInfo.envvars.vars.FASTDO_BASE ) {
            if ( envInfo.package.base ) {
                return true;
            }
        }
        if ( !envInfo.envvars.vars.FASTDO_INCLUDE ) {
            if ( envInfo.package.include ) {
                return true;
            }
        }
        const archs = [ 'X64D', 'X64R', 'X86D', 'X86R' ];
        for (const arch of archs) {
            if ( !envInfo.envvars.vars['FASTDO_' + arch + '_BIN'] ) {
                if ( envInfo.package.arch[arch] ) {
                    return true;
                }
            }
            if ( !envInfo.envvars.vars['FASTDO_' + arch + '_LIB'] ) {
                if ( envInfo.package.arch[arch] ) {
                    return true;
                }
            }
        }
        return false;
    } );

    return { envInfo, fetchData, registerVars, EnvCheckCanNext, EnvVarsCanRegister };
} );
