/*
975. Odd Even Jump
*/

// TC:O(nlgn) SC:O(n)
class Solution {
public:
    int oddEvenJumps(vector<int>& arr) {
        int n = arr.size();
        vector<bool> dp_odd(n);
        vector<bool> dp_even(n);
        dp_odd[n-1] = true;
        dp_even[n-1] = true;
        unordered_map<int,int> map;//val->idx
        map[arr.back()] = n-1;
        set<int> set;
        set.insert(arr.back());
        for(int i = n-2; i>=0; i--){
            //假設這一步是奇數
            auto iter1 = set.lower_bound(arr[i]);
            if(iter1 != set.end()){
                int j = map[*iter1];
                dp_odd[i] = dp_even[j];
            }
            //假設是偶數步
            auto iter2 = set.upper_bound(arr[i]);
            if(iter2 != set.begin()){
                iter2 = prev(iter2,1);
                int j = map[*iter2];
                dp_even[i] = dp_odd[j];
            }

            set.insert(arr[i]);
            map[arr[i]] = i;//遇到一樣的數字總是只會記得最靠前的
        }

        int count = 0;
        for(int i = 0; i<n; i++){
            if(dp_odd[i] == 1) count++;
        }

        return count;
    }
};

//單純用map更快
class Solution {
public:
    int oddEvenJumps(vector<int>& arr) {
        int n = arr.size();
        vector<bool> dp_odd(n);
        vector<bool> dp_even(n);
        dp_odd[n-1] = true;
        dp_even[n-1] = true;
        map<int,int> map;//val->idx
        map[arr.back()] = n-1;
        
        for(int i = n-2; i>=0; i--){
            //假設這一步是奇數
            auto iter1 = map.lower_bound(arr[i]);
            if(iter1 != map.end()){
                int j = iter1->second;
                dp_odd[i] = dp_even[j];
            }
            //假設是偶數步
            auto iter2 = map.upper_bound(arr[i]);
            if(iter2 != map.begin()){
                iter2 = prev(iter2,1);
                int j = iter2->second;
                dp_even[i] = dp_odd[j];
            }

            map[arr[i]] = i;//遇到一樣的數字總是只會記得最靠前的
        }

        int count = 0;
        for(int i = 0; i<n; i++){
            if(dp_odd[i] == 1) count++;
        }

        return count;
    }
};


/*
此題的規則是如果某個數字是走第奇數次的步數 那她就要找下一個比他大於等於的數字 如果這種的有重複 那麼優先選最前面的
走偶數次的話 就要找跟他最靠近的小於等於的數字 重複一樣找最靠前的
考點兩個
1. dp要想到要走到終點就要看他前面能否走到他 所以會是從後往前遍歷
2. 從我這個點想去找後面 比我大or小要怎麼找！？ a. 用二分 b. 要用hash map存idx
*/
