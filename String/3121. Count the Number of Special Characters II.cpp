/*
3121. Count the Number of Special Characters II
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int numberOfSpecialChars(string word) {
        int n = word.size();
        unordered_map<char, pair<int,int>> map;
        unordered_set<char> del;
        int count = 0;
        for(int i = 0; i < n; i++){
            //是大寫
            if(map.find(word[i]) == map.end())
                map[word[i]] = {i,i};
            else map[word[i]].second = i;
        }
        
        for(auto p : map){
            if(map.find(p.first-32) != map.end()){
                int start = p.second.first;
                int end = p.second.second;
                int targetx = map[p.first-32].first;
                int targety = map[p.first-32].second;
                if(end < targetx) count += 1;
            }
        }
        
        return count;
    }
};

/*
所有的小寫字母要出現在大寫之前
小寫-32 = 大寫
去記錄每個大寫出現的位置min, max
unordered_map<int, pair<int,int>> map;
"bEbdBbc"
"cADEDee"
*/
