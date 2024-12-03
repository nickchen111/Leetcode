/*
2542. Maximum Subsequence Score
*/

// TC:O(nlgn) SC:O(n)
class Solution {
    using LL = long long;
public:
    long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<pair<LL, LL>> nums;
        int n = nums1.size();
        for(int i = 0; i < n; i++) {
            nums.push_back({nums1[i], nums2[i]});
        }
        auto cmp = [](const pair<LL, LL>& a, const pair<LL, LL>& b) {
            if(a.second != b.second) return a.second > b.second;
            else return a.first > b.first;
        };
        sort(nums.begin(), nums.end(), cmp);
        priority_queue<LL, vector<LL>, greater<LL>> pq;
        LL res = 0;
        LL curSum = 0;
        for(int i = 0; i < n; i++) {
            if(i < k-1) {
                curSum += nums[i].first;
                pq.push(nums[i].first);
            }
            else {
                curSum += nums[i].first;
                pq.push(nums[i].first);
                res = max(res, curSum * nums[i].second);
                curSum -= pq.top();
                pq.pop();
            }
        }

        return res;
    }
};

/*
要讓nums1選的數字盡量大 * (對應index上 nums2的最小數字) => maximize it
需要PQ 去判斷每種可能性
我希望我選的nums1大並且他對應的nums2也大 所以兩者要如何sort?
*/
