/*
1124. Longest Well-Performing Interval
*/

//TC:O(n) SC:O(n)
class Solution {
public:
    int longestWPI(vector<int>& hours) {
        
        vector<int> presum({0});
        int sum =0;
        for(int i = 0; i<hours.size(); i++){
            if(hours[i] > 8) sum+=1;
            else sum-=1;
            presum.push_back(sum);
        }
        //stack計算單調遞減數組
        stack<int> s;
        for(int i=0; i<presum.size(); i++){
            if(s.empty() || presum[s.top()] > presum[i]){
                s.push(i);
            }
        }
        int res = 0;
        //從後往前開始找
        for(int j = presum.size()-1; j>=0; j--){
            while(!s.empty() && presum[s.top()] < presum[j]){
                res = max(res, j-s.top());
                //因為在往前的元素肯定不會比現在這個元素來的結果寬
                s.pop();
            }
        }

        return res;
    }
};
/*
此題可以先將大於8的變成1 小於八的都是-1 做presum數組
就轉換成 求presum[j] > presum[i-1]的最長範圍是多少
如果是要用O(n)時間做->用stack 單調遞增沒有意義 每個元素都會去找最前面的數值作配對  所以用單調遞減
*/
