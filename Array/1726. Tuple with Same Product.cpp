/*
1726. Tuple with Same Product
*/

// 2025.02.6 分組循環 TC:O(n^2) SC:O(n^2)
class Solution {
public:
    int tupleSameProduct(vector<int>& nums) {
        int n = nums.size();
        vector<int> arr;
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                arr.push_back(nums[i] * nums[j]);
                // mp[nums[i] * nums[j]] += 1;
            }
        }
        sort(arr.begin(), arr.end());
        int ans = 0;
        // for(auto &[val, freq] : mp) ans += (freq-1) * freq / 2;
        int cnt = 0, i = 0;
        while(i < arr.size()) {
            cnt += 1;
            if(i + 1 < arr.size() && arr[i] == arr[i+1]) {
                i ++;
                continue;
            }
            ans += cnt * (cnt - 1) / 2;
            cnt = 0;
            i ++;
        }
        return ans * 8;
    }
};

// 公式解 TC:O(n^2) SC:O(n)
class Solution {
public:
    int tupleSameProduct(vector<int>& nums) {
        unordered_map<int,int> map;//乘積 -> 有幾組可以達成
        for(int i = 0; i < nums.size(); i++){
            for(int j = i + 1; j < nums.size(); j++){
                map[nums[i]*nums[j]] += 1;
            }
        }
        
        int res = 0;
        for(pair<int,int> p : map){
            int n = p.second;
            res += n*(n-1)/2;// C幾取幾的公式
        }

        return res*8;
    }
};


/*
此題說數組內元素都是獨特的 選四個數字滿足 a*b = c*d 的可能組合有多少個
3 * 10 = 5 * 6 
此題要想到數學解 c n 取 2 取出來的元素會有 8種排列組合 *8就是答案
看了提示解出來
*/xw

// Brute force TC:O(n^3) SC:O(n)
class Solution {
public:
    int tupleSameProduct(vector<int>& nums) {
        unordered_map<int,int> map;
        for(int i = 0; i < nums.size(); i++){
            map[nums[i]] = i;
        }
        
        int res = 0;
        for(int i = 0; i < nums.size(); i++){
            for(int j = i+1; j < nums.size(); j++){
                if(i == j) continue;
                int cur = nums[i]*nums[j];
                for(int k = 0; k < nums.size(); k++){
                    if(k == i || k == j) continue;
                    if(cur % nums[k] != 0) continue;
                    int num = cur/nums[k];
                    if(map.find(num) != map.end() && map[num] != i && map[num] != j && map[num] != k){
                        res += 2;
                    }
                }
            }
        }

        return res;
    }
};
