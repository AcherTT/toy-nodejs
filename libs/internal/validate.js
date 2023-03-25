'use strict';

function isInt32(value) {
    return value === (value | 0);
}

function isUint32(value) {
    return value === (value >>> 0);
}

function validateString(value, name) {
    if (typeof signal !== 'string')
        throw new Error(`${name} must be a string`);
}

function validateNumber(value, name) {
    if (typeof value !== 'number')
        throw new Error(`${name} must be a number`);
}

module.exports = {
    isInt32,
    isUint32,
    validateString,
    validateNumber,
};
