/*
1239. Maximum Length of a Concatenated String with Unique Characters
*/

// TC:O(2^n) SC:O(2^n)
class Solution {
    int res = 0;
    vector<bool> check;
    int n;
public:
    int maxLength(vector<string>& arr) {
        n = arr.size();
        check.resize(n);
        vector<vector<int>> count(n, vector<int>(26,0));
        //判斷哪些是不合法的 就不要用   
        for(int i = 0; i < n; i++){
            for(int j = 0; j < arr[i].size(); j++){
                count[i][arr[i][j]-'a'] += 1;
                if(count[i][arr[i][j]-'a'] > 1){
                    check[i] = 1;
                }
            }
        }
        
        
        for(int i = 0; i < n; i++){
            if(check[i] == 1) continue;
            int state = 0;
            for(int k = 0; k < 26; k++){
                state += (count[i][k] << k);
            }
            backtrack(arr,count,i, arr[i].size(), state);
        }

        return res;
    }
    void backtrack(vector<string>& arr, vector<vector<int>>& count, int cur, int sum, int state){

        res = max(res, sum);

        for(int i = cur + 1; i < n; i++){
            if(check[i] == 1) continue;
            int num = 0;
            for(int j = 0; j < 26; j++){
                num += (count[i][j] << j);
            }
            if((state & num) == 0){
                backtrack(arr, count, i, sum + arr[i].size(), state | num);
            }
        }
    
    }
};

/*
用給定的字串數組組成字串 字串裡每個字都是獨特的 不能重複 這樣的字串可以多長
16*26
如果某個拼圖字串已經不符合規則 可以直接pass
16*16*26*26 直接回溯暴力解 但是當前狀態可以用狀態壓縮方式紀錄
*/
