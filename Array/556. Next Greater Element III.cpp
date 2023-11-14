/*
556. Next Greater Element III
*/


// TC:O(n) SC:O(n)
class Solution {
public:
    int nextGreaterElement(int n) {
        //這題其實跟31題一樣 只不過從數組換成數字
        vector<int> digits;
        while(n > 0){
            digits.push_back(n%10);
            n/=10;
        }

        reverse(digits.begin(),digits.end());

        //先確定哪個數字是要被替換的
        int m = digits.size();
        int idx = m-1;
        for(int i = m-1; i>=1; i--){
            if(digits[i-1] < digits[i]){
                idx = i-1;
                break;
            }
        }
        if(idx == m-1) return -1;
        //開始找要跟他換的數字
        int j = m-1;
        while(digits[idx] >= digits[j]){
            j--;
        }

        swap(digits[idx],digits[j]);
        sort(digits.begin()+idx+1,digits.end());

        long long res = 0;
        for(int i =0; i<m; i++){
            res = res*10+digits[i];
        }

        if(res > INT_MAX) return -1;

        return res;

    }
};
