/*
3134. Find the Median of the Uniqueness Array
*/

// TC:O(32*n) SC:O(n)
class Solution {
    using LL = long long;
public:
    int medianOfUniquenessArray(vector<int>& nums) {
        int n = nums.size();
        LL N = (LL)n*(n-1)/2 + n; 
        int left = 1, right = n;
        while(left < right){
            int mid = left + (right-left)/2;
            if(atMostK(nums, mid) >= (N+1)/2){
                right = mid;
            }
            else left = mid + 1;
        }

        return left;
    }
    LL atMostK(vector<int>& nums, int k){
        int n = nums.size();
        unordered_map<int,int> map;
        int i = 0;
        LL count = 0;
        for(int j = 0; j < n; j++){
            map[nums[j]] += 1;
            while(map.size() > k){
                map[nums[i]] -=1;
                if(map[nums[i]] == 0) map.erase(nums[i]);
                i++;
            }

            count += (j-i+1);
        }

        return count;
    }
};

/*
總共會有 n*(n-1)/2 + n 種可能性 因為n*(n-1)就是選頭選尾不重複 + 頭尾相同的n個
數量級過高 並且看得出 很難用個什麼方法去把每一個subarray按照順序真的枚舉出他的distinct 
這種情況就可以用二分去猜一個獨特出現的次數會是中位數
再來要問你有多少個subarray 他的獨特元素出現的次數不超過k 就是992題了
x x x x x O -> j-i+1
*/
