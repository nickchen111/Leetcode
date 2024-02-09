/*
1255. Maximum Score Words Formed by Letters Solved
*/

// TC:O(2^n) SC:O(n + 26)
class Solution {
    vector<int> count;
    int n;
    bool valid[15];//如果某個字串內的元素本身就超過上限那就完全不用考慮他了
    int res = 0;
    int memo[20000];
    vector<int> score;
public:
    int maxScoreWords(vector<string>& words, vector<char>& letters, vector<int>& score) {
        n = words.size();
        count.resize(26);
        this->score = score;
        for(int i = 0; i < n; i++){
            valid[i] = 1;
        }
        for(auto ch : letters){
            count[ch-'a'] += 1;
        }
        int state = 0;
        for(int i = 0; i < n; i++){
            vector<int> map(26);
            int sum = 0;
            for(auto ch : words[i]){
                map[ch-'a'] += 1;
                sum += score[ch-'a'];
                if(map[ch-'a'] > count[ch-'a']){
                    valid[i] = 0;
                    break;
                }
            }
            if(valid[i]){
                backtrack(map, words, sum, i+1, state + (1<<i));
            }
        }

        return res;
    }
    void backtrack(vector<int>& map, vector<string>& words, int sum, int idx, int state){
        if(idx == words.size()){
            res = max(res, sum);
            memo[state] = sum;
            return;
        }
        if(memo[state]) return;

        for(int i = idx; i < n; i++){
            if(valid[idx] == 0) continue;
            bool flag = 1;
            vector<int> map_tmp = map;
            int sum_tmp = sum;
            for(auto ch : words[i]){
                map_tmp[ch-'a'] ++;
                sum_tmp += score[ch-'a'];
                if(map_tmp[ch-'a'] > count[ch-'a']){
                    flag = 0;
                    break;
                }
            }
            if(flag){
                backtrack(map_tmp, words, sum_tmp, i+1, state + (1<<i));
            }
            backtrack(map, words, sum, i+1, state);
        }
       
    }
};

/*
給每一個字母一個分數 但只有某些字母是可以使用的並且用完就沒了 問說給你一串字串 最多可以湊出幾分
單純去做backtrack 收集可能的subset 用for loop 表示大概像是
for(int i = 0; i < n; i++){
    for(int j = i+1; j < n; j++){
        裡面的元素可取or不取 取的話要滿足元素上限 用vector取代map速度會更快 然後用memo記憶化已經走到底的可能性
    }
}
*/
