/*
327. Count of Range Sum
*/


class Solution {
public:
    int ans = 0;
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        vector<long> presum(nums.size()+1);

        for(int i = 1; i <=nums.size(); i++){
            presum[i] = presum[i-1]+nums[i-1];
        }
        mergesort(presum, 0, nums.size(), lower, upper);

        return ans;
    }
    void mergesort(vector<long>& presum, int front, int end, int lower, int upper){//divide and conquer
        if(front == end) return;

        int mid = front + (end-front)/2;
        mergesort(presum, front, mid, lower, upper);//divide
        mergesort(presum, mid+1, end, lower, upper);

        //兩個sort好的數組開始比較
        for(int i = front; i <=mid; i++){
            auto p1 = lower_bound(presum.begin()+mid+1, presum.begin()+end+1, lower+presum[i]);
            auto p2 = upper_bound(presum.begin()+mid+1, presum.begin()+end+1, upper+presum[i]);

            ans += p2-p1; 
        }

        inplace_merge(presum.begin()+front, presum.begin()+mid+1, presum.begin()+end+1);
    }
};
/*
解題思路：
此題想求區間和 range of sum 看到即想到前綴技巧
1. 先做出前綴和數組出來 之後就可以用此數組去看哪幾個相加有符合條件
lower <= presum[j+1] - presum[i] <= upper
2.符合條件的位置之間相減即是有幾種結果符合
3.最後再將兩數組合併

tc: o(nlgn) sc:o(n)
參考：
https://github.com/wisdompeak/LeetCode/tree/master/Divide_Conquer/327.Count-of-Range-Sum
*/
