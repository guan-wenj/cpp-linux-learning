//
// Created by guan on 2025/10/5.
//

#ifndef CPP_LINUX_LEARNING_ENTITY_H
#define CPP_LINUX_LEARNING_ENTITY_H
#include <string>

namespace my_todo_list {

class Task {
    int id_;
    std::string message_;
    int year_;
    int month_;
    int day_;

public:
    Task(std::string  message, int year, int month, int day);
    Task(std::string input);
    bool is_expired();
    std::string display();
    std::string format();
    //set
    void set_message(const std::string& message);
    void set_time(int year,int month,int day);

    bool early_than(int year,int month,int day) const;
    bool early_than_other(const Task& other) const ;
    bool operator<(const Task& other) const;

};


}








#endif //CPP_LINUX_LEARNING_ENTITY_H