const { console } = InternalModuleObject

InternalModuleObject.moduleCache = new Map();
console.log(111, module.exports)

// TODO 临时使用路径作为 key，后续需要使用 module id
function _require(pathUrl) {
    if (InternalModuleObject.moduleCache.has(pathUrl))
        return InternalModuleObject.moduleCache.get(pathUrl);

    const module = {
        exports: {},
    };
    compare(pathUrl).call(null, _require, module, module.exports);
    return module.exports;
}

module.exports = _require;