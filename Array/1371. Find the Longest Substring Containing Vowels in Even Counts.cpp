/*
1371. Find the Longest Substring Containing Vowels in Even Counts
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int findTheLongestSubstring(string s) {
        int n = s.size();
        vector<int> count(5,0);
        unordered_map<int,int> map;
        map[0] = -1;
        int res = 0;
        for(int i = 0; i<s.size(); i++){
            if(s[i] == 'a') count[0]+=1;
            else if(s[i] == 'e') count[1]+=1;
            else if(s[i] == 'i') count[2]+=1;
            else if(s[i] == 'o') count[3]+=1;
            else if(s[i] == 'u') count[4]+=1;
            int key = convert(count);
            if(map.find(key) != map.end()){
                res = max(res, i-map[key]);
            }
            else map[key] = i;
        }

        return res;
    }
    int convert(vector<int>& count){
        int key = 0;
        for(int i = 0; i<count.size(); i++){
            if(count[i]%2 ==1){
                key += 1<<i;
            }
        }

        return key;
    }
};

/*
最長的子字串 包含 五個字母 都是偶數
freq[i:j] = freq[1:j] - freq[1:i-1]
後兩者奇偶性相同即可
因為要求五個母音都要考慮到 用類似狀態壓縮的概念將它轉成bit 00000 01010 
*/
