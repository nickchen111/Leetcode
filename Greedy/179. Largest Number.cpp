/*
179. Largest Number
*/

//TC:O(nlgn) SC:O(n)
class Solution {
    static bool cmp(string& a, string& b){
        return (a+b) > (b+a); //根據傳導性可以推出此式是對的
    }
public:
    string largestNumber(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return to_string(nums[0]);

        vector<string> num;
        for(auto x:nums){
            num.push_back(to_string(x));
        }

        sort(num.begin(), num.end(), cmp);

        string res;
        for(int i = 0; i<num.size(); i++){
            res +=num[i];
        }
        
        int i = 0;
        while(i < res.size() && res[i] == '0') i++;
        if(i == res.size()) return "0";

        else return res.substr(i); 
    }
};

/*
"此題想求 給你一串int 要你轉換成string拼接起來的數字最大 就是貪心每次都選數字最大的
但是此題要用conductiity的性質 將string相加 (a+b) (b+a)比較哪個大 才可以合理化比較第二個第三個字的時候的情況"
*/
