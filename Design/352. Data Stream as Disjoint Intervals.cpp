/*
352. Data Stream as Disjoint Intervals
*/

// Greedy Interval TC:O(nlgn + m) SC:O(n) m為每次整理過後的區間數量
class SummaryRanges {
    using PII = pair<int,int>;
    vector<PII> arr;
public:
    SummaryRanges() {
        
    }
    
    void addNum(int value) {
        arr.push_back({value, value});
    }
    
    vector<vector<int>> getIntervals() {
        if(arr.size() == 0) return {};
        auto cmp = [](const PII& a, const PII& b){
            if(a.first != b.first) return a.first < b.first;
            else return a.second > b.second;
        };

        sort(arr.begin(), arr.end(), cmp);
        vector<vector<int>> res;

        
        int j = 1;
        for(int i = 0; i < arr.size(); i++){
            int start = arr[i].first;
            int curMax = arr[i].second;
            j = max(j, i+1);
            while(j < arr.size() && arr[j].first <= curMax+1){
                curMax = max(curMax, arr[j].second);
                j++;
            }
            res.push_back({start, curMax});
            i = j-1;
        }

        return res;
        
    }
};


// Heap TC:O(nlgn + n) SC:O(n) n 為 新增數據的多寡
class SummaryRanges {
    set<int> set;
public:
    SummaryRanges() {
        
    }
    
    void addNum(int value) {
        set.insert(value);
    }
    
    vector<vector<int>> getIntervals() {
        int start,end;
        int first = 1;
        vector<vector<int>> res;
        if(set.empty()) return {};
        
        for(auto a:set){
            if(first){
                start = a;
                end = a;
                first = 0;
                continue;
            }

            if(a == end+1){
                end = a;
            }
            else {
                res.push_back({start,end});
                start = a;
                end = a;
            }
        }
        res.push_back({start,end});
        return res;
    }
};
