module.exports = {
    join(...args) {
        if (args.length === 0)
            return '.';
        let joined;
        for (var i = 0; i < args.length; ++i) {
            const arg = args[i];
            validateString(arg, 'path');
            if (arg.length > 0) {
                if (joined === undefined)
                    joined = arg;
                else
                    joined += `/${arg}`;
            }
        }
        if (joined === undefined)
            return '.';
        return posix.normalize(joined);
    },
}