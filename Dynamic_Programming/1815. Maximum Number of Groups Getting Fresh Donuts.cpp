/*
1815. Maximum Number of Groups Getting Fresh Donuts
*/

// 記憶化 TC:O(batch^n) SC:O(batch^n)
class Solution {
    int batch,n;
    using LL = long long;
    unordered_map<LL, int> memo;
public:
    int maxHappyGroups(int batchSize, vector<int>& groups) {
        batch = batchSize;
        n = groups.size();

        vector<int> count(batch);
        for(const auto &num:groups){
            count[num % batch] += 1;
        }
        LL state = 0;//要紀錄的長度為5*9 = 45
        for(int i = 0; i < batch; i++){
            state += (LL)count[i] << (i*5);
        }

        return DFS(state, 0, 0); // count presum i i代表用了幾個
    }

    int DFS(LL state, int presum, int i){
        if(i == n) return 0;
        if(memo.find(state) != memo.end()) return memo[state];
        //記憶化 這裡要看這些餘數被拿取的狀態 -> count -> 裡面最多32 用二進位5個bit可以表達
        
        int bonus = (presum%batch == 0);
        int res = 0;
        for(int j = 0; j < batch; j++){
            if((state >>(j*5))%32 == 0) continue;
            state -= 1ll << (j*5);
            res = max(res, DFS(state, (presum+j)%batch, i+1));
            state += 1ll << (j*5);
        }

        memo[state] = res+bonus;

        return res+bonus;

    }
};

/*
permutation 30*29*28
在想成前綴和 
因為主要還是想求他跟batchsize的餘數 
3 2 | 5 | 4 3 3 | 1  batch = 5 
1 <= batchSize <= 9 - > 9*9*9 .... 9^30次方
但其實也沒那麼多 因為這些選擇是會分配到0~9這串之中的
worse case 狀況 平均分配 30/9-> 4 4 4 4 4 -> 5^9次方
*/

// 次佳解 還沒記憶化->TLE 
class Solution {
    int batch,n;
public:
    int maxHappyGroups(int batchSize, vector<int>& groups) {
        batch = batchSize;
        n = groups.size();
        vector<int> count(batch);//放餘數
        for(auto num:groups){
            count[num % batch] += 1;
        }
        return DFS(count, 0, 0); // count presum i i代表用了幾個
    }

    int DFS(vector<int>& count, int presum, int i){
        if(i == n) return 0;

        //記憶化 這裡要看這些餘數被拿取的狀態 -> count -> 裡面最多32 用二進位5個bit可以表達
        
        int bonus = (presum%batch == 0);
        int res = 0;
        for(int j = 0; j < batch; j++){
            if(count[j] == 0) continue;
            count[j]-=1;
            res = max(res, DFS(count, presum+j, i+1));
            count[j]+=1;
        }

        return res+bonus;

    }
};
