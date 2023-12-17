/*
2967. Minimum Cost to Make Array Equalindromic
*/

// TC:O(nlgn + n) SC:O(1)
class Solution {
    using LL = long long;
public:
    long long minimumCost(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        LL n = nums.size();
        int mid = n/2;
        
        LL mid1 = nums[mid];
        LL mid2 = mid1;
        
        
      
        while(!check(mid1)) mid1--;
        while(!check(mid2)) mid2++;
        
        LL cost1 = 0;
        LL cost2 = 0;
        for(int i = 0; i < n; i++){
            cost1 += abs(nums[i] - mid1);
            cost2 += abs(nums[i] - mid2);
        }
        
        LL res = min(cost1,cost2);
        
        return res;
    }
    
    
   
    bool check(LL num){
        LL reverse = 0;
        LL original = num;
        while(num != 0){
            reverse = reverse * 10 + num % 10;
            num /= 10;
        }
        
        return original == reverse;
    }
};

// 回文串判斷方式用字串 TC:O(nlgn + n) SC:O(1)
class Solution {
    using LL = long long;
public:
    long long minimumCost(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        LL n = nums.size();
        int mid = n/2;
        
        LL mid1 = nums[mid];
        LL mid2 = mid1;
        
        
      
        while(!check(mid1)) mid1--;
        while(!check(mid2)) mid2++;
        
        LL cost1 = 0;
        LL cost2 = 0;
        for(int i = 0; i < n; i++){
            cost1 += abs(nums[i] - mid1);
            cost2 += abs(nums[i] - mid2);
        }
        
        LL res = min(cost1,cost2);
        
        return res;
    }
    
  bool check(int num){
        string str = to_string(num);
        int left = 0; int right = str.size()-1;
        while(left < right){
            if(str[left] == str[right]){
                left++;
                right--;
            }
            else return false;
        }
        
        return true;
    }

/*
花最少cost改數字讓他們都一樣並且更改的數字要是回文串
要找一個回文串數字跟大家相減和最小
2 10 15 -> 27/3 = 9-> 7 + 1 + 6 = 14 or 10-> 8 + 0 + 5 最好的似乎會是有出現的中間數字回文串
我嘗試多次得到的邏輯是 接近mid數字正負他相減最少的就可能是答案 但是用了錯誤的比較方式 一直拿mid數字本身跟前後是回文串的數字相減
但其實不一定, 要都try過他周圍正負最近的兩個回文串數字才知道哪個會是正確答案
*/
