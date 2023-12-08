/*
2131. Longest Palindrome by Concatenating Two Letter Words
*/

// 最粗糙解 by multiset   想法是先將所有字串放入 再從頭遍歷看是否有跟他吻合的 有的話兩者都要從set刪掉 
class Solution {
public:
    int longestPalindrome(vector<string>& words) {
        int res = 0;
        multiset<string> set(words.begin(), words.end());
        bool flag = 0;
        for(auto word : words){
            if(set.find(word) == set.end()) continue;
            if(word[0] == word[1]){
                set.erase(set.find(word));
                if(set.find(word) != set.end()){
                    res += 4;
                    set.erase(set.find(word));
                }
                else flag = true;
            }

            if(word[0] != word[1]){
                set.erase(set.find(word));
                string cur; 
                cur.push_back(word[1]);
                cur.push_back(word[0]);
                if(set.find(cur) != set.end()){
                    res += 4;
                    set.erase(set.find(cur));
                }
            }
        }

        if(flag) res += 2;

        return res;
    }
};

//轉變想法並且改成用 map減少erase使用 :改成不先放入隊列 一個一個放 一個一個比對 這樣稍微提升了時間效率
class Solution {
public:
    int longestPalindrome(vector<string>& words) {
        int res = 0;
        unordered_map<string, int> map;
        for(auto word : words){
            if(word[0] == word[1]){
                if(map.find(word) != map.end()){
                    map[word] -= 1;
                    res += 4;
                    if(map[word] == 0) map.erase(word);
                }
                else map[word] += 1;
            }
            else {
                string cur;
                cur.push_back(word[1]);
                cur.push_back(word[0]);
                if(map.find(cur) != map.end()){
                    map[cur] -= 1;
                    res += 4;
                    if(map[cur] == 0) map.erase(cur);
                }
                else map[word] += 1;
            }
        }

        for(auto p : map){
            if(p.first[0] == p.first[1]){
                res += 2;
                break;
            }
        }

        return res;
    }
};

// 最優化解 改變想法 結合一點數學思想 TC:O(n) SC:O(n)
class Solution {
public:
    int longestPalindrome(vector<string>& words) {
        unordered_map<string,int> count1, count2, count3; // 分別放ab ba aa這三種狀況
        
        for(auto str:words){
            string str2 = str;
            reverse(str2.begin(), str2.end());

            if(str == str2){
                count3[str] += 1;
            }
            else {
                string key = min(str, str2);
                if(key == str){
                    count1[key] += 1;
                }
                else {
                    count2[key] += 1;
                }
            }
        }

        int res = 0;
        for(auto &[key, val] : count1){
            int a = count1[key];
            int b = count2[key];
            int k = min(a,b);
            res += k*2*2;
        }
        
        int flag = 0;
        for(auto &[key, val] : count3){
            int k = val/2;
            res += k*2*2;
            if(val % 2 == 1){
                flag = 1;
            }
        }

        return res + flag*2;
    }
};

