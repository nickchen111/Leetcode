/*
710. Random Pick with Blacklist
*/

// TC:O(k) SC:O(k) k為黑名單的數量
class Solution {
    int M;
    unordered_map<int,int> map;//非法對應合法
public:
    Solution(int n, vector<int>& blacklist) {
        M = n - blacklist.size();//此為合法的數目
        //將前面非法的做個跟後面合法的映射
        //因為總共的數n特別大 所以改成遍歷 黑名單數量
        unordered_set<int> set(blacklist.begin(), blacklist.end());
        
        int y = M;
        for(auto x:blacklist){
            if(x >= M) continue;
            //這裡開始是個非法但是會被蓋率計算列入可能的小於M的數字
            while(set.count(y)){
                y++;
            }
            map[x] = y;//y現在是合法的
            y++;//讓他往下個前進
        }
    }
    
    int pick() {
        int r = rand()%M;
        if(map.find(r) != map.end()){
            return map[r];
        }
        else return r;
    }
};

// 二分
class Solution {
    int n;
    vector<int> blacklist;
public:
    Solution(int n, vector<int>& blacklist) {
        sort(blacklist.begin(),blacklist.end());
        this->n = n;
        this->blacklist = blacklist;
    }
    
    int pick() {
        //二分搜尋的思維在於 從最少到最大的區間開始判斷合法的數字有幾個 如果滿足  隨機出來的數字就是答案
        int M = n - blacklist.size();
        int k = rand()%M+1;

        int left = 0;
        int right = n-1;

        while(left < right){
            //這裡需考量到 算出區間後有可能是在不合法的數字頭上算出所需合法數 所以需要找到最左邊的合法數目吻合答案
            int mid = left + (right-left)/2;
            if(countValid(mid) < k){
                left = mid+1;
            }
            else {
                right = mid;
            }
        }
        return left;
    }

    int countValid(int mid){
        int invalid = upper_bound(blacklist.begin(), blacklist.end(),mid)-blacklist.begin();
        return mid+1-invalid;//合法的數目
    }
};
