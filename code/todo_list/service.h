/**
  ******************************************************************************
  * @file           : service.h
  * @author         : guan
  * @brief          : None
  * @attention      : None
  * @date           : 2025/10/7
  ******************************************************************************
  */


#ifndef CPP_LINUX_LEARNING_SERVICE_H
#define CPP_LINUX_LEARNING_SERVICE_H
#include "entity.h"
#include "list_file.h"
/**
 * 读取文件  清理过期  排序   弹出今日消息
 */
my_todo_list::TodoList prepare();

/***
 * 获取用户输入  crud
 */
void run(my_todo_list::TodoList& todo);

/**
 * 清理过期  排序  保存文件
 */
void  save(my_todo_list::TodoList& todo);


void add(my_todo_list::TodoList& todo);

void update(my_todo_list::TodoList& todo);

void erase(my_todo_list::TodoList& todo);

void overlook(my_todo_list::TodoList& todo);




#endif //CPP_LINUX_LEARNING_SERVICE_H