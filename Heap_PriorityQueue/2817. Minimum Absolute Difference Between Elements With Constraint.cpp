/*
2817. Minimum Absolute Difference Between Elements With Constraint
*/

// TC:O(nlgx). x為窗口大小 查找跟插入都是lgx SC:O(x)
class Solution {
public:
    int minAbsoluteDifference(vector<int>& nums, int x) {
        int n = nums.size();
        multiset<int> set;
       
        int res = INT_MAX;
        for(int i = 0; i < n; i++){
            if(i <= x-1) continue;
            set.insert(nums[i-x]);

            auto iter = set.lower_bound(nums[i]);
            if(iter != set.begin()){
                auto iter2 = iter;
                iter2 = prev(iter2,1);
                res = min(res, nums[i] - *iter2);
            }
            if(*iter == nums[i]){
                res = 0;
                break;
            }
            else if(iter != set.end()){
                res = min(res, *iter- nums[i]);
            }

            
        }

        return res;

    }
};

/*
這題要你找兩個數組內的數字 他們的絕對值之差最小
但是但是這兩個數字index之差要大於等於x -> 越遠越好
slide window 先找到第一個肯定可以的範圍 然後從那開始做一個有序容器裝可以被射略到的數值 二分試試看當前數值or左邊
ex : x = 3 0-2都不行
0 1 2 3 4 5 6 
*/
