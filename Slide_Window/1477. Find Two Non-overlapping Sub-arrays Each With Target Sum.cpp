/*
1477. Find Two Non-overlapping Sub-arrays Each With Target Sum
*/

// 最佳解 前後綴分解 Slide Window TC:O(n) SC:O(nclass Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        vector<int> suffix(n, INT_MAX/2);
        int sum = 0;
        int min_len = INT_MAX/2;
        int i = n-1;
        for(int j = n-1; j >= 0; j--){
            sum += arr[j];
            while(i > j && sum > target) {
                sum -= arr[i];
                i--;
            }
            if(sum == target){
                min_len = min(min_len, i-j+1);
            }
            
            suffix[j] = min_len;
        }
        
        min_len = INT_MAX/2;
        int res = INT_MAX/2;
        i = 0;
        sum = 0;
        for(int j = 0; j < n; j++){
            sum += arr[j];
            while(i < j && sum > target) {
                sum -= arr[i];
                i++;
            }

            if(sum == target){
                min_len = min(min_len, j-i+1);
                if(j+1 < n)
                    res = min(res, min_len + suffix[j+1]);
            }
        }

        return res == INT_MAX/2 ? -1 : res;
    }
};



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
        int minLen = INT_MAX;
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

                    pos[i] = min(minLen, len1);
                    minLen = min(minLen, len1);
                }
                else if(pos.size() == 0){
                    pos[i] = len1;
                    minLen = min(minLen, len1);
                }
            }

            map[presum[i]] = i;
        }

        return res == INT_MAX ? -1 : res;
    }
};


/*
最優解思路
要問你兩個不重疊的subarray 他們的和都是target
問說這兩個subarrray 的長度加總最短是多少

從簡單到困難:
先問說如果單純要subarray等於target 你會算嗎?
滑窗然後紀錄長度 現在問說要兩個不重疊的 不就是要問你某個位置他的前後最短的符合條件的subarray 加總哪個最短
滑窗的時候紀錄 最終位置跟他的長度

次優解思路
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
