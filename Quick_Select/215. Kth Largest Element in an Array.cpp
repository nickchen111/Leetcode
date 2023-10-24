/*
215. Kth Largest Element in an Array
*/

// 10/15
class Solution {
    vector<int> nums;
public:
    int findKthLargest(vector<int>& nums, int k) {
        this->nums = nums;
        int n = nums.size();
        return quickselect(0,nums.size()-1,n-k+1);
    }
    int quickselect(int a, int b, int k){
        int pivot = nums[(a+b)/2];
       
        int i=a, t=a, j=b;
        while(t<=j){
            if(nums[t] < pivot){
                swap(nums[t],nums[i]);
                i++;
                t++;
            }
            else if(nums[t] > pivot){
                swap(nums[t],nums[j]);
                j--;
            }
            else t++;
        }

        if(i-a >=k) return quickselect(a,i-1,k);
        else if(j-a+1 >= k) return pivot;
        else return quickselect(j+1,b,k-(j-a+1));
    }
};

// quickselect
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {

        return quickselect(nums, 0, nums.size()-1, k);   
    }
    int quickselect(vector<int>& nums, int front, int end, int k){//直接做partition會做的事
        //寫法很類似quick sort差別在於不去理會不在範圍內的區間 因此tc可降到o(n)

        int pivot = nums[(front+end)/2];
        //三指針技巧
        int i = front, j = end, t = front; //i同樣是比較小的值的歸屬地 j為較大的值所在地 t為遍歷所有數組直到t=j的指針
        while(t <= j){
            if(nums[t] < pivot){
            swap(nums[i], nums[t]);//swap可自己寫一個
            i++;
            t++;
            }
            else if(nums[t] > pivot){
                swap(nums[j], nums[t]);// j換過去的還不確定數值所以t不加加
                j--;
            }
            else t++; //當nums[t] == pivot時
        }

        //遞歸求區間
        if(end-j >= k){
            return quickselect(nums, j+1,end, k);//寫return 因為這是有返回值的函式
        }
        else if(end-i+1 >= k){
            return pivot;
        }
        else {
            return quickselect(nums, front, i-1, k-(end-i+1));
        }
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
此方法： tc: o(nlgc) c為最小跟最大值總共會分割32次的概念 sc:

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

時間複雜度：

Quickselect 算法的平均時間複雜度為 O(n)，其中 n 是數組的大小。每次分區（partition）都將數組分成兩個部分，並且只對包含目標元素的區域進行遞迴操作。
這使得平均情況下，算法不需要遍歷所有元素，從而實現了較快的查找。
空間複雜度：

Quickselect 算法的空間複雜度主要取決於遞迴操作的調用堆棧。在最壞的情況下，Quickselect 的遞迴深度可能達到 n，因此空間複雜度為 O(n)。
然而，在平均情況下，遞迴深度遠小於 n，因此空間複雜度通常是較小的。

*/
