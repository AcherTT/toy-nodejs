const CHAR_FORWARD_SLASH = 47;

function validateString(value, name) {
    if (typeof value !== 'string')
        throw new Error(`${name} must be a string`);
}

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

    isAbsolute(path) {
        validateString(path, 'path');
        return path.length > 0 && path.charCodeAt(0) === CHAR_FORWARD_SLASH;
    },

    trailingSeparator(path) {
        validateString(path, 'path');
        const last = path.charCodeAt(path.length - 1);
        return last === CHAR_FORWARD_SLASH;
    },

    isPathSeparator(code) {
        return code === CHAR_FORWARD_SLASH;
    },

    normalizeString(path, allowAboveRoot, separator) {
        let res = '';
        let lastSegmentLength = 0;
        let lastSlash = -1;
        let dots = 0;
        let code;
        for (let i = 0; i <= path.length; ++i) {
            if (i < path.length)
                code = path.charCodeAt(i);
            else if (this.isPathSeparator(code))
                break;
            else
                code = CHAR_FORWARD_SLASH;
            if (this.isPathSeparator(code)) {
                if (lastSlash === i - 1 || dots === 1) {
                    // NOOP
                } else if (lastSlash !== i - 1 && dots === 2) {
                    if (res.length < 2 ||
                        lastSegmentLength !== 2 ||
                        res.charCodeAt(res.length - 1) !== CHAR_DOT ||
                        res.charCodeAt(res.length - 2) !== CHAR_DOT) {
                        if (res.length > 2) {
                            const lastSlashIndex = res.lastIndexOf(separator);
                            if (lastSlashIndex === -1) {
                                res = '';
                                lastSegmentLength = 0;
                            } else {
                                res = res.slice(0, lastSlashIndex);
                                lastSegmentLength = res.length - 1 - res.lastIndexOf(separator);
                            }
                            lastSlash = i;
                            dots = 0;
                            continue;
                        } else if (res.length === 2 || res.length === 1) {
                            res = '';
                            lastSegmentLength = 0;
                            lastSlash = i;
                            dots = 0;
                            continue;
                        }
                    }
                    if (allowAboveRoot) {
                        res += res.length > 0 ? `${separator}..` : '..';
                        lastSegmentLength = 2;
                    }
                } else {
                    if (res.length > 0)
                        res += `${separator}${path.slice(lastSlash + 1, i)}`;
                    else
                        res = path.slice(lastSlash + 1, i);
                    lastSegmentLength = i - lastSlash - 1;
                }
                lastSlash = i;
                dots = 0;
            } else if (code === CHAR_DOT && dots !== -1) {
                ++dots;
            } else {
                dots = -1;
            }
        }
        return res;
    },

    normalize(path) {
        validateString(path, 'path');
        if (path.length === 0)
            return '.';
        const isAbsolute = this.isAbsolute(path);
        const trailingSeparator = this.trailingSeparator(path);
        // Normalize the path
        let newPath = this.normalizeString(path, !isAbsolute, '/');
        if (newPath.length === 0 && !isAbsolute)
            newPath = '.';
        if (newPath.length > 0 && trailingSeparator)
            newPath += '/';
        if (isAbsolute)
            return `/${newPath}`;
        return newPath;
    },

    resolve(...args) {
        let resolvedPath = '';
        let resolvedAbsolute = false;
        for (let i = args.length - 1; i >= -1 && !resolvedAbsolute; i--) {
            let path;
            if (i >= 0)
                path = args[i];
            else
                path = process.pwd;
            validateString(path, 'path');
            if (path.length === 0) {
                continue;
            }
            resolvedPath = `${path}/${resolvedPath}`;
            resolvedAbsolute = this.isPathSeparator(path.charCodeAt(0));
        }
        resolvedPath = this.normalizeString(resolvedPath, !resolvedAbsolute, '/');
        return (resolvedAbsolute ? '/' : '') + resolvedPath || '.';
    }
}