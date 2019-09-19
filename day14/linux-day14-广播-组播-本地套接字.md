## linux-day14-广播-组播-本地套接字

### 1. 学习目标

### 2. tcp udp 使用场景

* tcp使用场景
  * 对数据安全性要求高的时候
    * 登录数据的传输
    * 文件传输
  * http协议
    * 传输层协议--tcp
* udp使用场景
  * 效率高 -- 实习性要求比较高
    * 视频聊天
    * 通话
  * 有实力的大公司
    * 使用udp
    * *在应用层自定义协议,做数据校验*

### 3 . 广播

* 广播(只适用于udp)

  * 服务器

    * 创建套接字 -- `socket`

    * fd绑定服务器IP和端口

    * 初始化客户端IP和端口

      ```c
      struct sockaddr_in cli;
      cli.sin_famliy = AF_INET;
      cli.sin_port = htons(9898);
      inet_pton(AF_INET, "xxx.xxx.123.255", &cli.sin_addr.s_addr) //必须是广播的ip地址
      ```

    * 发送数据

      * `sendto(fd, buf, len, 0)`

    * 设置广播权限

      * `setsockopt();`

  * 客户端

    * 创建套接字
    * **显式绑定IP和端口(为什么要绑定ip)**
      * bind(); 
    * 接收数据 -- 接受server的数据
      * recvfrom();

  * 适用范围

    * **只适用于局域网**

  * 广播地址和网关

    | 广播地址                         | 网关                                                         |
    | -------------------------------- | ------------------------------------------------------------ |
    | xxx.xxx.123.255  --255是广播地址 | xxx.xxx.123.1 ---1是网关地址,相当于一扇门                    |
    | 255.255.255.255                  | xxx.xxx.122.1 ---123网段想要和122网段通信,都要经过这两个网关 |

    

  * ![1568792069120](/home/sanjay/DATA/Learning_workspace/Learning_cpp/4_Linux_Learning/day14/assets/1568792069120.png)



### 4. 组播(多播)

* 使用范围

  * 局域网
  * internet

* 结构体

  ```cpp
            //美人儿去哪
  struct ip_merqn
  {
      //组播组的ip地址
      struct in_addr imr_multiaddr;
      //本地某一网络设备接口的ip地址
      struct in_addr imr_interface;
      int imr_ifindex; //网卡编号
  };
  struct in_addr
  {
      in_addr_t s_addr;
  };
  ```

* 组播地址

  * 224.0.0.0~224.0.0.255

  * 239.0.0.0~239.255.255.255

    本地管理组播地址,仅在特定的本地范围内有效

* 服务器端和客户端操作

  ![1568858751948](/home/sanjay/DATA/Learning_workspace/Learning_cpp/4_Linux_Learning/day14/assets/1568858751948.png)



### 5. 本地套接字

* 本地套接字

  * 文件格式

    * 管道:p
    * 套接字:s

    上面两者都是伪文件,无论对他们进行任何操作,文件的大小都一样.

    **因为他们都是在内核缓冲区进行操作的.**

    * 使用有名管道进行没有血缘关系的进程间通信流程

      ![1568860373404](/home/sanjay/DATA/Learning_workspace/Learning_cpp/4_Linux_Learning/day14/assets/1568860373404.png)

  * 服务器端

    * 创建套接字

      ```c
      int lfd = socket(AF_LOCAL, SOCK_STREAM, 0);
      ```

    * 绑定

      ```c
      struct sockaddr_un serv;
      serv.sun_family = AF_LOCAL;
      strcpy(serv.sun_path, "server.socket"); //---现在还不存在
      bind(lfd, (struct sockaddr*)&serv, len); //---绑定成功之后套接字文件被创建
      ```

      ![1568860976315](/home/sanjay/DATA/Learning_workspace/Learning_cpp/4_Linux_Learning/day14/assets/1568860976315.png)

      其中结构体`struct sockaddr_un`的具体结构如下:

      ```c
      头文件: sys/un.h
      #define UNIX_PATH_MAX 108
      struct sockaddr_un{
      	__kernel_sa_family sun_family;
      	char sun_path[UNIX_PATH_MAX];
      };
      ```

    * 设置监听

      ```c
      listen();
      ```

    * 等待接收连接请求

      ```c
      struct sockaddr_un client;
      int len = sizeof(client);
      int cfd = accept(lfd, &client, &len);
      ```

    * 通信

      * `send();`
      * `recv();`

    * 断开连接

      * `close(cfd);`
      * `close(lfd);`

  * 客户端

    * 创建套接字

      ```c
      int fd = socket(AF_LOCAL, SOCK_STREAM, 0);
      ```

    * 绑定一个套接字文件

      ```c
      struct sockaddr_un client;
      client.sun_family = AF_LOCAL;
      strcpy(client.sun_path, "client.socket");  //现在还不存在
      bind(fd, (struct sockaddr*)&client, sizeof(client)); //--绑定成功后套接字文件创建
      ```

    * 连接服务器

      ```c
      struct sockaddr_un serv;
      serv.sun_family = AF_LOCAL;
      strcpy(serv.sun_path, "server.socket"); //现在还不存在
      connect(fd, (struct sockaddr*)&serv, sizeof(serv));
      ```

    * 通信

      * `recv();`
      * `send();`

    * 关闭

      * `close(fd);`

  * 本地套接字进程通信流程

    ![1568862161254](/home/sanjay/DATA/Learning_workspace/Learning_cpp/4_Linux_Learning/day14/assets/1568862161254.png)

### 6. 心跳包

* 判断客户端和服务端是否处于连接状态

* 心跳机制

  * 不会携带大量的数据
  * 每隔一段时间: 服务器-->客户端 /  客户端-->服务器  发送一个数据包

* 心跳包看成一个协议

  * 应用层协议

* 判断网络是否断开

  * 有多个连续的心跳包没收到/没有回复 ---> 关闭通信的套接字

* 重连

  * 重新初始化套接字
  * 继续发送心跳包

* 乒乓包

  * 比心跳包携带的数据多一些
  * 除了知道连接是否存在,还能获取一些信息

* 例子: `客户端给服务器发1, 服务器回复2`

  ![1568874582328](/home/sanjay/DATA/Learning_workspace/Learning_cpp/4_Linux_Learning/day14/assets/1568874582328.png)