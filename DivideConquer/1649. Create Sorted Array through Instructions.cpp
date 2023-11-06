/*
1649. Create Sorted Array through Instructions
*/

//TC:O(nlgnlgn) SC:O(n)
class Solution {
    long long count[100005];
    long long smaller[100005];
    long long temp[100005];
    long long M =  1e9+7;
public:
    int createSortedArray(vector<int>& nums) {
        int n = nums.size();
        auto sorted = nums;
        long long res = 0;
        DivideConquer(nums,sorted,0,n-1);

        for(int i = 0; i<n; i++){
            res+=min(smaller[i],i-smaller[i]-count[nums[i]]);
            res%=M;
            count[nums[i]]+=1;
        }

        return res;   
    }

    void DivideConquer(vector<int>& nums, vector<int>& sorted, int a, int b){
        if(a>=b) return;

        int mid = a + (b-a)/2;
        DivideConquer(nums,sorted,a,mid); 
        DivideConquer(nums,sorted,mid+1,b);
        for(int i = mid+1; i<=b; i++){
            auto iter = lower_bound(sorted.begin()+a, sorted.begin()+mid+1,nums[i]);
            smaller[i]+=(iter-(sorted.begin()+a));
        }

        // merge
        int i=a; int j = mid+1; int p = 0;
        while(i <=mid && j<=b){
            if(sorted[i] < sorted[j]){
                temp[p] = sorted[i];
                i++;
            }
            else{
                temp[p] = sorted[j];
                j++;
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

/*
此題跟315類似 差別只差在多個限制從比他大的數以及比他小的數量取個最小的數
*/
