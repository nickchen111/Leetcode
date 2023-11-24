/*
1542. Find Longest Awesome Substring
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int longestAwesome(string s) {
        int n = s.size();
        vector<int> count(10,0);
        unordered_map<int,int> map;
        map[0] = -1;
        int res = 0;
        for(int i = 0; i<n; i++){
            count[s[i]-'0']+=1;
            int key = convert(count);
            if(map.find(key) != map.end()){
                res = max(res, i-map[key]);
            }
            for(int k = 0; k<10; k++){
                int newkey = key;
                //翻轉其中一位為0的k 如果之前也有就代表找到了
                if(((key>>k)&1) == 0){
                    newkey+=(1<<k);
                }
                else newkey-=(1<<k);

                if(map.find(newkey) != map.end()){
                    res = max(res, i-map[newkey]);
                }
            }
            if(map.find(key) == map.end()) map[key] = i;
        }

        return res;
    }

    int convert(vector<int>& count){
        int key = 0;
        for(int i = 0; i<count.size(); i++){
            if(count[i]%2 == 1){
                key+=(1<<i);
            }
        }

        return key;
    }
};

/*
此題跟1371是類似的概念
此題要求回文串 那就想回文串的定義 
1. 字元皆是偶數
2.只有一個奇數字元
將0~9的 count狀況轉成 bit 存取
判斷奇偶數 都是偶數 就可做 但還要處理只有一個奇數狀況
*/
