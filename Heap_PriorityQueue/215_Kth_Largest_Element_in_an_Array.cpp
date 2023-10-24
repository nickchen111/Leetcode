/*
215. Kth Largest Element in an Array
*/

class Solution {
    // priority_queue
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int> > pq; //採用最小的在上面 最小優先

        //每個元素都遍歷一遍 o(n)
        for(auto x:nums){
            pq.push(x);// o(lgn)

            if(pq.size() > k){ //只保留k個元素
                pq.pop();
            }
        }

        // pq 中剩下的是 nums 中 k 个最大元素，
        // 堆顶是最小的那个，即第 k 个最大元素
        return pq.top();
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
可以把小顶堆 pq 理解成一个筛子，较大的元素会沉淀下去，较小的元素会浮上来；当堆大小超过 k 的时候，
我们就删掉堆顶的元素，因为这些元素比较小，而我们想要的是前 k 个最大元素嘛。

当 nums 中的所有元素都过了一遍之后，筛子里面留下的就是最大的 k 个元素，而堆顶元素是堆中最小的元素，也就是「第 k 个最大的元素」。

二叉堆插入和删除的时间复杂度和堆中的元素个数有关，在这里我们堆的大小不会超过 k，所以插入和删除元素的复杂度是 O(logK)，
再套一层 for 循环，总的时间复杂度就是 O(NlogK)。

tc: o(nlgn) sc:o(k)
*/
