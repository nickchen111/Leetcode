/*
146. LRU Cache
*/

class LRUCache {
private:
    //盯著這三個數據結構看是否都update了
    unordered_map<int,int>key2val;
    list<int>List;//雙鍊錶結構
    unordered_map<int, list<int>::iterator>key2iter;  //   hash table存的是list的位置
    int cap;
public:
    LRUCache(int capacity) {
        this->cap = capacity;
    }
    
    int get(int key) {
        if(key2val.find(key) == key2val.end()){
            return -1;
        }
        //因為訪問了 所以要把他往前移 key2val不用動 因為沒有變更val
        auto iter = key2iter[key];
        List.erase(iter);
        List.push_back(key);
        key2iter.erase(key);
        key2iter[key] = --List.end();//就會移到end前一個位置

        return key2val[key];
    }
    
    void put(int key, int value) {
        if(get(key) != -1){//代表有此數值了 且操作這同時他已經自動排好位置了讚讚
            key2val[key] = value;
            return;
        }

        if(key2val.size() == cap){
            int keydel = *List.begin();
            List.erase(List.begin());//那就三個都處理一下
            key2iter.erase(keydel);
            key2val.erase(keydel);
        }

        List.push_back(key);
        key2iter[key] = --List.end();
        key2val[key] = value;
        return;
    }
};
/*
对于get函数，首先考虑是否在key2val中有key的记录，没有就只能退出。然后在List里删除key，并把key再装在List的末尾。
显然，访问List里的Key需要通过key2iter[Key],最后也要更新key2iter[Key]。
对于put函数，首先调用get(key)查看是否已经存在。如果已经存在，则只需要更新key2val[key]。
另外注意到一个trick，在调用get(key)的时候，已经更新了key在List中的顺序，所以这个情况下，就可以安心退出了。
如果get(key)==-1，那么就需要加入一个key。两种情况：一种是List.size()<cap，那么直接加key（需要添加key2val[key]、添加List、添加key2iter[key]）；
另一种是List.size()==cap，那么需要先删除一个元素，再加上key.删除key需要的操作有：确定要删除的keyDel（就在List最首），在List里删除keyDel，在key2val里删除keyDel.
总之，既然建立了三个数据结构 key2val, List, key2iter，那么在每一步操作的时候，注意都要更新这三个东西，就不会遗漏操作了。对于460题也是如此。
tc: o(1) sc: o(cap)
*/

// la 的 此路c++不通==
class LRUCache {
private:
    int cap;
    unordered_map<int, int> cache;
public:
    LRUCache(int capacity) {
        this->cap = capacity;
    }
    
    int get(int key) {
        if(cache.find(key) == cache.end()){
            return -1;
        }
        makeRecently(key);
        return cache[key];
    }
    
    void put(int key, int value) {
        if(cache.find(key) != cache.end()){//key已經存在了 
            cache[key] = value; //修改key的值 即使一樣也修改
            makeRecently(key); //將KEY改成最近使用
            return;
        }
        
        if(cache.size() >= cap){//容量不夠了
            int oldestkey = cache.begin()->first; //所以迭代器是指標餒
            cache.erase(oldestkey);//刪除舊的key 此刪除是連hash map上跟linked list一起刪除
        }
        cache[key] = value;//新增新的key
    }
private:
    void makeRecently(int key){
        int val = cache[key];
        cache.erase(key);
        cache[key] = val;
    }
};
