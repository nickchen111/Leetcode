/*
3296. Minimum Number of Seconds to Make Mountain Height Zero
*/

// TC:O(nlgm) n = 山高 m = worker數量 SC:O(m)
class Solution {
    using LL = long long;
public:
    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {
        LL res = LLONG_MIN;
        auto cmp = [](const vector<LL>& a, const vector<LL>& b){
            return a[2]+a[0]*a[1] > b[2] + b[0]*b[1];
        };
        
        priority_queue<vector<LL> , vector<vector<LL>>, decltype(cmp)> pq;
        for(auto t : workerTimes){
            pq.push({t,1,0});
        }
        
        while(mountainHeight--){
            LL time = pq.top()[0];
            LL idx = pq.top()[1];
            LL total = pq.top()[2];
            pq.pop();
            res = max(res, total+time*idx);
            pq.push({time,idx+1, total+time*idx});
        }
        
        return res;
    }
};

/*
5
[1,5]

1 + 2 + 3 + 4;
10
*/
