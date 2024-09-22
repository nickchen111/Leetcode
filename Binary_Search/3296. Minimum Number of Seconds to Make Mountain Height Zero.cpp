/*
3296. Minimum Number of Seconds to Make Mountain Height Zero
*/

// 二分 TC:O(nlgU) SC:O(1) U≤  5⋅10^15是二分上界
class Solution {
    using LL = long long;
public:
    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {
        
        auto check = [&](LL mid)->bool{
            LL left_h = mountainHeight;
            
            for(auto &t : workerTimes){
                // 公式 (-1 + sqrt(1+8k) )/2, k = m/t
                left_h -= (LL) ((sqrt(mid / t * 8 + 1) - 1) / 2);
                if(left_h <= 0) return true;
            }
            
            return false;
        };
        LL maxT = *max_element(workerTimes.begin(), workerTimes.end()); // int max_t = ranges::max(workerTimes);
        LL h = (mountainHeight-1)/(int)workerTimes.size() + 1; // 向上取整
        
        LL left = 0, right = maxT*h*(h+1)/2;
        
        while(left < right){
            LL mid = left + (right - left)/2;
            if(check(mid)){
                right = mid;
            }
            else left = mid + 1;
        }
        
        return left;
    }
};

// PQ TC:O(nlgm) n = 山高 m = worker數量 SC:O(m)
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
