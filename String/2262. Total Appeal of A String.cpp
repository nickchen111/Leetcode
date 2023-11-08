/*
2262. Total Appeal of A String
*/

// TC:O(n) SC:O(26)
class Solution {
public:
    long long appealSum(string s) {
        // 跟828好像 唯一差別是兩個以上相同的字母的情況也可以貢獻一分
        int n = s.size();
        vector<int> lastpos(26,-1);
        long long res = 0;
        for(int i = 0; i<n; i++){
            int j = lastpos[s[i]-'a'];
            res+=(long long)(i-j)*(long long)(n-i);
            lastpos[s[i]-'a'] = i;
        }
        
        return res;

    }
};

/*
算是828的變形828的時候只要字串包含兩個以上相同的通通不算分 在這就要算分了
所以此題主要考察的是去重的能力 以及對只出現一次的字母的細節處理
 x x x x a x x x a x x x a x x x x
        j        i.              n-1
約定每個重複的字母不能去加入左邊出現過的重複字母 用這個方式去重
但是在左邊的重複字母可以跨到右邊的重複字母
(i-j)*(n-i)
*/
