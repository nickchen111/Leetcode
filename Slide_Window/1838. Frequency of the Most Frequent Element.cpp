/*
1838. Frequency of the Most Frequent Element
*/

// TC:O(nlgn + n) SC:O(1)
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        // Slide Window
        sort(nums.begin(),nums.end());
        long long cost = 0;
        int res = 0;
        int j = 0;
        for(int i = 0; i<nums.size(); i++){
            if(i == 0) cost = 0;
            else cost += (long long)(i - j) * (nums[i] - nums[i - 1]);
            

            while(cost > k){
                cost-=(nums[i]-nums[j]);
                j++;
            }
            res = max(res, i-j+1);
        }
        return res;
    }
};
/*
n^2 answer if we choose one number and need to check the number before choosing one
高頻元素一定會是既有元素 隨意選一個元素當作可能的高頻元素 那要選誰當他的相同元素 肯定是他之前的那一串可以試試看
所以如果能夠選了一個數字後快速確認他之前的需要多少cost可以到他
[1 2 4]
1->2 需要 2-1 = 1;
4-> [2 2 4] (4-2)*(前面有多少數字) if 超過了k 去掉最前面的數字 cost -= (nums[j]-nums[i])
[j x x i i+1] 
cost += (i-j)*(nums[i]- nums[i-1]);
*/
