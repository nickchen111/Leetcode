/*
239. Sliding Window Maximum
*/

// 10/9 直接用函式就好哩 TC:O(n) SC:O(n/k)
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> dq;//維護單調遞減
        int n = nums.size();
        vector<int> res;

        for(int i = 0; i<n; i++){
            while(!dq.empty() && nums[dq.back()] <= nums[i]){
                dq.pop_back();
            }
            dq.push_back(i);
            while(!dq.empty() && dq.front() <= i-k){
                dq.pop_front();
            }

            if(i >= k-1){
                res.push_back(nums[dq.front()]);
            }
        }
        return res;   
    }
};

//heap TC:O(nlgk) SC:O(n/k)
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        multiset<int> set;
        vector<int> res;
        for(int i = 0; i<nums.size(); i++){
            set.insert(nums[i]);
            if(set.size() > k){
                set.erase(set.lower_bound(nums[i-k]));//也可用find
            }

            if(i >= k-1){
                res.push_back(*set.rbegin());
            }
        }

        return res;
    }
};

// 最一開始寫的 自己手刻deque
class Solution {
public:
    class monotonicQueue{
        //單調隊列的實現
    private:
        deque<int> q;
    public:
        void push(int x){
            //把比n小的都刪掉
            while(!q.empty() && q.back() < x){
                q.pop_back();
            }
            q.push_back(x);
        }

        int max(){
            return q.front();
        }

        void pop(int x){
            if(x == q.front()){
                q.pop_front();
            }
        }
    };
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        monotonicQueue window;
        vector<int> ans;

        for(int i = 0; i < nums.size(); i++){
            if(i < k-1){
                window.push(nums[i]);
            }
            else{//滑動窗口
                window.push(nums[i]);
                ans.push_back(window.max());
                window.pop(nums[i-k+1]);
            }
        }

        return ans;
    }
};

/*
解題思路：
monotonic queue
1.將k-1個元素放入q中
2. 如果等於k-1個時 將第k個元素放入似滑動窗口然後pop掉最大的 將當前最大的存入答案數組
tc: o(n) sc: o(n/k)

heap: tc: o(nlgk)

*/
