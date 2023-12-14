/*
2086. Minimum Number of Food Buckets to Feed the Hamsters
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int minimumBuckets(string hamsters) {
        int n = hamsters.size();
        if(n == 1 && hamsters[0] == 'H') return -1;
        else if(n == 1 && hamsters[0] == '.') return 0;
        if(n >= 3){
            if((hamsters[0] == 'H' && hamsters[1] == 'H') || (hamsters[n-2] == 'H' && hamsters[n-1] == 'H')){
                return -1;
            }
        }


        
        vector<int> pos;
        for(int i = 0; i < n; i++){
            if(hamsters[i] == 'H'){
                pos.push_back(i);
            }
        }
        if(pos.size() == n) return -1;
        
        int res;
        int start;
        bool flag = 1;
        if(pos.size() > 1){
            if(pos[1] - pos[0] == 2){
                res = 1;
                start = 2;
                flag = 0;
            }
            else {
                res = 1;
                start = 1;
            }
        }
        else {
            return pos.size();
        }

        
        for(int i = start; i < pos.size(); i++){
            if(pos[i] - pos[i-1] == 2 && flag == 1){
                flag = 0;
                continue;
            }
            else if(pos[i] - pos[i-1] == 2 && flag == 0){
                flag = 1;
                res += 1;
            }
            else {
                res += 1;
                flag = 1;
            }
            if(i+1 < pos.size() && pos[i-1] == pos[i]-1 && pos[i] == pos[i+1]-1) return -1;
        }

        return res;

    }
};

// 簡潔寫法  TC:O(n) SC:O(1)
class Solution {
public:
    int minimumBuckets(string hamsters) {
        int n = hamsters.size();
        int res = 0;
        for(int i = 0; i < n; i++){
            if(hamsters[i] != 'H') continue;
            if(i - 1 >=0 && hamsters[i-1] == '#'){
                continue;
            }
            else if(i + 1 < n && hamsters[i+1] == '.'){
                hamsters[i+1] = '#';
                res += 1;
            }
            else if(i - 1 >= 0 && hamsters[i-1] == '.'){
                hamsters[i-1] = '#';
                res += 1;
            }
            else return -1;
        }

        return res;
    }
};

/*
此題想餵所有位置上的哈姆太郎 只要他旁邊有吃的就算有餵到 問最少要放多少餅乾給他吃 or 無法都餵到
[x O x O x x O x x x x O x O]
[x O x x O x O x O x O x]
[x O x x O x O O x x x ]
[O O x x x]
1. 只要連續出現三個以上哈姆太郎就會失敗 or 一開始連續出現兩個也會失敗 or 結尾出現兩個 or n == 1 也不能為他
2. 只要其中有哈姆太郎間隔出現就只需花 1個餅乾
3. 如果哈姆太郎之間超過兩格 那就需要2個餅乾
*/
