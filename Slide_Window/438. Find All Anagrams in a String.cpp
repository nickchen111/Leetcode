/*
438. Find All Anagrams in a String
*/



//slide window TC:O(n) SC:O(k)
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int n = s.size();
        int m = p.size();
        unordered_map<char,int> need,window;
        for(auto s:p){
            need[s]+=1;
        }
        vector<int> res;
        int left = 0; int right = 0; int valid = 0;
        while(right< n){
            char d = s[right];
            right++;
            if(need.count(d)){
                window[d]+=1;
                if(window[d] == need[d]) valid+=1;
            }

            while(right-left == m){
                if(valid == need.size()) res.push_back(left);
                char c = s[left];
                left++;
                if(need.count(c)){
                    if(window[c] == need[c])
                        valid-=1;
                    window[c]-=1;
                }
            }
        }

        return res;
    }
};

/*
此題是想問說如果一字串中包含一個字串的異位詞anagram 請返回他的起始索引位置
仍然是需要一個valid 去紀錄ok的結果 跟need 紀錄需要什麼
1.用模板先想出何時該擴大何時該縮小
2.什麼位置可以將答案更新
*/
