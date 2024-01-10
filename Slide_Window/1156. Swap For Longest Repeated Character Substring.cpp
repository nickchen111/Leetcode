/*
1156. Swap For Longest Repeated Character Substring
*/

// 資料結構優化前 TC:O(26*n) SC:O(26) 
class Solution {
public:
    int maxRepOpt1(string text) {
        int n = text.size();
        vector<int> map(26,0);
        for(auto ch : text){
            map[ch-'a'] += 1;
        }

        int res = 0;
        for(int k = 0; k < 26; k++){
            if(map[k] == 0) continue;
            vector<int> mp = map;
            int count = 0;
            int i = 0;
            int j = 0;
            while(j < n){
                //如果後面還有這個元素以及還可以再交換的話才能繼續走下去
                while(j < n && count <= 1 && mp[k] > 0){
                    //如果現在元素不是目標元素 在map裡面看是否還有扣打減除他
                    if(text[j] != 'a'+k) {
                        count += 1;
                        mp[k] -= 1;
                    }
                    else mp[k] -= 1;
                    
                    j++;
                    if(count == 2) break;
                    res = max(res, j-i);
                }
                if(mp[k] == 0) break;

                while(count >= 2){
                    if(text[i]-'a' != k) count -= 1;
                    mp[k] += 1;
                    i++;
                }

            }
        }

        return res;
    }
};

//優化後 TC:O(26*n) SC:O(26) 
class Solution {
public:
    int maxRepOpt1(string text) {
        int n = text.size();
        int map[26];
        memset(map, 0, sizeof(map));
        for(auto ch : text){
            map[ch-'a'] += 1;
        }


        int res = 0;
        for(int k = 0; k < 26; k++){
            if(map[k] == 0) continue;
            int mp[26];

            memcpy(mp, map, sizeof(map));
            int count = 0;
            int i = 0;
            int j = 0;
            while(j < n){
                //如果後面還有這個元素以及還可以再交換的話才能繼續走下去
                while(j < n && count <= 1 && mp[k] > 0){
                    //如果現在元素不是目標元素 在map裡面看是否還有扣打減除他
                    if(text[j]-'a' != k) {
                        count += 1;
                        mp[k] -= 1;
                    }
                    else mp[k] -= 1;
                    
                    j++;
                    if(count == 2) break;
                    res = max(res, j-i);
                }
                if(mp[k] == 0) break;

                while(count >= 2){
                    if(text[i]-'a' != k) count -= 1;
                    mp[k] += 1;
                    i++;
                }
            }
        }

        return res;
    }
};

/*
問說只能選兩個字元翻轉一次 能讓多少個字重複出現的最長長度為多少
at most once
字母類問題 讓某字母當作是出現最多次的 遍歷26次
何時該縮小何時該前進 當出現的次非目標字 並且 已經沒辦法swap 縮小窗口 其餘狀況除非後面已經沒有這個字了 不然就繼續擴大
*/
