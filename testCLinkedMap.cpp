#include <map>
#include <list>
#include <vector>
#include <chrono>
#include <string>
#include <thread>
#include <iostream>
#include <unordered_map>
#include "CLinkedMap.hpp"
#include "CLinkedLowMap.hpp"
#include "CLinkedHashMap.hpp"

inline bool hasBitmap(const std::vector<char> &vBitmap, int pos)
{
    std::vector<char>::size_type charPos = pos / 8;
    if (charPos >= vBitmap.size())
        return false;
    int bitPos = 7 - pos % 8;
    return vBitmap[charPos] & (1 << bitPos);
}

class Base
{
public:
    int age;
    std::string name;
};

int test01()
{
    std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
    std::map<std::string, Base> linkedHashMap;
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
    std::cout << "map Elapsed time: " << elapsed.count() << "s" << std::endl;
    for (auto it = linkedHashMap.begin(); it != linkedHashMap.end(); ++it)
    {
        std::cout << it->first << ":" << it->second.name << " " << it->second.age << std::endl;
    }
    return 0;
}
int test02()
{
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
int test03()
{
    std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
    CLinkedHashMap<std::string, Base> linkedHashMap;
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
    std::cout << "CLinkedHashMap Elapsed time: " << elapsed.count() << "s" << std::endl;
    for (auto it = linkedHashMap.begin(); it != linkedHashMap.end(); ++it)
    {
        std::cout << it->first << ":" << it->second.name << " " << it->second.age << std::endl;
    }
    return 0;
}
int test04()
{
    std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
    CLinkedLowMap<std::string, Base> linkedLowMap;
    for (int i = 0; i < 100 * 10000; i++)
    {
        linkedLowMap["2"].age = 2;
        linkedLowMap["2"].name = "a2";
        linkedLowMap["1"].age = 1;
        linkedLowMap["1"].name = "a1";
        linkedLowMap["4"].age = 4;
        linkedLowMap["4"].name = "a4";
        linkedLowMap["5"].age = 5;
        linkedLowMap["5"].name = "a5";
        linkedLowMap["3"].age = 3;
        linkedLowMap["3"].name = "a3";
    }
    std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "CLinkedLowMap Elapsed time: " << elapsed.count() << "s" << std::endl;
    for (auto it = linkedLowMap.begin(); it != linkedLowMap.end(); ++it)
    {
        std::cout << it->first << ":" << it->second.name << " " << it->second.age << std::endl;
    }
    return 0;
}

int main()
{
    std::cout << "original order: 2 1 4 5 3" << std::endl;
    std::thread t1(test01);
    std::thread t2(test02);
    std::thread t3(test03);
    std::thread t4(test04);
    // system_clock 是系统的时钟；因为系统的时钟可以修改；甚至可以网络对时；所以用系统时间计算时间差可能不准。
    // steady_clock 是单调的时钟，相当于教练手中的秒表；只会增长，适合用于记录程序耗时；
    // high_resolution_clock 是当前系统能够提供的最高精度的时钟；它也是不可以修改的。相当于 steady_clock 的高精度版本。
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    return 0;
}
