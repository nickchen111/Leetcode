/*
1537. Get the Maximum Score
*/

// TC:O(m+n) SC:O(1)
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    int maxSum(vector<int>& nums1, vector<int>& nums2) {
        LL sum1 = 0, sum2 = 0;
        int i = 0; int j = 0;
        while( i < nums1.size() && j < nums2.size()){
            if(nums1[i] < nums2[j]){
                sum1= sum1+nums1[i];
                i++;
            }
            else if(nums1[i] > nums2[j]){
                sum2= sum2+nums2[j];
                j++;
            }
            else if(nums1[i] == nums2[j]){
                sum1 = max(sum1,sum2)+nums1[i];
                sum2 = sum1;
                i++; j++;
            }
        }
        while(i < nums1.size()){
            sum1= sum1+nums1[i];
            i++;
        }
        while(j < nums2.size()){
            sum2= sum2+nums2[j];
            j++;
        }

        return (max(sum1,sum2))%M;
        
    }
};

// 補一個前綴和 + 分組取最大
class Solution {
    using LL = long long;
    LL MOD = 1e9 + 7;
public:
    int maxSum(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size(), i = 0, j = 0;
        vector<LL> presum1(n+1), presum2(m+1);
        for(int i = 0; i < n; i++) presum1[i+1] = presum1[i] + (LL)nums1[i];
        for(int i = 0; i < m; i++) presum2[i+1] = presum2[i] + (LL)nums2[i];
        vector<pair<int,int>> arr{{0,0}};
        while(i < n && j < m) {
            if(nums1[i]<nums2[j]) i++;
            else if(nums1[i]>nums2[j]) j++;
            else {
                arr.emplace_back(i+1,j+1);
                i ++, j++;
            }
        }
        arr.emplace_back(n,m);
        LL ans = 0;
        for(int i = 1; i < arr.size();i++) {
            ans += max(presum1[arr[i].first] - presum1[arr[i-1].first], presum2[arr[i].second] - presum2[arr[i-1].second]);
        }
        return ans % MOD;
    }
};
