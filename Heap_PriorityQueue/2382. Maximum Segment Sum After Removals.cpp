/*
2382. Maximum Segment Sum After Removals
*/


// TC:O(nlgn+n) SC:O(n)
class Solution {
    using LL = long long;
    map<LL,LL> map;
    multiset<LL> set;
public:
    vector<long long> maximumSegmentSum(vector<int>& nums, vector<int>& removeQueries) {
        int n = nums.size();
        vector<LL> presum(n);
        for(int i = 0; i < n; i++){
            presum[i] = (i-1 < 0 ? 0 : presum[i-1]) + nums[i];
        }
        
        set.insert(presum[n-1]);
        map[0] = n-1;
        vector<LL> res(removeQueries.size());
        for(int i = 0; i < removeQueries.size(); i++){

            LL t = removeQueries[i];
            auto iter2 = map.upper_bound(t);

            LL start = prev(iter2)->first;
            LL end = prev(iter2)->second;
            LL del = presum[end] - (start - 1 < 0 ? 0 : presum[start-1]);
            set.erase(set.find(del));
            map.erase(start);
        

            if(start <= t-1){
                map[start] = t-1;
                LL add1 = presum[t-1] - (start-1 < 0 ? 0 : presum[start-1]);
                set.insert(add1);
            }

            if(t+1 <= end){
                map[t+1] = end;
                LL add2 = presum[end] - (t < 0 ? 0 : presum[t]);
                set.insert(add2);
            }

            if(set.size() > 0) res[i] = *set.rbegin();
        }

        return res;
    }
};
