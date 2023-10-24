/*
567. Permutation in String
*/

//10/9 slide window TC:O(26*n) SC:O(26)
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        vector<int> table1(26,0);
        for(auto ch:s1){
            table1[ch-'a']+=1;
        }

        int n = s1.size();
        vector<int> table2(26,0);
        for(int i = 0; i<s2.size(); i++){
            table2[s2[i]-'a']+=1;
            if(i >= n-1){
                if(table1 == table2) return true;
                table2[s2[i-n+1]-'a']-=1;
            }
        }

        return false;
    }
};

//slide window tc: o(n) sc:o(k)
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int left = 0, right = 0;
        unordered_map<char, int> need, window;
        int valid = 0;
        for(char c:s1){
            need[c]++;
        }

        while(right < s2.size()){
            char s = s2[right];
            right++;
            if(need.count(s)){
                window[s]++;
                if(window[s] == need[s]){
                    valid++;
                }
            }

            while(right - left >=s1.size()){//這裡也可寫成if畢竟是不變大小的窗口
                if(valid == need.size()) return true;

                char d = s2[left];
                left++;
                if(need.count(d)){
                    if(window[d] == need[d]){
                        valid--;
                    }
                    window[d]--;
                }
            }
        }
        return false;
    }
};

/*
解題思路
此題是要求不論排列是否有一連續的子串可以包含某個字串

一樣是套用模板 去思考何時該滑動窗口擴大跟縮小
此題特色是窗口的size擴張到一定之後就會以不變大小的方式滑動
*/
