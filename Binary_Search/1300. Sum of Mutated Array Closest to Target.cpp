/*
1300. Sum of Mutated Array Closest to Target
*/

// TC:O(nlgn + lgclgn + n) SC:O(n)
class Solution {
    int presum[10002];
public:
    int findBestValue(vector<int>& arr, int target) {
        sort(arr.begin(), arr.end());
        int n = arr.size();
        presum[0] = arr[0];
        for(int i = 1; i < n; i++){
            presum[i] = presum[i-1] + arr[i];
        }
        if(presum[n-1] <= target) return arr.back();
        int low = 0; int high = 100000;

        while(low < high){
            int mid = low + (high - low)/2;
            int sum = solve(arr,mid);
            if(sum < target){
                low = mid + 1;
            }
            else if(sum > target){
                high = mid;
            }
            else return mid;
        }
        if(abs(solve(arr,high-1)-target) <= abs(solve(arr,high) - target)) return high-1;
        else return high;
    }

    int solve(vector<int>& arr, int mid){
        auto iter = upper_bound(arr.begin(), arr.end(), mid);
        int n  = arr.size();
        if(iter == arr.begin()) return mid*arr.size();
        else if(iter == arr.end()) return presum[n-1];
        
        int num = arr.end() - iter;//這些就是比mid大的數量  
        int sum = 0;
        // 1 2 3 4 5 | 6 7 8 9
        sum += presum[iter - arr.begin() - 1];
        sum += num*mid;
        return sum;

    }
};
/*
此題說給你一個數組 以及target 要你求出最小的value 此value可以將數組內比他大的數字換成他本身 然後最後數組總和要盡量接近target
此題可以收斂再稍微高出target的那項再來比較高出的跟低的哪個比較接近target
*/
