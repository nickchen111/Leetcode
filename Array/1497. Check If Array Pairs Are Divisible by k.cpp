/*
1497. Check If Array Pairs Are Divisible by k
*/

// TC:O(n) SC:O(k)
class Solution {
public:
    bool canArrange(vector<int>& arr, int k) {
        int n = arr.size();
        unordered_map<int,int> map;
        for(auto x : arr){
            map[(x%k+k)%k] += 1;
        }
        // 處理剛好整除的狀況
        if(map[0] % 2 != 0) return false;

        //遍歷一半的餘數
        for(int i = 1; i <= k/2; i++){
            int mod = i;
            int remainder = k-i;
            if(map[mod] != map[remainder]) return false;
        }
        

        return true;
    }
};


//  TC:O(n*2) SC:O(k)
class Solution { 
public:
    bool canArrange(vector<int>& arr, int k) {
        int n = arr.size();
        unordered_map<int,int> map;
        for(auto x : arr){
            map[(x%k+k)%k] += 1;
        }
        for(int i = 0; i < n; i++){
            int mod = (arr[i]%k+k)%k;
            int mod2 = (k - mod) % k;
            if(map[mod] == 0) continue;
            if(mod == 0) {
                map[mod] -= 2;
                if(map[mod] == 0) map.erase(mod);
                else if(map[mod] < 0) return false;
            }

            else if(map.find(mod2) != map.end()){
                map[mod] -= 1;
                map[mod2] -= 1;
                if(map[mod] == 0) map.erase(mod);
                if(map[mod2] == 0) map.erase(mod2);
            }
            else return false;
        }
        

        return true;
    }
};

/*
這題要你將數組內的元素 組成一對一對 每一對的總和要可以被k整除
那就是用一個map紀錄 然後 一個一個取出看說他跟k整除的餘數有沒有互補的餘數讓他們是相加可以整除k的
3 2 -> 1 2%k+k
2 % 3 -> 2 找 1 (k - 2%k) % k
-1 % 3 -> 4 1 2
*/
