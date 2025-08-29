现代 C++ 与 Linux 系统编程学习计划（2025.9-2026.12）
=======================================

阶段 1：C++ 深度进阶（4 个月）
-------------------

**时间**：2025.9.1-2025.12.31  
**目标**：吃透 STL 底层与 Modern C++ 特性，建立内存安全编码思维

### 9.1-9.30（STL 深入：容器原理与实战）

**核心内容**：从底层理解容器机制，掌握性能优化技巧



* **vector 深度实践**
  
  * 重点：`reserve`预分配内存的底层逻辑（避免频繁扩容）、`shrink_to_fit`回收空间的适用场景；通过`g++ -g`编译后用`gdb`调试，观察插入 1000 个元素时`capacity`的扩容规律（通常为 “2 倍扩容”，不同编译器可能有差异）。
  * 实践：开发 “动态数组性能测试工具”——
    * 测试场景：分别用`push_back`（无预分配）、`reserve(1000)`（预分配）插入 10 万条`int`数据；
    * 指标：记录两种方式的总耗时（建议用`chrono`库精确计时），对比扩容次数对性能的影响（预分配通常可减少 90%+ 扩容开销）。

* **unordered_map 与哈希机制**
  
  * 重点：哈希表的 “桶结构” 底层；负载因子（默认 1.0）与`rehash`触发条件（`size > 桶数×负载因子`）；手动修改负载因子（如`max_load_factor(0.5)`）对冲突率的影响（低负载因子减少冲突但增加内存占用）。
  * 实践：实现 “字符串频次统计工具”——
    * 流程：生成 10 万条随机字符串（长度 5-10 位），插入`unordered_map`并统计频次；
    * 优化测试：分别在默认负载因子（1.0）与手动设置（0.5）下，统计`count`接口的平均耗时（建议用`valgrind --tool=callgrind`分析热点）。

* **STL 算法组合实战**
  
  * 重点：`sort`+`unique`+`erase`组合去重排序（`unique`仅移动重复元素到尾部，需配合`erase`删除）；`find_if`+`for_each`筛选处理（替代传统循环，代码精简 50%+）。
  * 实践：实现 LRU 缓存（基础版）——
    * 结构：`unordered_map`存键值对（O (1) 查找），`list`维护访问顺序（记录最近使用元素）；
    * 优化：用`list::splice`移动节点（避免元素拷贝，效率比 “删除 + 插入” 高 3 倍 +）。

### 10.1-10.31（Modern C++：从 C++11 到 C++20）

**核心内容**：按版本递进学习，从语法糖到底层机制，结合工程场景落地

#### 10.1-10.10（C++11：现代 C++ 基石）

* **核心特性重点**
  
  * **智能指针体系**：
    * `unique_ptr`（独占所有权）：适用场景（如资源句柄封装，`unique_ptr<FILE>`封装文件句柄，自定义删除器`[](FILE* p){fclose(p);}`实现自动关闭）；
    * `shared_ptr`（共享引用计数）：与`unique_ptr`的选择边界（多所有者场景用`shared_ptr`，单所有者用`unique_ptr`）；
    * `weak_ptr`：解决`shared_ptr`循环引用（以 “树节点父子引用” 为例：父节点用`shared_ptr`指向子节点，子节点用`weak_ptr`指向父节点，避免引用计数无法归零）。
  * **lambda 表达式**：捕获列表实战（`[=]`值捕获适合只读场景，`[&]`引用捕获适合需修改外部变量，`[this]`在类成员函数中捕获当前对象）；配合 STL 算法（如`sort`自定义排序、`for_each`批量处理）简化代码（对比传统函数对象，代码量减少 60%+）。
  * **移动语义与右值引用**：`std::move`的本质（将左值转为右值，触发移动构造 / 赋值，实现 “资源转移” 而非拷贝）；`vector`大容量数据传递测试（对比 10 万元素`push_back`拷贝与移动的耗时比，通常移动耗时仅为拷贝的 1/10）。

* **实践任务**：简易任务调度器
  
  * 结构：`vector<unique_ptr<Task>>`存储任务（`Task`为抽象基类，派生类实现具体任务），避免内存泄漏；
  * 特性应用：用 lambda 定义临时任务（如`scheduler.addTask([](){/* 打印日志 */});`）；任务队列满时用`std::move`转移数据到临时缓存，减少拷贝开销；
  * 对比测试：分别用 “原始指针 + 手动释放” 与 “智能指针” 实现，模拟 1000 次任务调度，统计内存泄漏次数（智能指针应实现 0 泄漏）。

#### 10.11-10.20（C++14：语法精简与泛型增强）

* **核心特性重点**
  
  * **泛型 lambda**：`auto`作为参数类型（如`[](auto a, auto b){return a+b;}`），支持多类型参数运算（对比 C++11 需手动写模板函数，代码量减少 50%）；
  * **返回类型推导**：`auto func(int x) { return x*2; }`（编译器自动推导返回类型）；`decltype(auto)`处理引用返回（如`decltype(auto) getRef() { return m_data; }`，正确保留引用属性）；
  * **`std::make_unique`**：替代`unique_ptr<T>(new T())`，避免裸`new`的异常安全问题（如内存分配时抛出异常，避免资源泄漏）。

* **实践任务**：优化 “动态数组工具”（基于 9 月 vector 实践）
  
  * 泛型 lambda 应用：实现通用元素运算（求和、求积，支持`int`/`double`等类型）；
  * 异常安全测试：对比`make_unique<vector<int>>(1000)`与`unique_ptr<vector<int>>(new vector<int>(1000))`在内存分配失败时的稳定性（前者可避免部分场景下的资源泄漏）；
  * 变量模板：定义跨类型扩容因子（`template<typename T> constexpr T expand_factor = T(1.5);`），支持不同精度场景（如`expand_factor<float>`用于 float 数组）。

#### 10.21-10.31（C++17/C++20：工程化与范式升级）

* **核心特性重点**
  
  * **C++17 关键特性**：
    * 结构化绑定：`auto [key, val] = *mapIter;`直接拆分`unordered_map`的键值对（对比`first`/`second`，代码可读性提升 40%+）；
    * `std::filesystem`：`path`类跨平台处理路径（`path("a/b") / "c.txt"`自动适配 Windows/Linux 路径分隔符）、`create_directories`创建多级目录（替代传统`mkdir`循环调用）；
    * `std::optional`：用`optional<int> findKey(...)`表示 “可能无结果”（替代`nullptr`或特殊值，避免歧义）。
  * **C++20 关键特性**：
    * ranges 库：`views::filter`+`views::transform`+`views::take`链式处理（如 “筛选> 10 的数→乘 2→取前 5 个”，对比传统嵌套算法，代码层级减少 3 层）；
    * `std::span`：替代 “指针 + 长度” 传参（`void process(span<int> data)`），支持边界检查（避免越界访问），兼容`vector`/ 数组 / 自定义容器；
    * concepts：自定义类型约束（如`template<std::integral T> T sum(T a, T b)`），编译期明确类型要求（报错信息比`static_assert`更友好）。

* **实践任务**：重构 “日志文本处理工具”
  
  * ranges 链式处理：`logLines | views::filter([](auto& line){return line.contains("ERROR");}) | views::transform(extractTimestamp) | views::for_each(printFormatted);`（对比 C++11 版本，代码量减少 30%+）；
  * `span`安全访问：用`span<char>`处理日志缓冲区（解析时自动检查边界，模拟 10MB 大日志测试越界报错）；
  * 综合特性：用`optional`存储解析后的时间戳（无时间戳时返回`nullopt`），用结构化绑定拆分日志 “级别 - 内容”，完整覆盖 C++11-20 核心能力。

### 11.1-11.30（内存与资源管理：进阶实践）

**核心内容**：深化现代 C++ 资源管理思维，解决工程化场景问题



* **智能指针进阶**
  
  * 重点：`shared_ptr`自定义删除器（如`shared_ptr<Socket>(new Socket(), [](Socket* s){s->close();})`管理网络连接）；`weak_ptr`在观察者模式中的应用（观察者持有被观察对象的`weak_ptr`，避免被观察对象生命周期受观察者绑定）。
  * 实践：封装 “网络连接类”——
    * RAII 机制：构造函数创建 Socket，析构函数自动关闭；
    * 连接监测：用`weak_ptr`存储连接实例，定期通过`lock()`检查连接有效性（避免访问已释放连接）。

* **移动语义与性能优化**
  
  * 重点：`std::move`在自定义类型中的应用（实现移动构造 / 赋值函数，转移成员资源）；`vector`大容量数据转移测试（对比 10MB+ 数据块的拷贝与移动耗时，移动通常可减少 95%+ 开销）。
  * 实践：“大文件数据缓冲区”——
    * 用移动语义传递缓冲区（`buffer = std::move(tempBuffer)`），避免大内存拷贝；
    * 测试：对比 “拷贝传递” 与 “移动传递” 处理 1GB 文件的总耗时（移动传递耗时应降低 50%+）。

### 12.1-12.31（阶段 1 综合实践与复盘）

* 综合项目：实现 “高性能配置文件解析器”
  * 功能：支持 JSON 格式解析，用`std::variant`存储多类型值，`filesystem`处理配置文件路径；
  * 优化：用移动语义减少数据拷贝，智能指针管理动态配置项；
  * 测试：解析 10MB 大配置文件，内存占用≤20MB，解析耗时≤500ms。
* 复盘：整理 STL 容器性能对比表、Modern C++ 特性适用场景清单。

阶段 2：Linux 工具链（2 个月）
--------------------

**时间**：2026.1.1-2026.2.29  
**目标**：掌握 Linux 下代码开发、编译、调试的高效工具链

### 1.1-1.15（高效命令与文本处理）

* **文件与代码搜索**
  
  * 核心命令：`find ./ -name "*.cpp" -exec grep "LRU" {} +`（批量搜索代码中 LRU 相关逻辑）；`rsync -av ~/code/ user@server:/home/code/`（同步代码到服务器，保留权限与软链接）；`ag`（比`grep`更快的代码搜索工具，`ag "LRU" ./src`）。

* **文本处理工具**
  
  * `awk`：`awk -F',' '{if($3>100) print $1,$2}' data.csv`（提取 CSV 第 3 列 > 100 的行，输出第 1、2 列）；
  * `sed`：`sed -i 's/old_key/new_key/g' *.ini`（批量修改所有 ini 文件中的关键字）；
  * `cut`/`sort`/`uniq`组合：`cut -d',' -f2 data.csv | sort | uniq -c`（统计第 2 列元素出现频次）。

* **实操**：用`find+grep`定位阶段 1 写的 LRU 缓存代码中`list`操作的所有位置，生成函数调用清单（`find ./ -name "*.cpp" -exec grep -n "list::" {} + > list_ops.txt`）。

### 1.16-1.31（编译调试工具链）

* **g++ 进阶**
  
  * 核心编译选项：
    * `-std=c++20`：启用 C++20 标准；
    * `-pthread`：链接线程库（支持`std::thread`）；
    * `-fsanitize=address`：启用地址 sanitizer（检测内存泄漏、越界访问）；
    * `-g`：生成调试信息，配合`gdb`使用；
    * `-O2`：开启优化（提升运行效率，保留部分调试能力）。
  * 实践：编译 LRU 缓存工具 ——
    * 命令：`g++ -std=c++20 -fsanitize=address -g lru_cache.cpp -o lru_tool`；
    * 测试：运行工具并触发缓存淘汰逻辑，用 sanitizer 检测数组越界 / 内存泄漏问题。

* **gdb 调试**
  
  * 核心指令：
    * 断点：`break cache.cpp:45 if size>1000`（缓存满时断点）；`tbreak`（临时断点，触发后自动删除）；
    * 变量监控：`watch cache_size`（当`cache_size`修改时断点）；`p *cache`（打印缓存当前状态）；
    * 调用栈：`bt`（查看当前调用栈）；`frame 3`（切换到第 3 层栈帧）。
  * 实践：调试 “缓存满时未淘汰旧数据” bug——
    * 流程：设置条件断点，监控`cache_size`与`list`元素变化，通过调用栈分析淘汰逻辑是否被正确触发。

* **valgrind 性能分析**
  
  * 核心工具：
    * `valgrind --leak-check=full ./lru_tool`（检测内存泄漏，输出泄漏点与堆栈）；
    * `valgrind --tool=callgrind ./lru_tool`（分析函数调用耗时，用`callgrind_annotate`生成报告）；
    * `valgrind --tool=cachegrind`（分析缓存命中率，优化热点代码）。

### 2.1-2.29（CMake 工程化：项目管理）

* **分目录项目结构**
  plaintext

* lru_cache/
    ├─ include/          # 头文件
    │  └─ lru_cache.h
    ├─ src/              # 源文件
    │  └─ lru_cache.cpp
    ├─ tools/            # 工具程序
    │  └─ cache_tool.cpp
    ├─ test/             # 测试用例
    │  └─ test_lru.cpp
    └─ CMakeLists.txt    # 主CMake配置
  
  

* **关键 CMake 指令**
  cmake

* cmake_minimum_required(VERSION 3.20)
   project(lru_cache VERSION 1.0)
  
  # 设置C++标准
  
   set(CMAKE_CXX_STANDARD 20)
   set(CMAKE_CXX_STANDARD_REQUIRED ON)
  
  # 头文件目录
  
   include_directories(include)
  
  # 编译静态库
  
   add_library(libcache STATIC src/lru_cache.cpp)
  
  # 编译工具程序
  
   add_executable(cache_tool tools/cache_tool.cpp)
   target_link_libraries(cache_tool PRIVATE libcache)
  
  # 编译测试用例（依赖Google Test）
  
   find_package(GTest REQUIRED)
   add_executable(test_lru test/test_lru.cpp)
   target_link_libraries(test_lru PRIVATE libcache GTest::GTest GTest::Main)
  
  # 启用测试
  
   enable_testing()
   add_test(NAME lru_test COMMAND test_lru)
  
  

* **实操**：构建项目并运行测试用例 ——
  
  * 流程：`mkdir build && cd build && cmake .. && make -j4`（并行编译）；
  * 验证：`make test`运行测试用例，确保所有模块编译通过且测试覆盖核心功能。

阶段 3：Linux 系统编程 + C++ 实战（3 个月）
------------------------------

**时间**：2026.3.1-2026.5.31  
**目标**：掌握 Linux 系统调用，结合 C++ 实现高可靠性系统工具

### 3.1-3.31（文件 IO 与进程：基础实践）

* **文件描述符管理**
  
  * 重点：用 C++ RAII 封装 fd（`unique_ptr<int>`+ 自定义删除器）：
  
  cpp

运行

* auto fd_ptr = unique_ptr<int>(
  
       new int(open("log.txt", O_WRONLY | O_CREAT, 0644)),
       [](int* p) { if (*p != -1) close(*p); delete p; }
  
   );
  
  

* 实践：“大文件分块拷贝工具”——
  
  * 功能：支持断点续传（记录已拷贝位置到临时文件）；
  * 实现：用`read`/`write`循环读写，`span`处理 4KB 缓冲区（`span<char> buf(buffer, 4096)`）；
  * 测试：拷贝 1GB 文件，对比 “分块拷贝” 与 “一次性读取” 的内存占用（分块拷贝应控制内存≤10MB）。

* **进程控制**
  
  * 重点：`fork`创建子进程（注意 “写时复制” 机制）；`waitpid`回收子进程（避免僵尸进程）；`execvp`执行外部程序（替换进程镜像）。
  
  * 实践：“日志切割工具”——
    
    * 逻辑：父进程监控日志文件大小（`stat`获取`st_size`），达 100MB 时`fork`子进程；
    * 子进程任务：用`execvp`调用`gzip`压缩旧日志（`execvp("gzip", {"gzip", "old.log", nullptr})`）；
    * 优化：父进程用`waitpid`等待子进程结束，获取退出状态（判断压缩是否成功）。

### 4.1-4.30（线程与同步：并发实践）

* **线程池实现**
  
  * 结构：
    * `vector<pthread_t>`管理工作线程；
    * `queue<function<void()>>`存储任务；
    * `mutex`+`condition_variable`实现线程安全队列（生产者 - 消费者模型）。
  * 实践：多线程日志收集器 ——
    * 功能：线程池处理日志写入（按级别分文件存储：`info.log`/`error.log`）；
    * 性能：支持 1000+ 条 / 秒写入，无日志丢失或错乱；
    * 同步：用`std::scoped_lock`保护文件写入临界区（避免手动`lock/unlock`遗漏）。

* **同步机制优化**
  
  * 重点：`std::scoped_lock`（RAII 锁，自动释放）vs `std::lock_guard`（仅支持单个锁）；`condition_variable`等待条件（避免 “虚假唤醒”，需在循环中检查条件）。
  * 实践：修复 “多线程写同一文件时的内容错乱”——
    * 问题原因：多个线程同时`write`导致数据交织；
    * 解决方案：用`scoped_lock`包裹`write`调用，确保同一时间仅一个线程写入；
    * 验证：启动 10 个线程同时写入，检查输出文件是否有乱序。

### 5.1-5.31（IPC 通信：进程间协作）

* **共享内存与信号量**
  
  * 重点：`shmget`创建共享内存（`shmget(IPC_PRIVATE, 1024*1024, IPC_CREAT | 0666)`）；`shmat`关联到进程地址空间；`sem_t`（POSIX 信号量）实现进程互斥（`sem_wait`/`sem_post`）。
  * 实践：“进程间缓存同步工具”——
    * 逻辑：多进程共享 LRU 缓存数据（共享内存存储缓存项）；
    * 同步：用信号量保护共享内存访问（读时`sem_trywait`，写时`sem_wait`）；
    * 性能测试：对比共享内存与管道的传输效率（共享内存通常比管道高 8-10 倍）。

* **其他 IPC 机制实践**
  
  * 管道（pipe）：实现父子进程单向通信（父进程写日志，子进程处理）；
  * 消息队列（msgqueue）：多进程间异步消息传递（模拟分布式任务通知）。

阶段 4：计算机网络 + Linux 网络编程（3 个月）
-----------------------------

**时间**：2026.6.1-2026.8.31  
**目标**：掌握 TCP/IP 协议与高并发网络编程，实现可靠网络服务

### 6.1-6.20（TCP/IP 与抓包：协议理解）

* **tcpdump 与 Wireshark**
  
  * 抓包命令：
    * `tcpdump -i lo port 8080 -w tcp.pcap`（抓本地 8080 端口流量，保存到文件）；
    * `tcpdump -nn 'tcp port 8080 and tcp[13] & 2 != 0'`（过滤 SYN 包，观察连接建立）。
  * 分析：用 Wireshark 打开`tcp.pcap`，标注三次握手的 SEQ/ACK 号；观察 TCP 粘包现象（单次`recv`返回多段数据，因 TCP 是字节流协议）。

* **TCP 服务器基础**
  
  * Socket 流程：`socket`（创建套接字）→`bind`（绑定端口）→`listen`（监听连接）→`accept`（接受连接）→`recv`/`send`（读写数据）→`close`（关闭连接）。
  
  * 实践：回声服务器（单连接）——
    
    * 处理粘包：用 “长度前缀法” 解析（消息前 4 字节存长度，`uint32_t`类型）；
    
    * 代码示例：

  cpp

运行

* // 读取消息长度
   uint32_t len;
   recv(conn_fd, &len, sizeof(len), 0);
   len = ntohl(len); // 网络字节序转主机字节序
   // 读取消息内容
   vector<char> buf(len);
   recv(conn_fd, buf.data(), len, 0);
  
  
  
  

### 6.21-7.31（HTTP 与客户端：应用层实践）

* **HTTP 报文解析**
  
  * 用`curl -v https://baidu.com`获取响应，拆解结构：
    
    * 请求行：`GET / HTTP/1.1`；
    * 响应头：`Status-Code: 200 OK`、`Content-Length: 1234`（消息体长度）；
    * 消息体：HTML 内容。
  
  * 实践：简易 HTTP 客户端 ——
    
    * 功能：拼接 GET 请求（请求行 + 头），`send`后`recv`响应，保存网页到本地；
    
    * 关键代码：

  cpp

运行

* string request = "GET / HTTP/1.1\r\nHost: baidu.com\r\nConnection: close\r\n\r\n";
   send(sock_fd, request.data(), request.size(), 0);
   // 循环读取响应并写入文件
  
  
  
  

### 8.1-8.31（epoll 高并发：性能优化）

* **epoll 原理与实践**
  
  * 接口：`epoll_create`（创建 epoll 实例）→`epoll_ctl`（添加 / 修改 / 删除事件）→`epoll_wait`（等待事件触发）；
  * 模式：LT 模式（水平触发，事件未处理完会反复通知，适合新手）；ET 模式（边缘触发，仅通知一次，效率更高但需一次性读完数据）。
  * 架构：Reactor 模式（事件循环 + 回调函数）——
    * `unordered_map<int, Connection>`存`fd`与连接对象映射（O (1) 查找）；
    * 事件处理：`EPOLLIN`触发时调用`recv`回调，`EPOLLOUT`触发时调用`send`回调。

* **实践**：epoll 改造回声服务器 ——
  
  * 功能：支持 100+ 并发连接；
  * 压测：用`ab -c 100 -n 10000 http://127.0.0.1:8080/`测试，QPS≥300；
  * 优化：用线程池处理消息解析（避免单线程阻塞），`fd`绑定 CPU 核心（减少缓存切换）。

阶段 5：PostgreSQL 数据库集成（2 个月）
---------------------------

**时间**：2026.9.1-2026.10.31  
**目标**：掌握数据库基础与 C++ 连接优化，实现数据持久化

### 9.1-9.30（数据库基础与部署）

* **SQL 进阶**
  
  * 事务：`BEGIN→INSERT→COMMIT`（模拟 “用户注册 + 日志记录” 原子操作，要么全成功，要么全失败）；
  * 索引：`CREATE INDEX idx_username ON users(username)`（优化查询，测试：无索引时查询耗时 100ms，有索引时≤10ms）；
  * 常用命令：`SELECT * FROM users WHERE name='test'`（查询）；`INSERT INTO users(name) VALUES('test')`（插入）。

* **Linux 部署**
  
  * 安装：`sudo apt install postgresql`（Ubuntu）；
  * 配置：
    * 修改`/etc/postgresql/14/main/pg_hba.conf`，设置本地密码登录（`local all all md5`）；
    * 重启服务：`sudo systemctl restart postgresql`；
  * 实践：创建 “用户行为日志” 表，插入 10 万条测试数据。

### 10.1-10.31（C++ 连接与优化）

* **libpqxx 库使用**
  
  * 安装：`sudo apt install libpqxx-dev`；
  * 基础操作：连接数据库（`pqxx::connection`）、执行 SQL（`pqxx::work`）、处理结果（`pqxx::result`）；
  * 实践：“用户日志入库工具”——
    * 功能：读取本地日志文件，批量插入数据库（用`INSERT ... VALUES (...), (...), ...`减少交互次数）；
    * 事务控制：每 1000 条日志作为一个事务提交（平衡性能与原子性）。

* **连接池实现**
  
  * 结构：`queue<shared_ptr<pqxx::connection>>`存储空闲连接；`mutex`保证线程安全；
  * 功能：连接超时回收（超过 5 分钟未使用则关闭）、健康检查（定期执行`SELECT 1`验证连接有效性）；
  * 测试：模拟 10 个线程并发获取连接，统计平均获取耗时（≤1ms）。

阶段 6：综合项目实战（2 个月）
-----------------

**时间**：2026.11.1-2026.12.31  
**项目**：高并发日志服务器（整合前序所有技术点）

### 11.1-11.20（核心模块开发）

* **网络接收模块**：基于 epoll 实现高并发连接（支持 500+ 并发客户端），用`span`安全处理接收缓冲区，解决 TCP 粘包问题；
* **日志解析模块**：用 C++20 ranges 库筛选 / 转换日志，结构化绑定提取关键信息（时间、级别、内容）；
* **存储模块**：结合数据库连接池，实现日志异步入库（线程池处理，不阻塞接收）。

### 11.21-12.15（优化与监控）

* **性能优化**：
  * 内存池：自定义`vector`内存分配器，减少频繁`new/delete`开销；
  * 缓存：用 LRU 缓存热点日志（如 ERROR 级别），减少数据库访问；
  * 压测：目标 QPS≥1000，平均响应时间≤50ms。
* **监控告警**：
  * 集成 Prometheus 监控（连接数、QPS、错误率）；
  * 实现磁盘满、连接超时等异常告警（写入告警日志 + 邮件通知）。

### 12.16-12.31（测试与文档）

* 全面测试：单元测试（覆盖率≥80%）、压力测试（持续 24 小时无崩溃）、异常测试（断网恢复、数据库宕机重启）；
* 文档完善：API 手册、部署指南、性能优化报告、核心模块设计文档。
