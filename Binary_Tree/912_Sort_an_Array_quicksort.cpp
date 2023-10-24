/*
912. Sort an Array
*/


// quick sort
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        quicksort(nums, 0, nums.size()-1);

        return nums;
    }
    void quicksort(vector<int>& nums, int front, int end){
        if(front < end){
            int pivot = partition(nums, front, end); //二叉樹的前序遍歷 先決定好root
            quicksort(nums, front, pivot-1);
            quicksort(nums, pivot+1, end);
        }
    }

    int partition(vector<int>& nums, int front, int end){
        int pivot = nums[end];
        int i = front -1; //去紀錄有多少個比pivot小的指針
        for(int j = front; j < end; j++){ //j 從front 去遍歷到end-1 看有多少個數字比pivot =end  小
            if(nums[j] < pivot){
                i++;
                swap(&nums[i], &nums[j]);
            }
        }
        //如果都比完了之後
        i++;
        swap(&nums[i], &nums[end]);

        return i;
    }
    
    void swap(int* a, int* b){
        int temp = *a;
        *a = *b;
        *b = temp;
    }

};
/*
解題思維
8/20 用quick sort解 worse case的話 o(n ^2) TLE
1.需要quicksort去拆解數組 
2. partition去將pivot歸位
3. swap函式手刻
用merge sort的方式解 tc: o(nlgn) sc: o(n + lgn)
當然也可以用其他sort 但有一些的時間複雜度就無法達到題目的要求
*/
