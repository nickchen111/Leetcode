/*
1624. Largest Substring Between Two Equal Characters
*/

//TC:O(n) SC:O(26)
class Solution {
public:
    int maxLengthBetweenEqualCharacters(string s) {
        vector<int> posStart(26,-1);
      
        unordered_map<int,int> map;
        int n = s.size();
         int res = -1;
        for(int i = 0; i < n; i++){
            if(map[s[i]-'a'] == 0){
                map[s[i]-'a'] += 1;
                posStart[s[i]-'a'] = i;
            }
            else {
                res = max(res, i - posStart[s[i]-'a']-1);
            }
        }

        return res;
    }
};

// TC:O(n) SC:O(26)
class Solution {
public:
    int maxLengthBetweenEqualCharacters(string s) {
        vector<int> posStart(26,-1);
        vector<int> posEnd(26,-1);
        unordered_map<int,int> map;
        int n = s.size();
        for(int i = 0; i < n; i++){
            if(map[s[i]-'a'] == 0){
                map[s[i]-'a'] += 1;
                posStart[s[i]-'a'] = i;
            }
            else {
                map[s[i]-'a'] += 1;
                posEnd[s[i]-'a'] = i;
            }
        }

        int res = -1;
        for(auto &p: map){
            if(p.second >= 2){
                int x = p.first;
                res = max(res, posEnd[x] - posStart[x]-1);
            }
        }

        return res;
    }
};


/*
此題問說 兩個相同字之間最長的字串為多長
如果沒有任何字出現兩次 return -1
*/
