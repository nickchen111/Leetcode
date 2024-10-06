/*
3309. Maximum Possible Number by Binary Concatenation
*/

// 最佳解 Bit + GreedySort: TC:O(nlgn) SC:O(1) 如果不用bit 就是nlgk, k 為二進制字串平均長度
class Solution {
public:
    int maxGoodNumber(vector<int>& nums) {
        int n = nums.size();
        
        auto cmp = [](const int& a, const int& b){
            int len_a = __lg(a) + 1;
            int len_b = __lg(b) + 1;
            return (a << (len_b) | b) > (b << (len_a) | a);
        };
        sort(nums.begin(), nums.end(), cmp);
        
        int res = 0;
        
        for(int i = 0; i < n; i++){
            res = (res << (__lg(nums[i]) + 1)) | nums[i];
        }
        
        return res;
        
        
    }
};

// 次佳解 TC:O(m) SC:O(m) m為轉成二進制string總長度
class Solution {
public:
    int maxGoodNumber(vector<int>& nums) {
        int n = nums.size();
        vector<string> arr;
        for(int i = 0; i < n; i++){
            string s;
            
            while(nums[i]) {
                s = to_string((nums[i] & 1)) + s;
                nums[i] /= 2;
            }
            
            arr.push_back(s);
        }
        string s1 = arr[0] + arr[1] + arr[2];
        string s2 = arr[0] + arr[2] + arr[1];
        string s3 = arr[1] + arr[2] + arr[0];
        string s4 = arr[1] + arr[0] + arr[2];
        string s5 = arr[2] + arr[0] + arr[1];
        string s6 = arr[2] + arr[1] + arr[0];
        int num1 = 0, num2 = 0, num3 = 0, num4 = 0, num5 = 0, num6 = 0;
     
        
        for(int i = 0; i < s1.size(); i++){
            num1 = num1*2 + (s1[i] - '0');
            num2 = num2*2 + (s2[i] - '0');
            num3 = num3*2 + (s3[i] - '0');
            num4 = num4*2 + (s4[i] - '0');
            num5 = num5*2 + (s5[i] - '0');
            num6 = num6*2 + (s6[i] - '0');
        }
        
        return max(num1, max(num2, max(num3, max(num4, max(num5,num6)))));
        
        
    }
};
