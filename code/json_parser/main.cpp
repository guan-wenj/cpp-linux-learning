//
// Created by guan on 2025/10/4.
//
#include <iostream>
#include "json/json.h"
using  namespace mercury::json;

int main() {
    // Json v1;
    // Json v2=true;
    // Json v3=78;
    // Json v4=1.23;
    // Json v5="hello";
    // Json v6=v5;
    //
    //
    // bool v7=v2;
    // int v8=v3;
    // double v9=v4;
    // std::string v10=v5;

    // Json obj;
    // obj["bool"]=true;
    // obj["int"]=123;
    // obj["double"]=3.14;
    // obj["st"]="hello";
    // std::cout<<obj.to_string()<<std::endl;
    Json arr;
    arr[0]=true;
    arr[1]=2;
    arr[2]=1.58;
    arr[3]="dqa";
    for (auto it =arr.begin(); it != arr.end(); ++it) {
        std::cout<<(*it).to_string()<<std::endl;
    }


    return 0;
}