/*
703. Kth Largest Element in a Stream
*/

//用multiset
class KthLargest {
    multiset<int> set;
    int n;
public:
    KthLargest(int k, vector<int>& nums) {
        n =k;
        for(auto num:nums){
            set.insert(num);
        }
        while(set.size() > k){
            set.erase(set.begin());
        }
    }
    
    int add(int val) {
        
        set.insert(val);
        while(set.size() > n){
            set.erase(set.begin());
        }
        return *set.begin();
    }
};

//用Pq
class KthLargest {
    int k;
    priority_queue<int, vector<int>, greater<int> > pq;
public:
    KthLargest(int k, vector<int>& nums) {
        for(auto num:nums){
            pq.push(num);
        }
        while(pq.size() > k){
            pq.pop();
        }
        this->k = k;
    }
    
    int add(int val) {
        pq.push(val);
        while(pq.size() > k){
            pq.pop();
        }

        return pq.top();
    }
};

/*
數據流題型
基本的priority queue數據結構考察 唯一下需注意的是當一開始建構時nums為空的情況 
需在一開始就建立global int k 告示k是多大
tc: o(lgk) sc:O(k)
*/
