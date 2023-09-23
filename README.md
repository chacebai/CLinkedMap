## Introduction
A C++ header-only LinkedMap is a map that maintains insertion order, designed based on Java LinkedHashMap

## How to use
Just include the header file in your project

## For example：
`helloworld.cpp`
```
#include <map>
#include <list>
#include <vector>
#include <chrono>
#include <string>
#include <thread>
#include <iostream>
#include <unordered_map>
#include "CLinkedMap.hpp"

class Base
{
public:
    int age;
    std::string name;
};

int main()
{
    std::cout << "original order: 2 1 4 5 3" << std::endl;
    std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
    CLinkedMap<std::string, Base> linkedHashMap;
    for (int i = 0; i < 100 * 10000; i++)
    {
        linkedHashMap["2"].age = 2;
        linkedHashMap["2"].name = "a2";
        linkedHashMap["1"].age = 1;
        linkedHashMap["1"].name = "a1";
        linkedHashMap["4"].age = 4;
        linkedHashMap["4"].name = "a4";
        linkedHashMap["5"].age = 5;
        linkedHashMap["5"].name = "a5";
        linkedHashMap["3"].age = 3;
        linkedHashMap["3"].name = "a3";
    }
    std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "CLinkedMap Elapsed time: " << elapsed.count() << "s" << std::endl;
    for (auto it = linkedHashMap.begin(); it != linkedHashMap.end(); ++it)
    {
        std::cout << it->first << ":" << it->second.name << " " << it->second.age << std::endl;
    }
    return 0;
}
```

## compile
`g++ helloworld.cpp  -o helloworld -g -static -Wall -std=c++11`

## run
`./helloworld`
```
original order: 2 1 4 5 3
CLinkedMap Elapsed time: 0.810576s
2:a2 2
1:a1 1
4:a4 4
5:a5 5
3:a3 3
```

## 介绍
只需包含头文件的LinkedMap.hpp是一个可以保持插入顺序的map，它是基于Java LinkedHashMap设计的

## 如何使用
只需在项目中包含头文件

## 案例
`helloworld.cpp`
```
#include <map>
#include <list>
#include <vector>
#include <chrono>
#include <string>
#include <thread>
#include <iostream>
#include <unordered_map>
#include "CLinkedMap.hpp"

class Base
{
public:
    int age;
    std::string name;
};

int main()
{
    std::cout << "original order: 2 1 4 5 3" << std::endl;
    std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
    CLinkedMap<std::string, Base> linkedHashMap;
    for (int i = 0; i < 100 * 10000; i++)
    {
        linkedHashMap["2"].age = 2;
        linkedHashMap["2"].name = "a2";
        linkedHashMap["1"].age = 1;
        linkedHashMap["1"].name = "a1";
        linkedHashMap["4"].age = 4;
        linkedHashMap["4"].name = "a4";
        linkedHashMap["5"].age = 5;
        linkedHashMap["5"].name = "a5";
        linkedHashMap["3"].age = 3;
        linkedHashMap["3"].name = "a3";
    }
    std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "CLinkedMap Elapsed time: " << elapsed.count() << "s" << std::endl;
    for (auto it = linkedHashMap.begin(); it != linkedHashMap.end(); ++it)
    {
        std::cout << it->first << ":" << it->second.name << " " << it->second.age << std::endl;
    }
    return 0;
}
```

## 编译
`g++ helloworld.cpp  -o helloworld -g -static -Wall -std=c++11`

## 运行
`./helloworld`
```
original order: 2 1 4 5 3
CLinkedMap Elapsed time: 0.810576s
2:a2 2
1:a1 1
4:a4 4
5:a5 5
3:a3 3
```
