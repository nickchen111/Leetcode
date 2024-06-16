/*
3186. Maximum Total Damage With Spell Casting
*/

// TC:O(nlgn) SC:O(n)
class Solution {
    using LL = long long;
public:
    long long maximumTotalDamage(vector<int>& power) {
        map<LL, LL> map; 
        unordered_map<LL, LL> count;
        for(auto num : power){
            count[num] += 1;
        }
        set<LL> set(power.begin(), power.end());
        vector<LL> arr(set.begin(), set.end());
        
        map[-2] = 0;
        LL res = 0;
        for(int i = 0; i < arr.size(); i++){
            auto iter = map.lower_bound(arr[i]-2);
            if(iter != map.begin()){
                iter = prev(iter);
                res = max(res, iter->second + arr[i]*count[arr[i]]);
                map[arr[i]] = res;
            }
            
        }
        
        return res;
    }
};

/*
[5,9,2,10,2,7,10,9,3,8]
2 2 3 5 7 8 9 9 10 10
*/
