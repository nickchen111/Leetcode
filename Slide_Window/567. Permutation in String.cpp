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

//slide window TC:O(n) SC::O(k) k種字母
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int n = s1.size(); int m = s2.size();
        unordered_map<char,int> need,window;
        for(auto s:s1){
            need[s]+=1;
        }

        int left = 0;
        int right = 0;
        int valid = 0;
        while(right < m){
            char d = s2[right];
            right++;
            if(need.count(d)){
                window[d]+=1;
                if(window[d] == need[d]){
                    valid+=1;
                }
            }

            while(right-left>=n){
                if(valid == need.size()) return true;
                char c = s2[left];
                left+=1;
                if(need.count(c)){
                    if(window[c] == need[c]) valid-=1;
                    window[c]-=1;
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
