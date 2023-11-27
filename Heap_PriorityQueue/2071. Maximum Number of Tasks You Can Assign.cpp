/*
2071. Maximum Number of Tasks You Can Assign
*/

// TC:O(32* nlgm+mlgm) SC:O(m)
class Solution {
public:
    int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills, int strength) {
        sort(tasks.begin(),tasks.end());

        int left = 0; int right = tasks.size();
        while(left < right){
            int mid = left + (right-left+1)/2;
            if(checkOk(tasks, workers, pills, strength, mid)){
                left = mid;
            }
            else right = mid-1;
        }

        return left;
    }

    bool checkOk(vector<int>& tasks, vector<int>& workers, int pills, int strength, int k){
        //工作比人多 
        if(k > workers.size()) return false;
        multiset<int> set(workers.begin(),workers.end());

        for(int i = k-1; i>=0; i--){
            if(*set.rbegin() >= tasks[i]){
                set.erase(--set.end());
            }
            else{
                if(pills == 0) return false;
                auto iter = set.lower_bound(tasks[i]-strength);
                if(iter == set.end()) return false;
                set.erase(iter);
                pills--;
            }
        }

        return true;
    }
};

/*
這題如果用 一個很難的任務是要放棄還是要做 要做的話是要找老師傅還是年輕人吃大力丸做
很難說哪個比較好 突破口在於如果指定你要做k件任務能否做完？ 可以那就繼續多加..->binary search
此題如果正面硬剛的話確實很難 但想到用二分搜索後我覺得難度就沒那麼高了
*/
