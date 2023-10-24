/*
277. Find the Celebrity🔒 名人問題
此題為graph的一種題型  人跟人之間社交關係 確實就是可以用graph來表示
*/

//brute force tc: o(n^2) sc:o(1)
class solution{
public:
    bool knows(int i, int j);
    int findCelebrity(int n) {
        if(n == 1) return 0;
        for(int cand = 0; cand < n; cand++){
            for(int other = 0; other < n; other++){
                if(cand == other) continue;
                if(know(cand, other) || !know(other, cand)){
                    break;
                }
            }
            if(other == n) return cand; //找到名人
        }
        return -1;/沒人符合
    }
};

//利用條件稍加改良 tc: o(n) sc: o(n)
//條件為人與人之間的關係條件 每次選兩個人出來可以先刪除一個人
class solution{
public:
    bool knows(int i, int j);
    int findCelebrity(int n) {
        if(n == 1) return 0;
        queue<int> q;// 使用佇列裝入所有候選人
        for(auto x:n){
            q.push(x);
        }

        //一直排除直到剩一個人
        while(q.size() >= 2){
            int cand = q.front(); q.pop();
            int other = q.front(); q.pop();

            if(know(cand, other) || !know(other, cand)){
                q.push(other);// cand 一定不是名人
            }
            else q.push(cand); //else 條件為 cand 不知other other還知道cand 所以other 一定不是名人
        }
        
        int cand = q.front; q.pop();
        for(int other = 0; ohter < n; otehr++){
            if(cand == other) continue;
            if(know(cand, other) || !know(other, cand)){
                return -1;
            }
        }
        return cand;
    }
};

//將空間降下來
//tc: o(n) sc: o(1)
class solution{
public:
    bool knows(int i, int j);
    int findCelebrity(int n) {
        int cand = 0; //利用假設的方式去做
        for(int other = 1; other < n; other++){
            if(know(cand, other) || !know(other, cand)){
                cand = other; //名人換人當去測試看看
            }
            else{
                //啥都不做
            }
        }
        
        for(int other = 0; ohter < n; otehr++){
            if(cand == other) continue;
            if(know(cand, other) || !know(other, cand)){
                return -1;
            }
        }
        return cand;
    }
};
