#include <iostream>
#include <list>
#include <unordered_map>

// LRU 缓存类
// 突然发现哈希表的实际应用原理跟内存映射是一样的，都是将一个大范围的数据映射到一个
// 小范围的数据，因此就必然会有冲入（哈希冲突），所以每一个位置都存的是一个链表
class LRUCache 
{
private:
    int capacity; // 缓存容量
    std::list<std::pair<int, int>> cacheList; // 双向链表，用于存储缓存项，按访问顺序排列
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> cacheMap; // 哈希表，用于快速查找缓存项
public:
    // 构造函数，初始化缓存容量
    LRUCache(int capacity) : capacity(capacity) {}

    // 获取缓存项
    int get(int key) 
    {
        auto it = cacheMap.find(key);
        if (it != cacheMap.end()) 
        {
            // 如果 key 存在，将该项移到链表头部，表示最近访问
            std::pair<int, int> kv = *it->second;
            cacheList.erase(it->second);
            // 这里为什么不适用push_back()呢？是因为放在头部可以直接使用begin()来获取位置
            cacheList.push_front(kv);
            cacheMap[key] = cacheList.begin();
            return kv.second;
        }
        return -1; // key 不存在
    }

    // 插入或更新缓存项
    void put(int key, int value) 
    {
        auto it = cacheMap.find(key);
        if (it != cacheMap.end()) 
        {
            // 如果 key 已存在，更新其值并移到链表头部
            cacheList.erase(it->second);
        } 
        else if (cacheList.size() == capacity) 
        {
            // 如果缓存已满，移除链表尾部的元素（最近最少使用的元素）
            int lastKey = cacheList.back().first;
            cacheMap.erase(lastKey);
            cacheList.pop_back();
        }
        // 插入新的缓存项到链表头部
        cacheList.push_front({key, value});
        cacheMap[key] = cacheList.begin();
    }
};