/*
187. Repeated DNA Sequences
*/

// Rabin-Karp algorithm  TC:O(n) SC:O(n)
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        //rabin-karp演算法
        unordered_map<string,int> seen;
        vector<string> res;
        int n = s.size();
        for(int i = 0; i<n-9; i++){
            string temp = s.substr(i,10);
            seen[temp]++;
            if(seen[temp] == 2) res.push_back(temp);
        } 

        return res;
    }
};
