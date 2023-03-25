InternalModuleObject.moduleCache = new Map();

// 使用绝对路径作为id
function _require(pathUrl) {
    InternalModuleObject.console.log(`module: ${module.currentPath}`)
    const currentPath = pathUrl[0] === '/' ? pathUrl : `${module.currentPath}/${pathUrl}`;

    if (InternalModuleObject.moduleCache.has(currentPath))
        return InternalModuleObject.moduleCache.get(currentPath).exports;

    const currentModule = {
        exports: {},
        currentPath
    };

    console.log(`currentModule.currentPath: ${currentModule.currentPath}`)
    require(currentModule.currentPath).call(null, _require, currentModule, currentModule.exports);
    InternalModuleObject.moduleCache.set(currentPath, currentModule);
    return currentModule.exports;
}

module.exports = {
    require: _require,
};