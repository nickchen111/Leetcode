/*
3011. Find if Array Can Be Sorted
*/

// Slide Window TC:O(nlgU) U為數字大小 SC:O(n)
class Solution {
public:
    bool canSortArray(vector<int>& nums) {
        int n = nums.size();
        auto arr = nums;
        int prev = INT_MIN;
        for(int i = 0; i < n; i++) {
            int j = i+1;
            int curMin = nums[i];
            int curMax = nums[i];
            while(j < n && __builtin_popcount(nums[i]) == __builtin_popcount(nums[j])) {
                curMin = min(curMin, nums[j]);
                curMax = max(curMax, nums[j]);
                j++;
            }

            if(prev > curMin) return false;
            prev = curMax;
            i = j-1;
        }

        return true;
    }
};

// TC:O(8*n) SC:O(n)
class Solution {
public:
    bool canSortArray(vector<int>& nums) {
        int n = nums.size();
        
        vector<int> arr(n);
        for(int i = 0; i < n; i++){
            int count = 0;
            for(int j = 0; j < 9; j++){
                if((nums[i]>>j)&1) count += 1;
            }
            arr[i] = count;
        }
        
        
        int cmp = arr[0];
        int maxVal = nums[0];
        int minVal = nums[0];
        vector<pair<int,int>> temp; // min, max
        for(int i = 1; i < n; i++){
            if(arr[i] != cmp){
                temp.push_back({minVal, maxVal});
                minVal = nums[i];
                maxVal = nums[i];
                cmp = arr[i];
            }
            else {
                minVal = min(minVal, nums[i]);
                maxVal = max(maxVal, nums[i]);
            }
        }
        //最後一個切割數組沒有比較到 再多加上去
        temp.push_back({minVal, maxVal});
        
        //第一個數組的最小值比你的還大 or 最大值 比你的還大 
        for(int i = 0; i < temp.size()-1; i++){
            if(temp[i].first > temp[i+1].first || temp[i].second > temp[i+1].first) return false;
        }
        
        return true;
        
        
    }
};

/*
每個數字跟數字如果要交換的話他們的1的bit數量要一樣多 現在給你一組未排序的數組 問說能否藉由限制的交換方法讓他變成像是排序後的樣子
我的想法是先將每個數字的bit數量算出來 再根據bit數量切割數組 同時紀錄每個數組的最大最小值
如果前一個數組的最小值比後個數組的最小值還小 or 前一個數組的最大值比後一個數組的最小值還大 代表他們有重疊 return false
[75,34,30] -> 4,2,4
30 34 75 -> 2
[3,16,8,4,2] -> 2,1,1,1,1
*/
