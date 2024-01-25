/*
2034. Stock Price Fluctuation 
*/

// TC:O(lgn) SC:(n)
class StockPrice {
    int time;
    unordered_map<int,int> map; // days -> price
    multiset<int> set; // price
public:
    StockPrice() {
        time = 0;
    }
    
    void update(int timestamp, int price) {
        if(map.find(timestamp) == map.end()){
            map[timestamp] = price;
            set.insert(price);
            time = max(time,timestamp);
        }
        else {
            int prevPrice = map[timestamp];
            set.erase(set.find(prevPrice));
            map[timestamp] = price;
            set.insert(price);
        }
        
    }
    
    int current() {
        return map[time];
    }
    
    int maximum() {
        return *set.rbegin();
    }
    
    int minimum() {
        return *set.begin();
    }
};

/*
紀錄股票波動 第一次傳進去的值不一定是對的 time -> price
map[times] = price
multiset<int> set;
並且記錄各種時候的最大最小值 以及最新的一天價格
*/
