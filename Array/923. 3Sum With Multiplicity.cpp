/*
923. 3Sum With Multiplicity
*/

// Two Pointer TC:O(n^2) SC:O(1)
class Solution {
    using LL = long long;
    LL M = 1e9 + 7;
public:
    int threeSumMulti(vector<int>& arr, int target) {
        
        int n = arr.size();
        sort(arr.begin(), arr.end());
        LL res = 0;
       
        
        for(int i = 0; i < n-2; i++){
            int left = i + 1;
            int right = n-1;
            
            while(left < right){
                LL sum = arr[left] + arr[right] + arr[i];
                if(sum > target){
                    right--;
                }
                else if(sum < target){
                    left++;
                }
                else {
                    int count1 = 1;
                    int count2 = 1;
                    while(left < right && arr[left] == arr[left+1]){
                        left++;
                        count1++;
                    }
                    while(right > left && arr[right] == arr[right-1]){
                        right--;
                        count2++;
                    }

                    if(left != right)
                        res = (res + count1*count2) % M;
                    else {
                        res = (res + (count1)*(count1-1)/2)%M;
                    }
                    
                    left++; right--;
                }
            }
        }

        return res;

    }
};

/*
此題在3sum基礎上允許了重複數字 並且要求index位置不能改變
這題因為可以允許重複數字組合 所以索性不用第一層遍歷每個點都算 做雙指針的時候如果遇到重複的再來計數兩方的數量 但這裡要注意如果數字兩個重複 數學公式來說是(n*n-1)/2
*/
