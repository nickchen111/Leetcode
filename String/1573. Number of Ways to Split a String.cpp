/*
1573. Number of Ways to Split a String
*/


// TC:O(n) SC:O(n) Hash Map
class Solution {
    long long M = 1e9+7;
public:
    int numWays(string s) {
        long long n = s.size();
        unordered_map<int,int> map;
        int count = 0;
        for(int i = 0; i < n; i++){
            if(s[i] == '1'){
                count++;
                map[count] = i;
            }
        }

        if(map.size() % 3 != 0) return 0;
        if(map.size() == 0) return ((n-1)*(n-2)/2)%M;
        //每一份需要多少個 1
        long long res = 1;

        long long x = map[count/3+1] - map[count/3];
        long long y = map[count/3*2+1] - map[count/3*2];
        
        return (x*y)%M;
    }
};


// TC:O(n) SC:O(n)  Vector
class Solution {
public:
    int numWays(string s) {
        long long n = s.size();
        vector<int> pos;
        for(int i = 0; i < n; i++){
            if(s[i] == '1') pos.push_back(i);
        }

        if(pos.size() % 3 != 0) return 0;
        //每一份需要多少個 1
        int t = pos.size()/3;
        long long M = 1e9+7;
        long long res = 1;

        for(int i = t-1; i < pos.size()-1; i+=t){
            long long b = (i + 1 == pos.size() ? n-1:pos[i+1]) - pos[i];
            res = (res * b)%M;
        }
        if(pos.size() == 0) return ((n-1)*(n-2)/2)%M;
        return res;
    }
};

/*
此題問說一串由01組成的字串 問有多少種切割三等分方法 讓三個字串的1的數量相同
0 0 1 0 1 0 0 0 0 1 1 0 0 0 1 0 1 0 0 
"00000000"
一開始我的想法是用vector記錄位置 然後遍歷他 以可以切分成三等分方法遍歷 
後來看了其他解答 可以直接用map畢竟我們要的也只有兩個數字的相乘
*/
