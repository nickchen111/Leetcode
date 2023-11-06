/*
493. Reverse Pairs
*/

// TC:O(nlgnlgn) SC:O(n) 11/6
class Solution {
    int res = 0;
    int temp[50002];
public:
    int reversePairs(vector<int>& nums) {
        int n = nums.size();
        auto sorted = nums;
        DivideConquer(nums,sorted,0,n-1);
        return res;
    }

    void  DivideConquer(vector<int>& nums,vector<int>& sorted,int a, int b){
        if(a>=b) return;
        int mid = a+(b-a)/2;
        DivideConquer(nums,sorted,a,mid);
        DivideConquer(nums,sorted,mid+1,b);

        for(int j = mid+1; j<=b; j++){
            auto iter = upper_bound(sorted.begin()+a,sorted.begin()+mid+1,(long long)2*nums[j]);
            res+= sorted.begin()+mid-iter+1;
        }

        int i=a; int j = mid+1; int p = 0;
        while(i <=mid && j <=b){
            if(sorted[i] > sorted[j]){
                temp[p] = sorted[j];
                j++;
            }
            else {
                temp[p] = sorted[i];
                i++;
            }
            p++;
        }
        while(i <= mid){
            temp[p] = sorted[i];
            i++;p++;
        }
        while(j <= b){
            temp[p] = sorted[j];
            j++;p++;
        }

        for(int i = 0; i<b-a+1; i++){
            sorted[i+a] = temp[i];
        }
    }
};

// TC:O(nlgnlgn) SC:O(n)
class Solution {    
public:
int count = 0;
    int reversePairs(vector<int>& nums) {

        vector<int> sorted = nums;
        return mergesort(nums, sorted, 0, nums.size()-1);
    }
    int mergesort(vector<int>& nums, vector<int>& sorted, int front, int end){
        if(front < end){
            
            int mid = front + (end - front)/2;
            mergesort(nums, sorted, front, mid);
            mergesort(nums, sorted, mid+1, end);

            //兩個排序好的數組開始比較
            for(int j = mid+1; j <= end; j++ ){
                auto pos = upper_bound(sorted.begin()+front, sorted.begin()+mid+1, 2*(long)nums[j]);
                count += sorted.begin()+mid+1 - pos;
            }

            inplace_merge(sorted.begin()+front, sorted.begin()+mid+1, sorted.begin()+end+1);

            return count;
        }
        return 0;
    }
};


/*
8/20
解題思路 
這一題思考一下會發現如果是sort的話會好做很多 也就是说确定了i，很容易就能找到满足条件的j；反过来也是。这就强烈提示了需要用分治法（divide and conquer）来做
dc通常會跟merge sort 合併一起來做
因此這題可以想成說
1.這數組瘋狂divide 然後他們各自去比較內部有沒有reverse pairs 存在 數量是多少
2. conquer的時候就是兩邊要去比較的時候再去寫個迴圈判斷即可

此題本質上來說還是可以構思成二叉樹的狀態
*/
