/*
907. Sum of Subarray Minimums
*/

// TC:O(n) SC:O(n)
class Solution {
    long long M = 1e9+7;
public:
    int sumSubarrayMins(vector<int>& arr) {
        int n = arr.size();
        vector<int> nextSmaller(n,n);
        vector<int> prevSmaller(n,-1);
        stack<int> s;//單調遞增
        for(int i = 0; i<n; i++){
            while(!s.empty() && arr[s.top()] > arr[i]){
                nextSmaller[s.top()] = i;
                s.pop(); 
            }

            if(!s.empty()) prevSmaller[i] = s.top();//其實是small or equal 方便去除重複元素
            s.push(i);
        }

        long long res = 0;
        for(int i = 0; i<n; i++){
            int a = prevSmaller[i]; int b = nextSmaller[i];
            //  a x x i x x b -> 9 種  a x i x b
            int x = i-a;
            int y = b-i;
            long long num = (arr[i]*x)%M*y%M;
            res = (res+num)%M;
        }
        
        return res;
    }
};

/*
此題考察
1. 如何利用約定來避免重複計算子數組 -> prevSmaller 其實是small or equal 重複元素的話只有最前面的會是真正的prev smaller 
2. 利用nextsmaller prevsmaller將時間複雜度降低 此做法很常用在求subarray的所有可能性
*/
