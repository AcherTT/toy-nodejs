console.log(
    '测试第一个打印输出',
    new Date(),
    {
        info: '测试object打印',
        arr: [1, 2, '23'],
        object: { info: '第二层' },
        bool: true
    }
);

function add(a, b) {
    return new Promise((resolve, reject) => {
        const id = timeUtils.setTimeout(() => {
            resolve({ result: a + b });
        }, 3000);

        console.log(`setTimeout id: ${id}`)
    })
}

async function timesTest() {
    console.log('测试函数打印：', add);
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
}

function testBuffer() {
    const buffer = Buffer.from('测试buffer');
    console.log(buffer.toString());
}

(async function () {
    // 定时器测试
    await timesTest();

    // buffer测试
    testBuffer();
})();
