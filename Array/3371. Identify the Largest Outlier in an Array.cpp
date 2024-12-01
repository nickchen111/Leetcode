/*
3371. Identify the Largest Outlier in an Array
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int getLargestOutlier(vector<int>& nums) {
        int n = nums.size();
        unordered_map<long long, int> freq;
        long long totalSum = 0;
        
        for (int num : nums) {
            totalSum += num;
            freq[num]++;
        }
        
        long long maxOutlier = LLONG_MIN;
        
        // 對於每個可能的和
        for (auto it = freq.begin(); it != freq.end(); ++it) {
            long long sum = it->first;  // 假設這個數是特殊數字的和
            
            // 計算這種情況下的異常值
            // 如果 sum 是特殊數字的和，則：
            // totalSum = sum + outlier + sum (因為 sum 在數組中出現兩次)
            // 所以：outlier = totalSum - 2 * sum
            long long outlier = totalSum - 2 * sum;
            
            bool isValid = true;
            
            // 檢查這個和是否合理
            if (freq.count(outlier)) {
                // 檢查頻率
                int sumFreq = it->second;
                int outlierFreq = freq[outlier];
                
                // 檢查條件：
                // 1. sum 必須在數組中至少出現一次
                // 2. 如果 sum == outlier，總共出現次數必須足夠
                // 3. sum 的出現次數必須允許一個作為和，其他作為特殊數字
                if (outlier == sum) {
                    if (sumFreq >= 2) {
                        maxOutlier = max(maxOutlier, outlier);
                    }
                } else {
                    // sum 和 outlier 是不同的數
                    if (outlierFreq >= 1) {
                        maxOutlier = max(maxOutlier, outlier);
                    }
                }
            }
        }
        
        return maxOutlier;
    }
};
