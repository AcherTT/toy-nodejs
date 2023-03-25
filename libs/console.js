const { console } = InternalModuleObject

module.exports = {
    log(...args) {
        const content = args.map(arg => {
            if (typeof arg === 'object')
                return JSON.stringify(arg);
            if (typeof arg === 'function')
                return arg.toString();
            if (typeof arg === 'symbol')
                return arg.toString();
            return arg;
        }).join(' ');
        console.log(content);
    },
}