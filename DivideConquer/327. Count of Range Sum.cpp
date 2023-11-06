/*
327. Count of Range Sum
*/

// TC: O(nlgn) SC:O(n) 11/6
class Solution {
    int res = 0;
    long temp[100002];
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int n = nums.size();
        vector<long> presum(n+1);
        presum[0] = 0;
        for(int i = 1; i<=n; i++){
            presum[i] = presum[i-1]+nums[i-1];
        }

        // how to compute all combination? 如果他們個別都是排好序的就好做很多
        DivideAndConquer(presum,0,presum.size()-1,lower, upper);
        return res;
    }
    void DivideAndConquer(vector<long>& presum, int a, int b, int lower, int upper){
        if(a>=b) return;

        int mid = a + (b-a)/2;
        DivideAndConquer(presum,a,mid,lower,upper);
        DivideAndConquer(presum,mid+1,b,lower,upper);
        //開始找其中一個i固定他看他可以配對出多少個j
        for(int i=a; i<mid+1; i++){
            auto x = lower_bound(presum.begin()+mid+1,presum.begin()+b+1,presum[i]+lower);
            auto y = upper_bound(presum.begin()+mid+1,presum.begin()+b+1,presum[i]+upper);
            res+= (y-x);
        }
        // 自己寫merge sort
        int i = a; int j = mid+1; int p = 0;
        while(i < mid+1 && j <= b){
            if(presum[i] > presum[j]){
                temp[p] = presum[j];
                j++;
            }
            else {
                temp[p] = presum[i];
                i++;
            }
            p++;
        }

        while(i < mid+1){
            temp[p] = presum[i];
            i++;p++;
        }
        while(j <= b){
            temp[p] = presum[j];
            j++;p++;
        }

        for(int i = 0; i<b-a+1; i++){
            presum[i+a] = temp[i];
        }
    }
};


//函式sort
class Solution {
public:
    int ans = 0;
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        if(nums.size() == 0) return 0;
        vector<long> presum(nums.size()+1);
        presum[0] = nums[0];
        for(int i = 1; i<=nums.size(); i++){
            presum[i] = presum[i-1] + nums[i-1];
        }

        divide(presum, 0, presum.size()-1, lower, upper);

        return ans;

    }
    void divide(vector<long>& presum, int left, int right, int lower, int upper){
        //base case
        if(left < right){
            int mid = left + (right -left)/2;
            divide(presum, left, mid, lower, upper);
            divide(presum, mid+1, right, lower, upper);

            for(int i = left; i <= mid; i++){ //肯定是右邊減去左邊
                auto p1 = lower_bound(presum.begin()+mid+1, presum.begin()+right+1, lower+presum[i]);
                auto p2 = upper_bound(presum.begin()+mid+1, presum.begin()+right+1, upper+presum[i]);
                ans += (p2-p1);
            }

            inplace_merge(presum.begin()+left, presum.begin()+mid+1, presum.begin()+right+1);
        }
        return;
    }
};
/*
解題思路：
此題想求區間和 range of sum 看到即想到前綴技巧
1. 先做出前綴和數組出來 之後就可以用此數組去看哪幾個相加有符合條件
lower <= presum[j+1] - presum[i] <= upper. 如果這個數組在比較的時後有排序過那就好比多了-->divide and conquer
2.符合條件的位置之間相減即是有幾種結果符合
3.最後再將兩數組合併

*/
