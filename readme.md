### HLW聊天室——使用Linux C网络编程技术开发的多人聊天工具

#### 原作者链接

[fujie-xiyou/chat_room: 聊天室 -- 17年暑假项目(Linux C网络编程) (github.com)](https://github.com/fujie-xiyou/chat_room)

#### 环境

mysql 8.4.0

gcc 8.3.1(red hat 8.3.1)    原作者的编译器版本较低,会有一些警告,当然该聊天室当前还是存在一些问题的

centos7
在该环境下未报错,所有的警告以及报错都修改了,原作者的数据库版本较低,所以sql语句有一两处需要修改 该聊天室 支持 mysql 8的各个版本

#### 更新日志

之前拿来做课设的时候,是存在一些bug的,修改了一部分,目前还是有一些bug的,已经忘记了

后来,本来打算二开这个聊天室的,但是在测试其他主机的客户端连接服务端的时候,连接失败,也不知道是为什么
关闭防火墙也不行,开通了对应端口,且用基本的客户端程序能够连上服务端,后来socket的问题解决了,还是会莫名其妙的突然的挂掉,或许原本的框架就有问题吧,网络程序不是很好处理这个问题

当时花了两三天时间,没能解决其他主机客户端连接服务端的问题,就放弃了

最终决定,重新写一个聊天室
完善更多功能,实现其他主机能通过客户端正常使用

以及实现
分布式
线程池
I/O复用

还会实现部分数据访问接口,这样做只是为了实现类似数据中心的功能
正式开始之后,会把项目连接挂在这个仓库
2024.10.19

#### 安装部署

- 克隆

``` shell?linenums
git clone https://github.com/fujie-xiyou/chat_room.git
```

- 服务器端

``` shell?linenums
cd chat_room/Server
make
```

然后将`chat_room.sql`导入到你的数据库中，并修改`config.json`中的数据库信息<br>
最后`./chat_room_srv`
没有报错的话服务器就启动成功了

 - 客户端

``` shell?linenums
cd chat_room/Client
make
```

然后在config.json中修改服务器地址<br>
最后`./chat_room_cli`<br>
请先注册一个账号

####  演示视频

[聊天室视频演示](https://www.github.com/fujie-xiyou/Graph-bed/raw/master/小书匠/聊天室.md/聊天室演示.mp4)

####  项目概述

- 本项目是一个使用Linux C网络编程技术开发的字符界面聊天室，基本功能有，用户注册登录，添加好友，私聊，创建群聊，邀请好友加入群聊，群聊，聊天记录查看，文件传送等。

#### 项目设计

- 本项目基于C/S模型设计，分为客户端和服务器端两个部分，客户端直接连接到服务器，与服务器双向交换数据，服务器端用于接收客户端发来的消息，并转发给目标用户，所有数据的持久化工作也均由服务器端完成。
- 项目代码采用分层的思想进行设计，客户端由界面层和业务逻辑层(请求层)构成，服务器端由业务逻辑层和持久化层构成，代码结构如图：<br>
  ![代码结构](https://www.github.com/fujie-xiyou/Graph-bed/raw/master/小书匠/聊天室.md/代码结构.png)
- 数据库设计
  - 本项目开发时尚未系统学过数据库相关课程，但是后来审视本项目数据库设计，居然是符合BC范式的。
  - 项目数据库部分示例如图所示<br>
    ![数据库设计](https://www.github.com/fujie-xiyou/Graph-bed/raw/master/小书匠/聊天室.md/聊天室数据库设计.png)
- 文件传输功能设计
  由于本项目客户端与服务器端采用JSON进行数据交互，对于文件传输需要做特殊处理，因此在此简单介绍一下文件传输的处理方式，先上图：
  ![文件传输处理](https://www.github.com/fujie-xiyou/Graph-bed/raw/master/小书匠/聊天室.md/聊天室文件处理过程.png)
- 如图在当用户输入要发送的文件名后，系统使用open()系统调用打开文件，然后使用read()系统调用读取指定字节的文件内容，将read的返回值记录在数据包的size字段，然后将读取到的文件内容使用base64转码，将得到的结果记录在数据包的data字段中，然后将数据包发给接收方，再根据read返回值的大小判断文件是否全部发送完成，如果read返回值小于read的大小参数，则关闭文件，否则继续read转码发送。
- 接收方收到文件包后，将data中的数据解码为二进制，然后根据size的值将存储data的转码结果的buff中的数据追加写入文件中。