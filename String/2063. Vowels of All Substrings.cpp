/*
2063. Vowels of All Substrings
*/


// TC:O(n) SC:O(1)
class Solution {
    using LL = long long;
    bool isVowel(char ch){
        return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
    }
public:
    long long countVowels(string word) {
        int n = word.size();
        LL res = 0;
        for(int i = 0; i < n; i++){
            if(isVowel(word[i])){
                res += (LL)(i+1) * (LL)(n-i);
            }
        }
        
        return res;

    }
};

/*
給一字串 求所有substring中有多少個母音 加總起來
要計算count subaray這種的 絕不會直接去一個一個看個字可以組成哪些sub 
用目前這個字母可以貢獻多少個subarray為出發點只要遍歷到母音就去count他的貢獻

*/
