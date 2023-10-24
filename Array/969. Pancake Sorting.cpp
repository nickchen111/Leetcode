/*
969. Pancake Sorting
*/


TC:O(n^2) SC:O(n) 
class Solution {
    vector<int> res;
public:
    vector<int> pancakeSort(vector<int>& arr) {
        sort(arr, arr.size());

        return res;
    }

    void sort(vector<int>& arr, int n){
        //base case
        if(n == 1) return;

        int max = 0;
        int maxIndex = 0;
        for(int i = 0; i<n; i++){
            if(arr[i] > max){
                max = arr[i];
                maxIndex = i;
            }
        }

        reverse(arr, 0, maxIndex);
        res.push_back(maxIndex+1);//題目是從1直接開始計算
        reverse(arr,0,n-1);
        res.push_back(n);
        
        //遞迴調用
        sort(arr,n-1);//每次都確定好底下那層
    }

    void reverse(vector<int>& arr, int i, int j){
        while(i < j){
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }
};

//不用遞迴的寫法 TC:O(n^2) SC:O(n)
class Solution {
    vector<int> res;
public:
    vector<int> pancakeSort(vector<int>& arr) {
        int n = arr.size();
        int j = n-1;

        while(j){
            int maxIndex = 0;
            for(int i = 0; i<=j; i++){
                if(arr[i] >= arr[maxIndex]){
                    maxIndex = i;
                }
            }

            reverse(arr.begin(), arr.begin()+maxIndex+1);
            reverse(arr.begin(), arr.begin()+j+1);
            res.push_back(maxIndex+1);
            res.push_back(j+1);
            j--;
        }

        return res;
    }
};

/*
此題挺有趣的 問你看你能用任意幾次都行 但要給出你具體的翻轉方式將疊在一起大小不一的燒餅
翻轉成由大到小
解題想法是遍歷出一個最大的 將最大的掀翻轉到最上面 再將最上面的跟當前最下面的來做翻轉
會用到遞迴
*/
