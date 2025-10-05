# 待办事件工具

## 快速原型

### main.cpp
1. 是程序的入口
2. 检查存储文件并读取
3. 获取用户输入并相应crud文件
4. 修改完成后，退出前，应该按照日程排序，并保存

### entity.h cpp
1. 设计表示task的类
   1. 具有id、message、待执行日期（年月日 分开存储）的字段
   2. 具有使用字符串创建对象的方法，以及控制台输入创建的方法，检查是否过期的方法
   3. 具有检查日期合法性的方法和输出为string的format和展示display的方法具有set方法
   4. 1 2015-8-9 事件实例
2. 设计表示todo_list的类
   1. 一个vector，包含task，用智能指针存储
   2. 具有crud的方法
   3. 具有排序的能力按照执行日期排序
   4. 具有过期检查的方法
   5. 输出为vector string方便写入展示
   6. 当日输出message的方法，

### list_file.h cpp
1. 读取文件流 按照id message yyyy mm dd hh mm形式
2. 将list的输出写入文件

## 未来可做
1. 日期的循环性 周待办、月待办
2. 使用sqlite存储