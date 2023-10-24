/*
1081. Smallest Subsequence of Distinct Characters
*/

//TC:O(n) SC:O(1)
class Solution {
public:
    string smallestSubsequence(string s) {
        unordered_map<char,int> map;//判斷有幾個
        unordered_set<char> set;//判斷是否已經有了
        string res;
        for(int i = 0; i<s.size(); i++){
            map[s[i]]++;
        } 

        for(int i = 0; i <s.size(); i++){
            if(set.find(s[i]) !=set.end()){
                map[s[i]]--;
                continue;
            }
            while(res.size() > 0 && res.back() > s[i] && map[res.back()]>0){
                set.erase(res.back());
                res.pop_back();
            }

            //沒有加入過的情況
            res+=s[i];
            set.insert(s[i]);
            map[s[i]]--;
        }

        return res;
    }
};
/*
求一個每個字母都至少出現過一次的盡量保持從小到大排序的subsequence
所以如果是這種情況：
abcdx [e] 就要去判定x後面還有沒有
沒有的話也只能這樣排 abcdxe
*/
