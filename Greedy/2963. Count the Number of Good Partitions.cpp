/*
2963. Count the Number of Good Partitions
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int numberOfGoodPartitions(vector<int>& nums) {
        //紀錄每個點真正的起始與結束
        long long M = 1e9 + 7;
        unordered_map<int,pair<int,int>> map; 
        int n = nums.size();
        for(int i = 0; i < n; i++){
            if(map.find(nums[i]) != map.end()){
                int start = map[nums[i]].first;
                int end = i;
                map[nums[i]] = {start,end};
            }
            else {
                int start = i;
                int end = i;
                map[nums[i]]= {start,end};
            }
        }
        
        //轉成區間vector數組
        vector<pair<int,int>> arr;
        for(auto p:map){
            arr.push_back(p.second);
        }
        auto cmp = [](const pair<int,int>& a, const pair<int,int>& b){
            if(a.first != b.first)
                return a.first < b.first;
            else return a.second > b.second;
        };
        // sort by start point
        sort(arr.begin(), arr.end(),cmp);
        
        //概念類似將所有區間重疊的合併在一起 然後算剩餘區間數量
        int count = 0;
        int i = 0;
        while(i < arr.size()){
            count+=1;
            count %= M;
            int j = i + 1;
            int end = arr[i].second;
            while(j < arr.size() && arr[j].first <= end){
                end = max(arr[j].second, end);
                j++;
            }
            i = j;
        }
        vector<int> power(count+1,1);
        for(int i = 1; i <= count; i++){
            power[i] = (power[i-1]*2) % M;
        }
        
        long long res = power[count-1];
        
        return res;
        
    }
};

/*
此題問說有多少種分法將array分出的子數組跟其他子數組元素不重複
-> 每個元素都去看她最後一個有重複的位置在哪  一路包含到那去 走的路途中如果又有重複元素那就也要考慮他 -> intervals cover intervals
Create intervals of [first, last] instances of each number, and count minimum intervals to cover whole range. Answer is 2^(n - 1), modulo 10^9+7.
求最少需要多少區間的去涵蓋整個區間
xxxxxxx
  xxxxxxx
*/
