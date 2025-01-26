// 2025.01.26 Sliding Window or Three Pointer
class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        int i1 = 0, i2 = 0, ans = 0, sum1 = 0, sum2 = 0;
        for(int j = 0; j < n; j++) {
            sum1 += (nums[j] % 2);
            sum2 += (nums[j] % 2);
            while(sum1 >= k) {
                sum1 -= (nums[i1++] % 2);
            }
            while(sum2 >= k+1) {
                sum2 -= (nums[i2++] % 2);
            }
            ans += i1-i2;
        }
        return ans;
    }
};


// Hash + presum: TC:O(n) SC:O(n)
class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        unordered_map<int,int> map; // the number of odd number -> freq
        int n = nums.size();
        map[0] = 1;
        int count = 0;
        int res = 0;
        for(int i = 0; i < n; i++){
            if(nums[i] % 2 == 1){
                count += 1;
            }
            if(map.find(count - k) != map.end()){
                res += map[count-k];
            }
            map[count] += 1;
        }

        return res;
    }
};

// Slide Window TC:O(n) SC:O(1)
class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        // slide
        int count = 0;
        int j = 0;
        int i = 0;
        int res = 0;
        int n = nums.size();
        int temp = 0;
        while(j < n){
            if(nums[j] % 2 == 1){
                temp = 0;
                count++;

            }
            while(count == k){
                temp++;
                //去計算合法狀態下左邊的數量
                if(nums[i] % 2 == 1) count--;
                i++;
            }
            j++;
            res += temp;
        }

        return res;
    }
};

// Count subarray by element 貢獻法類似概念 但比較偏數學去計算 TC:O(n) SC:O(n)
class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        // slide
        vector<int> pos;
        for(int i = 0; i < nums.size(); i++){
            if(nums[i] % 2 == 1) pos.push_back(i);
        }

        if(pos.size() < k) return 0;

        int n = pos.size();
        int res = 0;
        for(int i = 0; i < n; i++){
            if(i + k -1 < n){
                int a = pos[i] - (i - 1 < 0 ? -1:pos[i-1]);
                int b = (i + k == n ? nums.size() : pos[i + k] ) - pos[i+k-1];
                res += a*b;
            }
        }

        return res;
    }
};

/*
計算一個數組中 奇數元素的數量為 k個的子數組有幾個
這樣一來數字本身沒意義 只要看 %2 就好
hash + prefix sum or slide window or count subarray by element
x x x x x x x x  k = 3

*/
