/*
3013. Divide an Array Into Subarrays With Minimum Cost II
*/


// TC:O(nlgk) SC:O(n)
class Solution {
    using LL = long long;
public:
    long long minimumCost(vector<int>& nums, int k, int dist) {
        int n = nums.size();
        k -= 1; //找k個最小值 在dist+1的滑窗內
        multiset<LL> set1;
        multiset<LL> set2;
        LL sum = 0;
        LL res = LLONG_MAX;
        for(int i = 1; i < n; i++){
            if(set1.size() < k){
                set1.insert(nums[i]);
                sum += nums[i];
            }
            else if(*set1.rbegin() <= nums[i]){
                set2.insert(nums[i]);
            }
            else if(*set1.rbegin() > nums[i]){
                sum -= *set1.rbegin();
                set2.insert(*set1.rbegin());
                set1.erase(--set1.end());
                set1.insert(nums[i]);
                sum += nums[i];
            }

            if(i >= dist+1){
                res = min(res, sum + (LL)nums[0]);
                int need2delete = nums[i-dist];
                if(set2.find(need2delete) != set2.end()){
                    set2.erase(set2.find(need2delete));
                }
                else {
                    set1.erase(set1.find(need2delete));
                    sum -= need2delete;
                    //這一步要注意
                    if(!set2.empty()) {
                        set1.insert(*set2.begin());
                        sum += *set2.begin();
                        set2.erase(set2.begin());
                    }
                }
            }
        }
        return res;
    }
};

// 這題就是在說首先數組第一個元素必定選然後他可以一路選元素 找dist+1滑出內 k-1個最小的元素求他們的和
// 要最小
// 滑窗範圍內選數值 第一個必選 剩下的(k-1)個元素 第一個元素跟最後一個元素距離不超過dist+1
