/*
1160. Find Words That Can Be Formed by Characters
*/

// TC:O(m*n) SC:O(n)
class Solution {
public:
    int countCharacters(vector<string>& words, string chars) {
        unordered_map<int,int> map;
        for(const auto &ch : chars){
            map[ch] += 1;
        }
        int res = 0;
        for(int i = 0; i < words.size(); i++){
            unordered_map<int,int> check;
            bool flag = 0;
            for(const auto &ch : words[i]){
                check[ch] += 1;
                if(check[ch] > map[ch]){
                    flag = 1;
                    break;
                }
            }
            if(flag == 0) res += words[i].size();
        }

        return res;
    }
};
