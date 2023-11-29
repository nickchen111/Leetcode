/*
2289. Steps to Make Array Non-decreasing
*/

// TC:O(n) SC:O(n) 第一個解法 用list
class Solution {
public:
    int totalSteps(vector<int>& nums) {
        int n = nums.size();
        list<int> List;
        unordered_map<int, list<int>::iterator> idx2iter;
        for(int i = 0; i<n; i++){
            List.push_back(i);
            idx2iter[i] = (--List.end());
        }

        queue<int> q;
        for(int i = n-1; i>=1; i--){
            if(nums[i] < nums[i-1]) q.push(i);
        }

        //BFS概念先將第一輪的erase 在加入之後的元素判斷是否需刪除
        int step = 0;
        while(!q.empty()){
            int sz = q.size();
            vector<int> candidates;
            for(int i = 0; i<sz; i++){
                //後面的會先被彈出來 所以紀錄出後面準備被刪除的後一個元素是沒問題的
                int idx = q.front();
                q.pop();
                auto iter = idx2iter[idx];
                if(next(iter) != List.end() && (candidates.empty() || candidates.back() != *next(iter))){
                    //需保證裡面部會包含重複元素
                    candidates.push_back(*next(iter));
                }
                //這裡會重複刪除就會報錯
                List.erase(iter);
            }

            for(int j:candidates){
                auto iter = idx2iter[j];
                if(iter != List.begin() && nums[*prev(iter)] > nums[j]){
                    q.push(j);
                }
            }
            step++;
        }

        return step;
    }
};

//第二個解法 較快
class Solution {
public:
    int totalSteps(vector<int>& nums) {
        int n = nums.size();
        vector<int> next(n);
        vector<int> remove(n);

        for(int i = 0; i<n; i++){
           next[i] = i+1;
        }

        queue<pair<int,int>> q;
        for(int i = n-1; i>=1; i--){
            if(nums[i] < nums[i-1]) q.push({i-1,i});
        }

        //BFS概念先將第一輪的erase 在加入之後的元素判斷是否需刪除
        int step = 0;
        while(!q.empty()){
            int sz = q.size();
            
            for(int i = 0; i<sz; i++){
                auto [l,r] = q.front();
                q.pop();

                //這段也很重要
                if(remove[l]) continue;

                remove[r] = 1;
                int j = next[r];
                while(j != n && remove[j]){
                    j = next[j];
                }
                //這段code做路徑壓縮
                next[r] = j;
                if(j != n && nums[l] > nums[j]){
                    q.push({l,j});
                }
            }

            step++;
        }

        return step;
    }
};

/*
此題第一個解法會用到以前LRU LFU的數據結構 list+hash
List: {0,1,2,3,4,...}
Hash: key:idx value list::iterator
idx->刪除 nums[*prev(hash[idx])] > nums[idx] -> List.erase(hash[idx]) 刪除後還會有他下一個跟他連結的點進來 此點可能會在下一輪被刪除 ->似BFS
但是跑得較慢因為用的數據結構比較笨重 雖然時間複雜度量級還是O(n)
第二個解法 不用那麼笨重的數據結構 改用vector紀錄每個點左右 {l,r} 這樣每次刪除節點後 只要從去加入被刪除節點右邊的數值
並且需要一些code做狀態壓縮 讓他不用每次都要走很長的路徑
第三個解法單調棧 太難想到了略過
[i-1 i i+1 i+2 i+3 i+4....j-1 j]
     x  x.  x.  x.  x.     x. O
*/
