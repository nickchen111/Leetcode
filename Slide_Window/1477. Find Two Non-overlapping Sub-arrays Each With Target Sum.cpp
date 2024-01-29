/*
1477. Find Two Non-overlapping Sub-arrays Each With Target Sum
*/



// Presum + Hash Map + 似Rolling array TC:O(n) SC:O(n)
class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        vector<int> pos(n, INT_MAX);
        vector<int> presum(n);
        for(int i = 0; i < n; i++){
            presum[i] = (i - 1 < 0 ? 0 : presum[i-1]) + arr[i];
        }

        int res = INT_MAX;
        unordered_map<int, int> map; // presum -> pos
        map[0] = -1;
        int minLen = INT_MAX;
        for(int i = 0; i < n; i++){
            int cur = presum[i];
            if(map.find(cur-target) != map.end()){
                int lastPos = map[cur-target];
                int len1 = i-lastPos;
                if(lastPos >= 0 && pos[lastPos] != INT_MAX){
                    res = min(res, pos[lastPos] + len1);
                }
                minLen = min(minLen,  len1);
            }

            map[presum[i]] = i;
            pos[i] = minLen;
        }

        return res == INT_MAX ? -1 : res;
    }
};


// Binary Search + Presum + Hash Map TC:O(nlgn) SC:O(n)
class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        map<int,int> pos; // pos -> minLen
        vector<int> presum(n);
        for(int i = 0; i < n; i++){
            presum[i] = (i - 1 < 0 ? 0 : presum[i-1]) + arr[i];
        }

        int res = INT_MAX;
        unordered_map<int, int> map; // presum -> pos
        map[0] = -1;
        for(int i = 0; i < n; i++){
            int cur = presum[i];
            if(map.find(cur-target) != map.end()){
                int lastPos = map[cur-target];
                int len1 = i-lastPos;
                if(pos.size() > 0) {
                    //lastPos本身也可以被這次的長度計算在內 所以用upper_bound
                    auto iter = pos.upper_bound(lastPos);
                    if(iter != pos.begin()){
                        iter = prev(iter,1);
                        res = min(res, iter->second + len1);
                    }
                    
                    auto iter2 = --pos.end();
                    pos[i] = min(iter2->second, len1);
                }
                else if(pos.size() == 0){
                    pos[i] = len1;
                }
            }

            map[presum[i]] = i;
        }

        return res == INT_MAX ? -1 : res;
    }
};


/*
找兩個不重疊區域的subarray 他們的和都是target   
讓這兩個區域的長度加總最短可以是多少
x x x x pos x x i
(4,4), (5,3),(6,2)
(1,4),(3,5), (5,6)
我的想法是先用一個數組去計算presum 可以在之後幫我們快速找出當前有沒有區間是相加等於target
然後用一個數組紀錄到某個點為止最短的合法數組長度多少
1. 用Hash Map去紀錄走到某個數字為止最好的長度 之後就藉由二分的方式去找
2. 直接紀錄一個數組 每走一步就紀錄當下找到的最短長度 就可以用O(1)時間查找
這題剛開始先想錯邏輯 以為每走一步如果發現他前面index的長度比他長就去掉 但是後面的可能性還是有可能去取道較長的那段區間
再來是map iter不熟 iter取出來算是指針 要用->first, ->second去取值 再來是用lower_bound邏輯錯誤 當下presum找到的lastpos那點也要被算進去在內所以用upper_bound
*/
