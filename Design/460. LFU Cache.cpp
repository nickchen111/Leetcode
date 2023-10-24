/*
460. LFU Cache
*/

class LFUCache {
    unordered_map<int, int> key2freq;//方便分類 freq
    unordered_map<int, list<int>::iterator> key2iter; //  方便增刪 連到的是每個key對應的freq中的各個位置
    unordered_map<int, int> key2val; //方便 o(1)找到值
    unordered_map<int, list<int>> freq2list; //方便從freq得知此freq 有什麼key value
    int minfreq, cap;
public:
    LFUCache(int capacity) {
        minfreq = 0;
        this->cap = capacity;
    }
    
    int get(int key) {
        if(key2val.find(key) == key2val.end()){// 找不到的情況下
            return -1;
        }
        //如果有的話 key2freq 要＋＋ key2iter位置要改道f+1的最後面 freqlist也要改 如果讓minfreq沒東西也要改
        //從圖像思考中從下面改到上面
        /*
             key
              |
            freq
              |
            linked list(key value) 
        */
        int f = key2freq[key];//確定目前在的freq

        auto iter = key2iter[key];//得知位置
        freq2list[f].erase(iter);//去把此位置刪掉
        freq2list[f+1].push_back(key);
        key2iter.erase(key);
        key2iter[key] = --freq2list[f+1].end();
        key2freq[key] = f+1;

        if(freq2list[minfreq].size() == 0){
            minfreq += 1;
        }

        return key2val[key];
    }
    
    void put(int key, int value) {
        if (cap==0) return;
        if(get(key) != -1){
            key2val[key] = value;
            return;
        }

        //刪除最舊的minfreq
        if(key2val.size() == cap){
            int oldestkey = freq2list[minfreq].front();
            freq2list[minfreq].erase(key2iter[oldestkey]);//寫成freq2list[minfreq].pop_front();更好
            key2iter.erase(oldestkey);
            key2val.erase(oldestkey);
            key2freq.erase(oldestkey);
        }
        freq2list[1].push_back(key);
        key2iter[key] = --freq2list[1].end();
        key2val[key] = value;
        key2freq[key] = 1;
        minfreq = 1;
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */


 /*
本题用到了STL里的一个新的数据结构，list。list和vector的用法差不多，
但其在内存中的存储并不是线性的，而是链表状的，所以它的插入、删除都很方便（因为已经被封装好了，我们不必实现链表插入、删除的细节）。
删除list中一个元素，可以有这些操作：pop_front(), pop_back(), erase(iterator);     
在list中加入一个元素，push_back(value), 其对应的iterator就是 --List.end()
hash map key -> freq -> linked list(key value)
 */
