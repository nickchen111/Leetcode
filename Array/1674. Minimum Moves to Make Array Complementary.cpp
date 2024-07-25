/*
1674. Minimum Moves to Make Array Complementary
*/

// 如果數據規模在10^5左右: TC:O(n + limit) SC:O(limit)
class Solution {
public:
    int minMoves(vector<int>& nums, int limit) {
        int n = nums.size();
        vector<int> diff(200005);
        for(int i = 0; i < n/2; i++){
            int mn = min(nums[i], nums[n-i-1]);
            int mx = max(nums[i], nums[n-i-1]);

            diff[2] += 2;
            diff[mn+1] -= 1;
            diff[mn+mx] -= 1;
            diff[mn+mx+1] += 1;
            diff[mx + limit+1] += 1;
        }
        
        int res = n/2;
        int sum = 0;
        for(int i = 2; i <= limit*2; i++){
            sum += diff[i];
            res = min(res, sum);
        }

        return res;
    }
};

// 10^9: TC:O(nlgn) SC:O(n)
class Solution {
public:
    int minMoves(vector<int>& nums, int limit) {
        int n = nums.size();
        map<int,int> map;
        for(int i = 0; i < n/2; i++){
            int mn = min(nums[i], nums[n-i-1]);
            int mx = max(nums[i], nums[n-i-1]);

            map[2] += 2;
            map[mn+1] -= 1;
            map[mn+mx] -= 1;
            map[mn+mx+1] += 1;
            map[mx + limit+1] += 1;
        }
        
        int res = n/2;
        int sum = 0;
        for(auto &[key, val]: map){
            sum += val;
            res = min(res, sum);
        }

        return res;
    }
};

//  最初的寫法 但是空間可能會超時TC:O(n) SC:O(limit)
class Solution {
public:
    int minMoves(vector<int>& nums, int limit) {
        int n = nums.size();
        unordered_map<int,int> map;
        vector<int> diff(200005);
        for(int i = 0; i < n/2; i++){
            map[nums[i] + nums[n-i-1]] += 1;
            int mn = min(nums[i], nums[n-i-1]);
            int mx = max(nums[i], nums[n-i-1]);

            int curMin = mn+1;
            int curMax = mx + limit;
            diff[curMin] += 1;
            diff[mn+mx] -= 1;
            diff[mn+mx+1] += 1;
            diff[curMax+1] -= 1;
        }
        for(int i = 1; i < 200005; i++){
            diff[i] += diff[i-1];
        }
        // 10 2 -> 1+2 = 3, limit - 10 min ?! 
        int res = n/2;
        for(auto &[val, freq] : map){
            int nums1 = diff[val]; // 只需要換一個的組
            int reduct = n/2 - freq - diff[val];
            res = min(res, reduct*2 + diff[val]);
        }

        return res;
    }
};
