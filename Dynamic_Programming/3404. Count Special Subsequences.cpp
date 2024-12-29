/*
3404. Count Special Subsequences
*/


// GCD 前後綴分解 TC:O(n^2 * lgU) SC:O(n)
class Solution {
    using LL = long long;
public:
    long long numberOfSubsequences(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, LL> suf;
        for(int i = 4; i < n; i++) {
            // o x o x x
            int c = nums[i];
            for(int j = i + 2; j < n; j++) {
                int d = nums[j];
                int g = gcd(c,d);
                suf[(d/g << 16) | c/g] += 1;
            }
        }
        // O x O x O
        LL res = 0;
        for(int i = 2; i < n-2; i++) {
            int b = nums[i];
            for(int j = i - 2; j >= 0; j--) {
                int a = nums[j];
                int g = gcd(a,b);
                res += suf[(a/g << 16) | b/g];
            }
            int c = nums[i+2];
            for(int j = i + 4; j < n; j++) {
                int d = nums[j];
                int g = gcd(c,d);
                suf[(d/g << 16) | c/g] -= 1;
            }
        }
        
        return res;
        
    }
};


// 枚舉右維護左 TC:O(n^2) SC:O(n) 有除法double精度風險 但是 number value < 1e7 都不會有問題
class Solution {
    using LL = long long;
public:
    long long numberOfSubsequences(vector<int>& nums) {
        int n = nums.size();
        unordered_map<double, LL> cnt;
        LL res = 0;
        for(int i = 4; i < n; i++) {
            // x x x x x x x  
            double b = nums[i-2];
            for(int j = 0; j < i-3; j++) {
                cnt[nums[j]/b] += 1;
            }
            
            double c = nums[i];
            for(int j = i+2; j < n; j++) {
                res += cnt[nums[j] / c];
            }
        }
        
        return res;
    }
};

// 前後綴分解 除法版本 時間消耗因為兩個map所以比較高
class Solution {
    using LL = long long;
public:
    long long numberOfSubsequences(vector<int>& nums) {
        int n = nums.size();

        unordered_map<double, LL> suf_counter;
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i - 2; j >= 0; j--) {
                double score = (double) nums[i] / (double)nums[j];
                suf_counter[score]++;
            }
        }

        LL ans = 0;

        // 遍歷每個可能的中點 mid
        for (int mid = 0; mid < n; mid++) {
            unordered_map<double, LL> pre_counter;

            for (int i = 0; i < mid - 2; i++) {
                double score = (double)nums[i] / (double)nums[mid-1];
                pre_counter[score]++;
            }

            for (int i = mid + 2; i < n; i++) {
                double score = (double)nums[i] / (double)nums[mid];
                suf_counter[score]--;
            }

            
            for (const auto& [value, count] : pre_counter) {
                if (suf_counter.find(value) != suf_counter.end()) {
                    ans += count * suf_counter[value];
                }
            }
        }

        return ans;
        
    }
};

/*
nums[p] * nums[r] == nums[q] * nums[s]
nums[p] / nums[q] = nums[s] / nums[r]
nums[r] / nums[q] = nums[s] / nums[p]
p < q < r < s
*/

