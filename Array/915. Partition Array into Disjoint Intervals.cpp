/*
915. Partition Array into Disjoint Intervals
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int partitionDisjoint(vector<int>& nums) {
        //這題的思路在於不管我走到哪後面的點都要小於我前面遍歷到的最大值一但又有比較小的值 那又要嘗試更新走過路途中的最大值
        int minNum = nums[0];
        int maxNum = nums[0];
        int idx = 0;
        for(int i = 1; i < nums.size(); i++){
            if(nums[i] < minNum){
                idx = i;
                minNum = maxNum;
            }
            maxNum = max(nums[i], maxNum);
        }

        return idx+1;
    }
};

/*
此題要求分割subarray成兩半 讓某一半的subarray都比另一半的小或者相等 求左半邊的最小長度
1. 肯定要不斷往後包含到最小值
2. 確認當前最大值並且與之後元素作比較

我會想先遍歷一遍找到最小值所在位置->之後將這之前的都包含進去 並且從中紀錄目前最大值 往後遍歷確定當前沒有值比他小
但其實這題的思路在於不管我走到哪後面的點都要小於我前面遍歷到的最大值一但又有比較小的值 那又要嘗試更新走過路途中的最大值
有點像是我先確認了一個最小值一路往後走確認比他還小的加入隊伍裡 當我每次確認到比我還小的值 我都要回頭看是否有其他更大的數值被加入了 這樣想代碼會更簡潔 
*/
