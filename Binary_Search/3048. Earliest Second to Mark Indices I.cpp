/*
3048. Earliest Second to Mark Indices I
*/

// TC:O(32*n) SC:O(n)
class Solution {
    using LL = long long;
public:
    int earliestSecondToMarkIndices(vector<int>& nums, vector<int>& changeIndices) {
        int left = nums.size();
        int right = changeIndices.size();
        if(left > right) return -1;
        unordered_map<int,int> map;
        for(int i = 0; i < changeIndices.size(); i++){
            map[changeIndices[i]] += 1;
        }

        if(map.size() < nums.size()){
            return -1;
        }

        LL sum = 0;
        for(int i = 0; i < nums.size(); i++){
            sum += nums[i];
        }

        //如果本身長度 < 原本數組要改變的元素+他需要扣掉的sum 
        if(right < left+sum) return -1;

        while(left < right){
            int mid = left + (right - left)/2;
            if(check(nums,changeIndices, mid, sum)){
                right = mid;
            }
            else left = mid + 1;
        }
        

        return left;
    }
    bool check(vector<int>& nums, vector<int>& changeIndices, int mid, LL sum){
        
        vector<int> arr(nums.size(),-1);
        int count = 0;
        
        for(int i = mid-1; i >= 0; i--){
            if(arr[changeIndices[i]-1] == -1){
                arr[changeIndices[i]-1] = i;
                count += 1;
            }
            if(count == nums.size()){
                break;
            }
        }

        if(count < nums.size()) return false;
        
        LL curSum = 0;
        for(int i = 0; i < mid; i++){
            int idx = changeIndices[i]-1;
            if(arr[idx] == i){
                curSum -= nums[changeIndices[i]-1];
                if(curSum < 0) return false;
            }
            else curSum += 1;
        }

        return true;
    }
};

/*
這題要先感覺到答案是單調性的 如果給的時間越久 我越容易清零 可以達成目標 
那我需要最短多少時間達成目標 那就是二分猜值 並且這題還有許多貪心思想 一定會想將給定範圍內的最後出現的index 當作最後讓他complete的時刻 
其他剩下的元素就是做減一操作 那減一操作是否足夠 就是影響最終答案的因素之一 還有一個是如果當前範圍沒辦法涵蓋所有想要complete的index 也是沒辦法達成
*/
