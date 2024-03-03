/*
3068. Find the Maximum Sum of Node Values
*/

// TC:O(nlgn + n) SC:O(n)
class Solution {
    using LL = long long;
public:
    long long maximumValueSum(vector<int>& nums, int k, vector<vector<int>>& edges) {
        int n = nums.size();
        vector<LL> arr;
        LL sum = 0;
        for(int i = 0; i < n; i++){
            LL cur = nums[i]^k;
            LL diff = cur - nums[i];
            arr.push_back(diff);
            sum += nums[i];
        }
        
        sort(arr.rbegin(), arr.rend());
        
        for(int i = 0; i < arr.size(); i += 2){
            if(i+1 < n && arr[i] + arr[i+1] > 0){
                sum += (arr[i] + arr[i+1]);
            }
            else break;
        }
        
        return sum;
    }
};

/*
在他給定的邊 可以讓這兩個數字都與 k 做 XOR  可以做任意次
問說最後數組總和最大是多少
這裡要先有一個鮮明的概念 一個點做兩次XOR 等於沒做 所以就算兩個點沒有連在一起 他們還是可以直接選起來直接做XOR
010 XOR 101 -> 111 XOR 101 -> 010
x j x x x i 
*/
