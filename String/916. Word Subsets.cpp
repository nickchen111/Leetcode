/*
916. Word Subsets
*/

// Vector -> TC:O(n*k) k為字串平均長度 SC:O(26)
class Solution {
public:
    vector<string> wordSubsets(vector<string>& words1, vector<string>& words2) {
        vector<int> need(26,0);
        for(const auto& word:words2){
            vector<int> temp(26,0);
            for(const auto& ch : word){
                temp[ch-'a'] += 1;
            }
            for(int i = 0; i < 26; i++){
                need[i] = max(need[i], temp[i]);
            }
        }
    

        vector<string> res;
        for(const auto& word:words1){
            vector<int> check(26,0);
            bool flag = 1;
            for(const auto& ch:word){
                check[ch-'a'] += 1;
            }
            for(int i = 0; i < 26; i++){
                if(check[i] < need[i]){
                    flag = 0;
                    break;
                }
            }
            if(flag) res.push_back(word);
        }

        return res;
    }
};

// Map -> TC:O(n*k) k為字串平均長度 SC:O(26*t)
class Solution {
public:
    vector<string> wordSubsets(vector<string>& words1, vector<string>& words2) {
        unordered_map<char, int> need;
        for(const auto& word:words2){
            unordered_map<char,int> check;
            for(const auto& ch : word){
                if(need.find(ch) == need.end()){
                    need[ch] += 1;
                    check[ch] += 1;
                }
                else {
                    check[ch] += 1;
                    if(need[ch] < check[ch]){
                        need[ch] = check[ch];
                    }
                }
            }
        }
        
        int target = need.size();

        vector<string> res;
        for(const auto& word:words1){
            int count = 0;
            unordered_map<char, int> map;
            bool flag = 0;
            for(const auto& ch : word){
                if(need[ch] != 0){
                    map[ch] += 1;
                    if(map[ch] == need[ch]) {
                        count++;
                    }
                    if(count == target) {
                        res.push_back(word);
                        flag = 1;
                    }
                }
                if(flag) break;
            }
        }

        return res;
    }
};
