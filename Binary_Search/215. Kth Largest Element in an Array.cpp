/*
215. Kth Largest Element in an Array
*/

class Solution {
    // binary search
public:
    int findKthLargest(vector<int>& nums, int k) {
        long left = INT_MIN, right = INT_MAX;// 確保mid的計算不會overflow
        
        while(left < right){
            int mid = left + (right - left+1)/2;//避免死回圈

            if(count(nums, mid) >= k){
                left = mid;
            }
            else right = mid-1;
        }
        return left;
    }
    int count(vector<int>& nums, int t){
        int res = 0;
        for(auto x:nums){
            res += (x>=t);
        }

        return res;
    }
};


/*
有四種解法
1. sort the whole array: o(nlgn)
2. priority queue: rolling k max element-> o(nlgk)
3. binary search by values 
guess t: if(countNum >= t) >=k -> adjust bigger
                            <k -> adjust smaller 
binary search: the largest t s.t(such that) satisfy condition
array : k-th largest element is the largest t s.t satisfy condition
此方法： tc: o(nlgc) c為最小跟最大值總共會分割32次的概念 sc:o(1)

4. quick-select: 專門解 k-th element 此方法也有api nth_element(nums.begin(), nums.begin()+n-k, nums.end())
        pivot
S S S S O O O X L L L L L L   要碰到之前
front   i   t j           end

   a個元素。b 個。  c個
S S S S O O O O L L L L L L   t j相遇
front   i     j           end

if(c>= k) find k-th largest element in [L]
else if(b+c >= k) k-th is pivot
else k-(b+c)-th largest in [S]

解法0： PQ
此题比较简单的方法就是用priority_queue,遍历整个数组,每次只保留最大的K个值. 时间复杂度是NlogK.

解法1：二分搜值
另外还有一个理论上o(N)的算法，就是二分搜值，猜测这个数是t。如果发现nums里大于等于t的个数大于等于k，那么我们可以猜测更大的t（注意t可能是答案），
将下界上调为t；反之我们可以猜测更小的t（注意t不可能是答案），将上界下调至t-1。

有人会问，为什么最后上下界收敛得到的结果一定是数组里的元素？首先，二分搜索收敛到的是符合条件（即至少有k个数组元素大于等于它）的最大值。
其次，数组里的第k大元素，就是符合条件的最大值。所以二分搜索收敛的结果就是数组里的第k大元素。

二分搜值的时间复杂度是o(N*logC)

解法2：quick select
有一种类似于快速排序的quick select，可以在平均o(N)的时间内找到乱序数组里的第k大的数。步骤是：

任选数组里的某个元素作为pivot
利用三指针算法，将数组调整为三段：小于pivot的部分，等于pivot的部分，大于pivot的部分。
我们令三部分的个数分别是a,b,c。那么如果c>=k，那么接下需要在大于pivot的部分里选第k个的元素。
如果b+c>=k，那么说明pivot就是第k个大元素；否则，接下来需要再小于pivot的部分里选第b+c-k大的元素。
重复步骤1.
*/
