console.log('测试第一个打印输出');

function add(a, b) {
    return new Promise((resolve, reject) => {
        const id = timeUtils.setTimeout(() => {
            console.log('测试第三个打印输出');
            resolve({ result: a + b });
        }, 3000);

        console.log(`setTimeout id: ${id}`)
    })
}

(async function () {
    console.log('测试第二个打印输出');
    const result = await add(1, 2);
    console.log(JSON.stringify(result));
    const intervalId = timeUtils.setInterval(() => {
        console.log('测试第四个打印输出')
    }, 3000);
    console.log(`setInterval id: ${intervalId}`)

    timeUtils.setTimeout(() => {
        console.log('测试第五个打印输出')
        timeUtils.clearInterval(intervalId);
    }, 3000);
    const timeoutId2 = timeUtils.setTimeout(() => {
        console.log('理论上不会打印，除非你时间设太短')
        timeUtils.clearInterval(intervalId);
    }, 10000);
    timeUtils.clearTimeout(timeoutId2);
})();
