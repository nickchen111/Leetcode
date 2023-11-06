/*
2426. Number of Pairs Satisfying Inequality
*/

//TC:O(nlgnlgn) SC:O(n)
class Solution {
    long long res = 0;
    int diff;
    int temp[100002];
public:
    long long numberOfPairs(vector<int>& nums1, vector<int>& nums2, int diff) {
        int n = nums1.size();
        this->diff = diff;
        vector<int> arr(n);
        for(int i = 0; i<n; i++){
            arr[i] = nums1[i]-nums2[i];
        }
        auto sorted = arr;
        DivideConquer(arr,sorted,0,n-1);
        return res;
    }

    void DivideConquer(vector<int>& arr, vector<int>& sorted, int a, int b){
        if(a>=b) return;
        int mid = a+(b-a)/2;
        DivideConquer(arr,sorted,a,mid);
        DivideConquer(arr,sorted,mid+1,b);

        for(int i = mid+1; i<=b; i++){
            //找到第一個大過arr[j]+diff的位置
            auto iter = upper_bound(sorted.begin()+a,sorted.begin()+mid+1, arr[i]+diff);
            res+= iter-(sorted.begin()+a);
        }

        // merge
        int i = a; int j = mid+1; int p = 0;
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

        while(i<=mid){
            temp[p] = sorted[i];
            i++;p++;
        }
        while(j<=b){
            temp[p] = sorted[j];
            j++;p++;
        }
        
        for(int i = 0; i<b-a+1; i++){
            sorted[i+a] = temp[i];
        }
    }
};
/*
想找到 nums1[i] - nums1[j] <= nums2[i]-nums2[j]+diff的各種解
公式化解
nums1[i] - nums2[i] <= nums1[j]-nums2[j]+diff
arr[i]<=arr[j]+diff
*/
