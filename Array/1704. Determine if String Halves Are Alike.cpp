/*
1704. Determine if String Halves Are Alike
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    bool halvesAreAlike(string s) {
        unordered_set<char> set = {'a','e','i','o','u','A','E','I','O','U'};
        
        int count1 = 0, count2 = 0;
        int n = s.size();

        for(int i = 0; i < n/2; i++){
            if(set.find(s[i]) != set.end()){
                count1 += 1;
            }
        }
        for(int i = n/2; i < n; i++){
            if(set.find(s[i]) != set.end()){
                count2 += 1;
            }
        }

        return count1 == count2;
    }
};
