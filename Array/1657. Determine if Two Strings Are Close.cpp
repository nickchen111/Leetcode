/*
1657. Determine if Two Strings Are Close
*/

// TC:O(nlgn) SC:O(n)
class Solution {
public:
    bool closeStrings(string word1, string word2) {
        if(word1.size() != word2.size()) return false;
        vector<int> arr1(26,0);
        vector<int> arr2(26,0);
        set<char> set1;
        set<char> set2;
        for(int i = 0; i < word1.size(); i++){
            arr1[word1[i]-'a']+=1;
            arr2[word2[i]-'a']+=1;
            set1.insert(word1[i]);
            set2.insert(word2[i]);
        }
        
        if(set1 != set2) return false;

        sort(arr1.begin(), arr1.end());
        sort(arr2.begin(), arr2.end());
        
        return arr1 == arr2;
    }
};

/*
此題說你可以隨意的換兩個字母的位置 或者將字串內的字母互換身份 ex abb -> baa
現在有兩個字串是否能讓他們變成一樣
這看起來只要先判斷長度是否相等 在判斷組成種類以及其數目是否相等就可判定
*/
