/*
167. Two Sum II - Input Array Is Sorted
*/


// hash map TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int n = numbers.size();
        unordered_map<int,int> map;
        for(int i =0; i<n; i++){
            map[numbers[i]] = i;
        }

        for(int i = 0; i<n; i++){
            if(i && numbers[i] == numbers[i-1]) continue;//去重 但這題只有一個答案 也是不必做這個操作
            int cur = target - numbers[i];
            if(map.count(cur)) return {i+1,map[cur]+1};

        }

        return {};
    }
};



// two pointer TC:O(n) SC:O(1)
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int n = numbers.size();
        int i =0; int j = n-1;
        while(i<j){
            int sum = numbers[i]+numbers[j];
            if(sum > target){
                j--;
            }
            else if(sum < target){
                i++;
            }
            else return {i+1,j+1};
        }

        return {};
    }
};

