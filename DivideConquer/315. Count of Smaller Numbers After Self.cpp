/*
315. Count of Smaller Numbers After Self
*/

// TC:O(nlgnlgn) SC:O(n)
class Solution {
    vector<int> res;
    int temp[100002];
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        res.resize(n);
        auto sorted = nums;
        DivideConquer(nums,sorted,0,n-1);//放的是index
        return res;
    }

    void DivideConquer(vector<int>& nums,vector<int>& sorted, int a, int b){
        if(a >= b) return;
        int mid = a+(b-a)/2;
        DivideConquer(nums,sorted,a,mid);
        DivideConquer(nums,sorted,mid+1,b);

        for(int i = a; i<=mid; i++){
            //這裡體現出為何要創sorted 因為要找的nums[i]位置不能被改變  
            auto x = lower_bound(sorted.begin()+mid+1, sorted.begin()+b+1, nums[i]);
            res[i]+=(x-(sorted.begin()+mid+1));
        }

        int i = a; int j = mid+1; int p = 0;
        while( i <= mid && j <= b){
            if(sorted[i] > sorted[j]){
                temp[p] = sorted[j];
                j++;
            }
            else{
                temp[p] = sorted[i];
                i++;
            }
            p++;
        }

        while(i<=mid){
            temp[p] = sorted[i];
            i++;
            p++;
        }
        while(j<=b){
            temp[p] = sorted[j];
            j++;
            p++;
        }

        for(int i = 0; i<b-a+1; i++){
            sorted[i+a] = temp[i];
        }
    }
};


// 使用函式
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        if(nums.size() == 0) return {};//base case
        vector<int> sorted = nums;
        vector<int> count(nums.size(), 0);
        mergesort(nums, sorted, count, 0, nums.size()-1);

        return count;
    }
    void mergesort(vector<int>& nums,vector<int>& sorted, vector<int>& count, int front, int end){
        if(front < end){
            int mid = front + (end-front)/2;
            mergesort(nums,sorted, count, front, mid);
            mergesort(nums, sorted, count, mid+1, end);
            //總而言之就是先去比較然後把比好的數組sort再一起
            
            // OK，既然现在start~mid和mid+1~end这两段都分别有序，
            // 那么对于start~mid中的任何一个元素，我们都可以轻易地知道在mid+1~end中有多少小于它的数
            for(int i = front; i<=mid; i++){ //
                auto iter = lower_bound(sorted.begin()+mid+1, sorted.begin()+end+1,nums[i]);
                count[i] += iter - (sorted.begin()+mid+1);
            }

            // 将两段已经有序的数组段start~mid,mid+1~end合起来排序。
            inplace_merge(sorted.begin()+front, sorted.begin()+mid+1, sorted.begin()+end+1);
        }
    }
};

/*
本题中带有鲜明的特征，即求nums[i]右边的所有小于它的数，这暗示了用分治和归并排序的算法。

在每一轮，序列start~end对半分为两部分，左序列区间从start到mid，右序列区间从mid+1到end。
两个部分各自递归调用分治排序的函数后，都变得有序（存放在sortedNums里）。此时，对于左序列的任意nums[i]，
都可以轻易在有序的右序列中用lower_bound找到可以插入的位置，也就知道了右序列中有多少小于它的数。据此可以更新count[i].

有人会问，那么在左序列中（从nums[start]到nums[mid]），肯定也有一些数小于nums[i]并且位于它右边呀。为什么不考虑呢？
其实这部分在之前对于start~mid区间调用分治排序的函数处理过了。
*/
