const { console, timeUtils, Buffer, CommonJSModule, process, moduleCache } = InternalModuleObject
console.log(Object.keys(CommonJSModule), process.argv, process.argc, moduleCache)

const module = {
    exports: {},
};
const fun = CommonJSModule.compare('../libs/commonjs/require.js')
// fun(CommonJSModule.compare, module, module.exports);
console.log(fun, Object.keys(fun));