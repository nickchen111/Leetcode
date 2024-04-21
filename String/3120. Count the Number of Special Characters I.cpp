/*
3120. Count the Number of Special Characters I
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int numberOfSpecialChars(string word) {
        int n = word.size();
        unordered_map<char,int> map;
        int count = 0;
        for(int i = 0; i < n; i++){
            if(map.find(word[i]) == map.end()){
                if(map.find(word[i]-32) != map.end() || map.find(word[i]+32) != map.end()){
                    count += 1;
                }
                
            }
            map[word[i]] += 1;
        }
        
        return count;
    }
};

/*
問有多少個字母在此字串中是大小寫都包含的
*/
