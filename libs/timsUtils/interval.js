const { timeUtils } = InternalModuleObject


module.exports = {
    setInterval: function (callback, interval, ...args) {
        const id = timeUtils.setInterval(callback, interval);
        return id;
    }
}