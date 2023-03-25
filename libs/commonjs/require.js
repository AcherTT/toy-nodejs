InternalModuleObject.moduleCache = new Map();

// TODO 临时使用路径作为 key，后续需要使用 module id
function _require(pathUrl) {
    if (InternalModuleObject.moduleCache.has(pathUrl))
        return InternalModuleObject.moduleCache.get(pathUrl);

    const _module = {
        exports: {},
    };
    require(pathUrl).call(null, _require, _module, _module.exports);
    return _module.exports;
}

module.exports = {
    require: _require,
};