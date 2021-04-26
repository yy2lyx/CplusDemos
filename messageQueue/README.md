### 多进程的消息队列 C++版本demo

#### 1. 功能

* 模式：适合单对单的生产消费模式；适合单对多的生产消费模式。

* 消费方式：支持多线程消费；支持多进程消费。
* 支持程序挂掉重连，同时记录offset。

#### 2. 代码使用

> 本代码基于Windows的，推荐使用vs2019编译生成代码。

* 单生产者对单消费者模式：`MultiThreadQueue`文件夹下生成即可。需要加入输入消息txt路径和指定一个中间txt路径。

* 单生产者对多消费者模式（多线程）：`MultiThreadQueue/main.cpp`文件修改如下：

```C++
//consumer(consumer_id, &ofs);

thread csm1{ consumer, "1",&ofs };
thread csm2{ consumer, "2",&ofs };
csm1.join();
csm2.join();
```

* 单生产者对多消费者模式（多进程）：

  * `MultiThreadQueue`文件夹下生成单对单消费模式的exe。
  * `MultiProcessQueue`文件夹下`main.cpp`修改exe的路径，如下：

  ```C++
  string cmdLine = "D:/setTimer.exe " + input_txt + " " + output_txt;
  ```

  

