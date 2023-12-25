/*
2261. K Divisible Elements Subarrays
*/

// TC:O(n^2) SC:O(n) Rolling Hash
class Solution {
    using ULL = unsigned long long;
    ULL B = 211;//設一個質數 比較不會有碰撞風險
public:
    int countDistinct(vector<int>& nums, int k, int p) {
        int n = nums.size();
        vector<ULL> power(211,1);
        for(int i = 1; i < B; i++){
            power[i] = power[i-1]*B;
        }
        int res = 0;
        for(int len = 1; len <= n; len++){
            unordered_set<ULL> set;
            ULL hash = 0;
            int count = 0;
            for(int i = 0; i < n; i++){
                if(i >= len){
                    hash = hash - power[len-1]* nums[i-len];
                    count -= (nums[i-len] % p == 0);
                }
                hash = hash*B + nums[i];
                count += (nums[i] % p == 0);
                if(i >= len-1){
                    if(set.find(hash) != set.end()) continue;
                    set.insert(hash);
                    if(count <= k)
                        res += 1;
                }
            }
        }
        

        return res;
    }
};

// TC:O(n^3) SC:O(n) 
class Solution {
public:
    int countDistinct(vector<int>& nums, int k, int p) {
        int n = nums.size();
        unordered_set<string> set;
        int res = 0;
        for(int i = 0; i < n; i++){
            int count = 0;
            string str;
            for(int j = i; j < n; j++){
                if(nums[j] % p == 0) {
                    count++;
                    if(count > k) break;
                }
                str += (nums[j] + '0' + ',');
                if(set.find(str) == set.end()){
                    res += 1;
                    set.insert(str);
                }
            }
        }

        return res;
    }
};

/*
求有多少個不同的subarray 裡面被p整除數量不超過k個
不能只是index不同 長相要不同
1. slide window紀錄目前整除數量 
2. set 將數組長相轉成字串 判斷是否存在一樣的 
TC:O(n^3)
*/
 
