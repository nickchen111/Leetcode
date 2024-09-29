/*
3306. Count of Substrings Containing Every Vowel and K Consonants II
*/

// TC:O(n) SC:O(26)
class Solution {
    using LL = long long;
    unordered_set<char> set = {'a', 'e', 'i', 'o', 'u'};
public:
    long long countOfSubstrings(string s, int k) {
        return atLeastK(s, k) - atLeastK(s,k+1);
   }
    LL atLeastK(string& s, int k){
        int n = s.size();
        unordered_map<char, int> map;
        int count = 0;
        int vowel = 0;
        int i = 0;
        LL res = 0;
        for(int j = 0; j < n; j++){
            if(set.find(s[j]) != set.end()){
                map[s[j]] += 1;
                if(map[s[j]] == 1) vowel += 1;
            }
            else count += 1;
            
            while(count >= k && vowel == 5){
                res += (LL)(n-j);
                if(set.find(s[i]) != set.end()){
                    map[s[i]] -= 1;
                    if(map[s[i]] == 0) vowel -= 1;
                }
                else count -= 1;
                i++;
            }
        }
        
        return res;
    }
    
};

/*
至少一個aeiou 並且其餘的要剛好k個
去剛好走到k個子音判斷是否有aeiou 以及後面有幾個aeiou
*/
