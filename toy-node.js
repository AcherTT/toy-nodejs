console.log('测试第一个打印输出');
console.log('测试第二个打印输出');

async function add(a, b) {
    return new Promise((resolve, reject) => {
        resolve(a + b);
        console.log('测试第三个打印输出');
    })
}

(async function () {
    const result = await add(1, 2);
    console.log(JSON.stringify(result));
})();   