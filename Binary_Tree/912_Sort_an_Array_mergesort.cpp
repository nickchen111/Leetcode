/*
912. Sort an Array
此題可用六大sot都做做看
六大sort的模板要練到可以手刻
*/

//merge sort
clss
public:
    vector<int> sortArray(vector<int>& nums) {
        mergesort(nums, 0, nums.size()-1);

        return nums;
    }
    void mergesort(vector<int>& nums, int front, int end){
        if(front < end){
            int mid = front+ (end-front)/2;
            mergesort(nums, front, mid);
            mergesort(nums, mid+1, end);
            merge(nums, front, mid, end);
        }
    }

    const int max = INT_MAX;
    void merge(vector<int>& nums, int front, int mid, int end){
        //將傳進來的nums分兩個group比較大小
        vector<int> leftsub(nums.begin()+front, nums.begin()+mid+1);
        vector<int> rightsub(nums.begin()+mid+1, nums.begin()+end+1);//+1是為了放max

        leftsub.insert(leftsub.end(), max);//放max是為了最後剩元素比較時能順利將真正最大那項放進去
        rightsub.insert(rightsub.end(), max);

        int indexleft = 0, indexright = 0;

        for(int i = front; i <= end; i++){//這裡用two pointer的方式去比較兩邊大小
            if(leftsub[indexleft] <= rightsub[indexright]){
                nums[i] = leftsub[indexleft];
                indexleft++;
            }
            else {
                nums[i] = rightsub[indexright];
                indexright++;
            }
        }

    }
};
/*
解題思維
用merge sort的方式解 
當然也可以用其他sort 但有一些的時間複雜度就無法達到題目的要求

tc: o(nlgn) sc: o(n + lgn)
*/
