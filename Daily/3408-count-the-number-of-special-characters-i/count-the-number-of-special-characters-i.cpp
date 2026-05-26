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