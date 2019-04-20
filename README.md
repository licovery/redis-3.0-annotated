[![Build Status](https://travis-ci.org/licovery/redis-3.0-annotated.svg?branch=unstable)](https://travis-ci.org/licovery/redis-3.0-annotated)

# Redis 3.0 源码阅读

本仓库fork自黄健宏的redis 3.0源码注释。主要是个人阅读时候做些小笔记，或者修改代码风格以符合自己的阅读代码习惯。虽然工作很忙，但是会坚持阅读的。

为了防止自己瞎改代码出现问题，加入了Travis CI，保证每次提交通过自带的Test。





## 附录：各个源码文件的作用简介

| 文件                                                         | 作用                                                         |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| `adlist.c` 、 `adlist.h`                                     | 双端链表数据结构的实现。                                     |
| `ae.c` 、 `ae.h` 、 `ae_epoll.c` 、 `ae_evport.c` 、 `ae_kqueue.c` 、 `ae_select.c` | 事件处理器，以及各个具体实现。                               |
| `anet.c` 、 `anet.h`                                         | Redis 的异步网络框架，内容主要为对 socket 库的包装。         |
| `aof.c`                                                      | AOF 功能的实现。                                             |
| `asciilogo.h`                                                | 保存了 Redis 的 ASCII LOGO 。                                |
| `bio.c` 、 `bio.h`                                           | Redis 的后台 I/O 程序，用于将 I/O 操作放到子线程里面执行， 减少 I/O 操作对主线程的阻塞。 |
| `bitops.c`                                                   | 二进制位操作命令的实现文件。                                 |
| `blocked.c`                                                  | 用于实现 BLPOP 命令和 WAIT 命令的阻塞效果。                  |
| `cluster.c` 、 `cluster.h`                                   | Redis 的集群实现。                                           |
| `config.c` 、 `config.h`                                     | Redis 的配置管理实现，负责读取并分析配置文件， 然后根据这些配置修改 Redis 服务器的各个选项。 |
| `crc16.c` 、 `crc64.c` 、 `crc64.h`                          | 计算 CRC 校验和。                                            |
| `db.c`                                                       | 数据库实现。                                                 |
| `debug.c`                                                    | 调试实现。                                                   |
| `dict.c` 、 `dict.h`                                         | 字典数据结构的实现。                                         |
| `endianconv.c` 、 `endianconv.h`                             | 二进制的大端、小端转换函数。                                 |
| `fmacros.h`                                                  | 一些移植性方面的宏。                                         |
| `help.h`                                                     | `utils/generate-command-help.rb` 程序自动生成的命令帮助信息。 |
| `hyperloglog.c`                                              | HyperLogLog 数据结构的实现。                                 |
| `intset.c` 、 `intset.h`                                     | 整数集合数据结构的实现，用于优化 SET 类型。                  |
| `lzf_c.c` 、 `lzf_d.c` 、 `lzf.h` 、 `lzfP.h`                | Redis 对字符串和 RDB 文件进行压缩时使用的 LZF 压缩算法的实现。 |
| `Makefile` 、 `Makefile.dep`                                 | 构建文件。                                                   |
| `memtest.c`                                                  | 内存测试。                                                   |
| `mkreleasehdr.sh`                                            | 用于生成释出信息的脚本。                                     |
| `multi.c`                                                    | Redis 的事务实现。                                           |
| `networking.c`                                               | Redis 的客户端网络操作库， 用于实现命令请求接收、发送命令回复等工作， 文件中的函数大多为 write 、 read 、 close 等函数的包装， 以及各种协议的分析和构建函数。 |
| `notify.c`                                                   | Redis 的数据库通知实现。                                     |
| `object.c`                                                   | Redis 的对象系统实现。                                       |
| `pqsort.c` 、 `pqsort.h`                                     | 快速排序（QuickSort）算法的实现。                            |
| `pubsub.c`                                                   | 发布与订阅功能的实现。                                       |
| `rand.c` 、 `rand.h`                                         | 伪随机数生成器。                                             |
| `rdb.c` 、 `rdb.h`                                           | RDB 持久化功能的实现。                                       |
| `redisassert.h`                                              | Redis 自建的断言系统。                                       |
| `redis-benchmark.c`                                          | Redis 的性能测试程序。                                       |
| `redis.c`                                                    | 负责服务器的启动、维护和关闭等事项。                         |
| `redis-check-aof.c` 、 `redis-check-dump.c`                  | RDB 文件和 AOF 文件的合法性检查程序。                        |
| `redis-cli.c`                                                | Redis 客户端的实现。                                         |
| `redis.h`                                                    | Redis 的主要头文件，记录了 Redis 中的大部分数据结构， 包括服务器状态和客户端状态。 |
| `redis-trib.rb`                                              | Redis 集群的管理程序。                                       |
| `release.c` 、 `release.h`                                   | 记录和生成 Redis 的释出版本信息。                            |
| `replication.c`                                              | 复制功能的实现。                                             |
| `rio.c` 、 `rio.h`                                           | Redis 对文件 I/O 函数的包装， 在普通 I/O 函数的基础上增加了显式缓存、以及计算校验和等功能。 |
| `scripting.c`                                                | 脚本功能的实现。                                             |
| `sds.c` 、 `sds.h`                                           | SDS 数据结构的实现，SDS 为 Redis 的默认字符串表示。          |
| `sentinel.c`                                                 | Redis Sentinel 的实现。                                      |
| `setproctitle.c`                                             | 进程环境设置函数。                                           |
| `sha1.c` 、 `sha1.h`                                         | SHA1 校验和计算函数。                                        |
| `slowlog.c` 、 `slowlog.h`                                   | 慢查询功能的实现。                                           |
| `solarisfixes.h`                                             | 针对 Solaris 系统的补丁。                                    |
| `sort.c`                                                     | SORT 命令的实现。                                            |
| `syncio.c`                                                   | 同步 I/O 操作。                                              |
| `testhelp.h`                                                 | 测试辅助宏。                                                 |
| `t_hash.c` 、 `t_list.c` 、 `t_set.c`、 `t_string.c` 、 `t_zset.c` | 定义了 Redis 的各种数据类型，以及这些数据类型的命令。        |
| `util.c` 、 `util.h`                                         | 各种辅助函数。                                               |
| `valgrind.sup`                                               | valgrind 的suppression文件。                                 |
| `version.h`                                                  | 记录了 Redis 的版本号。                                      |
| `ziplist.c` 、 `ziplist.h`                                   | ZIPLIST 数据结构的实现，用于优化 LIST 类型。                 |
| `zipmap.c` 、 `zipmap.h`                                     | ZIPMAP 数据结构的实现，在 Redis 2.6 以前用与优化 HASH 类型， Redis 2.6 开始已经废弃。 |
| `zmalloc.c` 、 `zmalloc.h`                                   | 内存管理程序。                                               |