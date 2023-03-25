# toy-nodejs
一个玩具版本的nodejs，属于个人练习项目，仅支持持linux

## 依赖

1. v8，版本与 node18.15.0 一致使用 10.2 版本
2. libev，使用 4.0 版本


## 编译方式
```shell
mkdir build && cd build
cmake ..
make
```

## 运行方式
```shell
./Node
```

## TODO

- [x] 实现 global 对象
- [x] 实现 global->console->console->log 方法
- [x] 实现 timeUtils->setTimeout clearTimeout 方法
- [x] 实现 timeUtils->setInterval clearInterval 方法
- [x] 实现 buffer 数据结构
- [ ] 实现 path 模块
- [ ] 实现 fs 模块 readFileAsync、writeFileAsync方法
- [x] 实现 commonJs 模块加载机制
- [x] 实现 process 数据结构
- [ ] 实现 event 模块
- [ ] 实现 net 模块
- [ ] 实现 http 模块
