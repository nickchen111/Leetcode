/*
2967. Minimum Cost to Make Array Equalindromic
*/

// 找較大較小回文串 by 貪心 TC:O(nlgn + n) SC:O(1)
class Solution {
    using LL = long long;
public:
    long long minimumCost(vector<int>& nums) {
        // find median
        sort(nums.begin(), nums.end());
        int n = nums.size();
        LL mid = (n-1)/2;
        LL median = nums[mid];
        LL res = 0;

        if(check(median)) {
            for(int i = 0; i < n; i++){
                res += abs(nums[i] - nums[mid]);
            }
            return res;
        }

        LL candidate1 = nextSmaller(median);
        LL candidate2 = nextGreater(median);

        LL sum1 = 0;
        LL sum2 = 0;
        for(int i = 0; i < n; i++){
            sum1 += abs(nums[i] - candidate1);
            sum2 += abs(nums[i] - candidate2);
        }

        res = min(sum1, sum2);

        return res;
    }
    bool check(LL median){
        LL sum = 0;
        LL target = median;
        while(median != 0){
            sum = sum * 10 + median % 10;
            median /= 10;
        }

        return sum == target;
    }

    LL nextGreater(LL n){
        string s = to_string(n);
        string target = to_string(n);
        int m = s.size();
        //先嘗試看看他可以自組成怎麼樣的回文串
        for(int i = 0, j = m-1; i<=j;){
            s[j--] = s[i++];
        }
        
        if(s > target) return stoll(s);
        int carry = 1;
        for(int i = (m-1)/2; i >= 0; i--){
            int d = s[i] - '0' + carry;
            if(d <= 9){
                s[i] = d + '0';
                carry = 0;
            }
            else {
                s[i] = '0';
                carry = 1;
            }
            s[m-1-i] = s[i];
        }
        if(carry == 1) {
            string str = string(m+1,'0');
            str[0] = str.back() = '1';
            return stoll(str);
        }
        else return stoll(s);
    }

    LL nextSmaller(LL n){
        string s = to_string(n);
        string target = to_string(n);
        int m = s.size();
        //先嘗試看看他可以自組成怎麼樣的回文串
        for(int i = 0, j = m-1; i<=j;){
            s[j--] = s[i++];
        }
        
        if(s < target) return stoll(s);
        int carry = 1;
        for(int i = (m-1)/2; i >= 0; i--){
            int d = s[i] - '0' - carry;
            if(d >= 0){
                s[i] = d + '0';
                carry = 0;
            }
            else {
                s[i] = '9';
                carry = 1;
            }
            s[m-1-i] = s[i];
        }
        if(s[0] == '0' && m > 1) {
            string str = string(m-1,'9');

            return stoll(str);
        }
        else return stoll(s);
    }
};

// 用整數判斷回文串TC:O(nlgn + n) SC:O(1)
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
