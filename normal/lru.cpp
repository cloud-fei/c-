#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;

class LRUCache{
private:
    int capacity;
    unordered_map<int, list<pair<int, int>>::iterator> cacheMap;  // 使用unordered_map存储键值对
    list<pair<int, int>> cacheList;  // 使用双向链表维护访问顺序

public:
    LRUCache(int capacity){
        this->capacity = capacity;
    }

    int get(int key){
        // 更新访问顺序，将当前节点移到链表头部
        if (cacheMap.find(key) != cacheMap.end()) {
            cacheList.splice(cacheList.begin(),cacheList, cacheMap[key]);
            return cacheMap[key]->second;
        }
        return -1;
    }

    void put(int key, int value){
        // 如果key已存在，更新value，并将当前节点移到链表头部
        if (cacheMap.find(key) != cacheMap.end()) {
            cacheMap[key]->second = value;
            cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
            return;
        }

         // 达到容量上限，删除最久未使用的节点（链表尾部）
        if (cacheMap.size() == capacity) {
            int leastUseKey = cacheList.back().first;
            cacheMap.erase(leastUseKey);
            cacheList.pop_back();
        }

        // 将新节点插入链表头部
        cacheList.push_front(make_pair(key, value));
        cacheMap[key] = cacheList.begin();
    }
};

int main(){
    LRUCache cache(2);

    cache.put(1, 1);
    cache.put(2, 2);
    std::cout << cache.get(1) << std::endl;     //1

    cache.put(3, 3);
    std::cout << cache.get(2) << std::endl;    // -1

    cache.put(4, 4);
    std::cout << cache.get(1) << std::endl;    //-1
    std::cout << cache.get(3) << std::endl;    //3
    std::cout << cache.get(4) << std::endl;    //4

    return 0;

}