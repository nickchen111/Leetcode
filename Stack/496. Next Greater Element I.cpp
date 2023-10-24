/*
496. Next Greater Element I
*/

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        vector<int> greater = nextGreaterElement(nums2);
        //將nums2 stack跟nums2元素之間用map存起來好方便等等nums1去取用
        unordered_map<int, int> map;
        for(int i = 0; i < nums2.size(); i++){
            map[nums2[i]] = greater[i];
        }

        vector<int> ans(nums1.size());
        for(int i = 0; i<nums1.size(); i++){
            ans[i] = map[nums1[i]];
        }

        return ans;


        
    }
    vector<int> nextGreaterElement(vector<int>& nums2) {
        int n = nums2.size();
        vector<int> ans(n);
        stack<int> s;//用來儲存前面元素往後看會看得到的元素
        for(int i = n-1; i >= 0; i--){//從後面到前面把元素加進stack中
            
            //把不可能被看到的元素pop掉 因為被高的擋住了
            while(!s.empty() && s.top() <= nums2[i]){
                s.pop();
            }

            // 看一下彈出去後or not stack內是否還有元素 (if是彈出去後的話肯定比彈出去的元素還要高)
            ans[i] = s.empty() ? -1:s.top();
            s.push(nums2[i]);
        }
        return ans;
    }
};

/*
解題思路：
類似求下一個更大元素題目上一個更小的元素 ()求合不合法 似乎都可以用stack來做
從後面開始把元素放入stack中 如果有更高的元素 就把stack頂端pop出來 因為最低的人看過去不可能看到他
1. 先將num2的單調棧每個更大的元素先存放在一map中 
2. 接著num1去尋訪他對應的值放入ans數組即可

tc: o(n+m) sc: o(n+m)
*/
