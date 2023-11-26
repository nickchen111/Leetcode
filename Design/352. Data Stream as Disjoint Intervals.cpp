/*
352. Data Stream as Disjoint Intervals
*/

// TC:O(n) SC:O(n)
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
