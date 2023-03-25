const value = 1;

function add(a, b) {
    return new Promise((resolve, reject) => {
        const id = setTimeout(() => {
            resolve({ result: a + b });
        }, 3000);

        console.log(`setTimeout id: ${id}`)
    })
}

exports.value = value;
exports.add = add;