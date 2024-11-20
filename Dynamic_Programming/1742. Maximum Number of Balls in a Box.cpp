/*
1742. Maximum Number of Balls in a Box
*/

// TC:O(10^m) m 為數字的位數 SC:O(total) total為位數的最大總和
class Solution {
public:
    int countBalls(int lowLimit, int highLimit) {
        function<vector<int>(int)> countTotal = [&](int n) -> vector<int>{
            string s = to_string(n);
            int m = s.size();
            vector<int> map(50); // # of bucket -> count
            function<void(int, bool, bool, int, int)> dfs = [&](int i, bool isLimit, bool isNum, int sum, int num) -> void {
                if(i == m) {
                    if(isNum && num >= lowLimit) map[sum] += 1;
                    return;
                }
               
                if(!isNum) dfs(i+1, false, false, sum, num);
                int up = isLimit ? s[i]-'0' : 9;
                
                for(int j = 1-isNum; j <= up; j++) {
                    int tmp = num*10 + j;
                    dfs(i+1, isLimit && j == up, true, sum + j, tmp);
                }
            };
            dfs(0, true, false, 0,0);
            
            return map;
        };
        vector<int> mx = countTotal(highLimit);
        int maxFreq = 0;
        for(auto &freq : mx) {
            if(freq > maxFreq) {
                maxFreq = freq;
            }
        }

        return maxFreq;
    }
};


// 暴力 + Hash Map 
class Solution {
public:
 int sum(int n)
 {
    int s=0;
    while(n>0)
    {
        s+=n%10;
        n=n/10;
    }
    return s;
 }
    int countBalls(int lowLimit, int highLimit) {
        int arr[46]={};
        for(auto i=lowLimit;i<=highLimit;i++)
        {
            int ind=sum(i);
            arr[ind]++;
        }
        return *max_element(begin(arr),end(arr));
    }
};
