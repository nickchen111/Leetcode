/*
3298. Count Substrings That Can Be Rearranged to Contain a String II
*/

// TC:O(n+m) SC:O(n+m)
class Solution {
    using LL = long long;
public:
    long long validSubstringCount(string word1, string word2) {
        int n = word1.size();
        unordered_map<int, LL> need;
        for(auto &w : word2){
            need[w-'a'] += 1;
        }
        
        LL count = 0;
        unordered_map<int,LL> map;
        int i = 0;
        LL res = 0;
        for(int j = 0; j < n; j++){
            if(need.find(word1[j]-'a') != need.end()){
                map[word1[j]-'a'] += 1;
                if(map[word1[j]-'a'] == need[word1[j]-'a']){
                    count += 1;
                }
            }
            
            while(count == need.size()){
                res += (LL)(n-j);
                if(need.find(word1[i]-'a') != need.end()){
                    if(need[word1[i]-'a'] == map[word1[i]-'a']){
                        count -= 1;
                    }
                    map[word1[i]-'a'] -= 1;
                }
                i++;
            }
        }
        
        return res;
    }
};

/*
word1 = "abcabc", word2 = "abc"
4 + 3 + 2 + 1

"dcbdcdccb"
"cdd"
6 + 4 + 4 + 4 
-> 18
*/
