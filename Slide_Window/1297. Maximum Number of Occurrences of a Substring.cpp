/*
1297. Maximum Number of Occurrences of a Substring
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int maxFreq(string s, int maxLetters, int minSize, int maxSize) {
        int n = s.size();
        unordered_map<char, int> freq;
        unordered_map<string, int> map;
        int j = 0;
        string temp = "";
        for(int i = 0; i <= n - minSize; i++){
            
            while(j < n && j-i+1 <= minSize){
                temp += s[j];
                freq[s[j]] += 1;
                j++;
            }

            if(freq.size() <= maxLetters){
                map[temp] += 1;
            }
            
            freq[s[i]] -= 1;
            if(freq[s[i]] == 0) freq.erase(s[i]);
            temp.erase(temp.begin());
        }

        int res = 0;
        for(auto p : map){
            res = max(res, p.second);
        }

        return res;
    }
};

/*
找一串字串有多少個符合以下條件
1. 字串獨特的字少於等於 maxLetters -> map來計算
2. 字串長度介於  minSize maxSize -> slide window 長度
符合條件的字串哪一個出現次數最多
這題如果讓相等於最小長度的狀況下繼續往前走 那麼就會錯失下個字的最短長度的可能性..自己在寫的時候沒有想到這件事情
主要還是要轉念一想最小長度出現的次數 肯定大於或者等於 最大長度頻率最高的出現次數 那麼就只要在意在minSize狀況下有多少種組合即可
就算在此minSize之後接的頻率太高 但是minSize本身也是合法的 不影響結果的計算 反而證實了最大長度出現頻率小於最小長度的狀況
*/
