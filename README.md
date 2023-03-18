# toy-nodejs
一个玩具版本的nodejs，属于个人练习项目，仅支持持linux

## 依赖

1. v8
2. libev


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
- [x] 实现 buffer 数据结构，可参考nodejs的实现方法，这是实现其余模块的基础
- [ ] 实现 fs 模块 readFileAsync、writeFileAsync方法
- [ ] 实现 commonJs 模块加载，可以基于fs模块纯js实现
- [ ] 实现 event 模块
- [ ] 实现 net 模块
- [ ] 实现 http 模块
