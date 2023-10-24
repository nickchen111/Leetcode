/*
981. Time Based Key-Value Store
*/

//TC:O(lgn)底層紅黑樹 SC:O(n)
class TimeMap {
    unordered_map<string,map<int,string>> map;
public:
    TimeMap() {
        
    }
    
    void set(string key, string value, int timestamp) {
        map[key].insert({timestamp,value});//裡面就會按照時間從小到大排序
    }
    
    string get(string key, int timestamp) {
        auto it = map[key].upper_bound(timestamp);
        if(it == map[key].begin()) return "";
        it--;
        return it->second;
    }
};
