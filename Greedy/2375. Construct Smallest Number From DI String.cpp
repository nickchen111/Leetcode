/*
2375. Construct Smallest Number From DI String
*/

//思維上更好的寫法 TC: O(n) SC:O(1)
class Solution {
public:
    string smallestNumber(string pattern) {
        pattern = "I" + pattern;
        int n = pattern.size();
        string res;
        char minCh= '0';
        for(int i = 0; i < n; i++){
            int j = i + 1;
            while(j < n && pattern[j] == 'D'){
                j++;
            } 
            // IDD I -> 3個
            int count = j - i;
            for(char k = minCh + count; k >= minCh+1; k--){
                res += k;
            }
            minCh = minCh + count;
            i = j - 1;
        }

        return res;
    }
};


// Set 操作 遇到 I 就是無腦加最小的 遇到D開始收集直到結尾或者不是D為止  TC: O(nlgn + n)) SC:O(n)
//第一次遇到時我AC的做法
class Solution {
public:
    string smallestNumber(string pattern) {
        set<char> set = {'1','2','3','4','5','6','7','8','9'};
        int n = pattern.size();
        string res;
        int count = 0;

        for(int i = 0; i < n; i++){
            //如果有Ｄ 就去算有幾個D
            if(pattern[i] == 'D'){
                count++;
                //後面有串D結尾 沒處理到要考慮 i + 1 == n 的狀況
                if(i + 1 == n || pattern[i+1] != 'D'){
                    int k = count;
                    auto iter = set.begin();
                    for(int i = 0; i < k; i++){
                        iter = next(iter,1);
                    }
                    auto newiter = iter;
                    for(int i = 0; i < k; i++){
                        auto newiter = iter;
                        res += *newiter;
                        iter = prev(iter,1);
                        set.erase(newiter);
                        count--;
                    }
                }
            }
            //如果是 I 直接加入最小值
            else if(pattern[i] == 'I'){
                res += *set.begin();
                set.erase(set.begin());
            }
        }
        

        //最後一個字不管是 I or D 都會想接當下最小的
        res += *set.begin();

        return res;
    }
};


/*
此題用一串字串包含ID 表示下一個字跟這個字之間的關係 
I 代表下一個字比現在大 D就是比現在小 並且你要能夠組成1~9每個數字使用不超過一次的最小字典序可能
如果遇到D 我會想知道後面有幾個Ｄ 並且挑選目前來說最小數字+後面Ｄ出現的次數+1

1. all number at most appear once -> set to check
2. stack->count to check how many D and when no more D calculate result
另一種思路 藉由觀察看出 將字串切成好幾個區段 每個區段不是平滑的遞增就是遞減狀態 
此種寫法須在剛開始加入I 用以處理 IDD or DDI開頭的狀況
*/
