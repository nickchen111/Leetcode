/*
493_Reverse_Pairs
*/
class Solution {    
public:
    int reversePairs(vector<int>& nums) {
        vector<int> sorted = nums;
        return mergesort(nums, sorted, 0, nums.size()-1); 
    }

    int mergesort(vector<int>& nums, vector<int>& sorted, int front, int end){
        if(front >= end) return 0;
            int mid = front + (end - front)/2;
            int count = 0;
            count += mergesort(nums,sorted, front, mid);
            count += mergesort(nums,sorted, mid+1, end);
            //有點像是sort 的同時順便做一下count計數

            //merge前先計數 但是如果是只有一個元素則會跳過這個先sort
            for(int j = mid+1; j <= end; j++){
                auto iter = upper_bound(sorted.begin()+front, sorted.begin()+mid+1, 2*(long)nums[j]);
                count +=  sorted.begin()+mid+1 - iter;
            }
            //類似 [xxxx]     [yyyy]
            //.        mid  mid+1  

            merge(sorted, front, mid, end); //inplace_merge(sorted.begin()+front, sorted.begin()+mid+1, sorted.begin()+end+1);用這個會變快

            return count;
    }
};
    const int max = INT_MAX;
    void merge(vector<int>&sorted, int front, int mid, int end){
    //會需要把傳入的數組分成兩個數組並分別給他們index
    vector<int> leftsub(sorted.begin()+front, sorted.begin()+mid+1);
    vector<int> rightsub(sorted.begin()+mid+1, sorted.begin()+end+1);

    leftsub.insert(leftsub.end(), max);//放max是為了最後剩元素比較時能順利將真正最大那項放進去
    rightsub.insert(rightsub.end(), max);
    int idxleft = 0, idxright = 0;
    //開始比較
    for(int i = front; i <= end; i++){
        if(leftsub[idxleft] <= rightsub[idxright]){
            sorted[i] = leftsub[idxleft];
            idxleft++;
        }
        else {
            sorted[i] = rightsub[idxright];
            idxright++;
        }
    }
    }
};
//merge sort可考量到要排序的數組已經是排好的狀況下的sort 時間複雜度更低
//首先需要兩個指針 跟一個int給temp
int i = front, j = mid+1, p = 0;
while(i <= mid && j <=end){
    if(nums[i] <= nums[j]){
        temp[p] = nums[i];
        i++;
        p++;
    }
    else{
        temp[p] = nums[j];
        j++;
        p++;
    }
    //如果其中一個數組還沒用完
    while(i <= mid){
        temp[p] = nums[i];
        i++;
        p++;
    }
    while(j <= end){
        temp[p] = nums[j];
        j++;
        p++;
    }
    //把temp加回去數組裡
    for(int i = 0; i< end-front+1; i++){
        nums[i+front] = temp[i];
    }
}

/*
解題思路 
這一題思考一下會發現如果是sort的話會好做很多 也就是说确定了i，很容易就能找到满足条件的j；反过来也是。这就强烈提示了需要用分治法（divide and conquer）来做
dc通常會跟merge sortu 合併一起來做
因此這題可以想成說
1.這數組瘋狂divide 然後他們各自去比較內部有沒有reverse pairs 存在 數量是多少
2. conquer的時候就是兩邊要去比較的時候再去寫個迴圈判斷即可
ps:寫這型的題目通常用一個sorted數組去另外儲存排列過的結果比較好 有時候會不希望原本的排列被動到

此題本質上來說還是可以構思成二叉樹的狀態

時間複雜度：

這個算法的時間複雜度是 O(n log n)，其中 n 是數組的大小。這是因為合併排序的時間複雜度是 O(n log n)，而在合併過程中，每次計算反序對的數量所需的時間是 O(n)。
空間複雜度：

這段程式碼使用了遞迴呼叫堆疊，遞迴的最大深度等於合併排序的深度，最壞情況下為 log n。此外，在合併過程中，使用了兩個臨時數組 leftsub 和 rightsub，
其大小分別是 mid - front + 1 和 end - mid。因此，空間複雜度是 O(n)。
總的來說，這個算法的時間複雜度是 O(n log n)，空間複雜度是 O(n)。需要注意的是，這個算法通常比較適用於中等大小的數組，對於非常大的數組可能會遇到效能問題。
*/
