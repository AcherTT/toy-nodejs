const { timeUtils, Buffer, CommonJSModule, process } = InternalModuleObject

function initModule() {
    const module = {
        exports: {},
    };
    const requireFunction = CommonJSModule.compare('../libs/commonjs/require.js')
    requireFunction.call(null, CommonJSModule.compare, module, module.exports);
    return module.exports['require'];
}

function initGlobal(require) {
    global['console'] = require.call(null, '../libs/console.js');
    global['setInterval'] = timeUtils.setInterval;
    global['setTimeout'] = timeUtils.setTimeout;
    global['clearTimeout'] = timeUtils.clearTimeout;
    global['clearInterval'] = timeUtils.clearInterval;
    global['Buffer'] = Buffer;
    global['process'] = process;
}

(function () {
    if (process.argc < 2)
        throw new Error('Please input the file path')
    const require = initModule();
    initGlobal(require);
    require.call(null, process.argv[1]);
})()