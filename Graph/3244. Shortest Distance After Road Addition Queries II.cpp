/*
3244. Shortest Distance After Road Addition Queries II
*/

// TC:O(n+m) SC:O(n)
class Solution {
    vector<int> parent;
    int find(int x){
        if(x != parent[x]){
            parent[x] = find(parent[x]);
        }

        return parent[x];
    }
    void union_(int x, int y){
        x = find(x);
        y = find(y);
        if(x < y){
            parent[x] = y;
        }
        else parent[y] = x;
    }
public:
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        int count = n-1;
        parent.resize(n-1);

        iota(parent.begin(), parent.end(),0);
        
        vector<int> res(queries.size());
        // 也可以用有序集合做
        for(int i = 0; i < queries.size(); i++){
            int l = queries[i][0], r = queries[i][1]-1;
            int fr = find(r);
            int ul = find(l);
            // 路徑壓縮
            while(ul < r){
                union_(ul,fr);
                count -= 1;
                ul = find(ul+1);
            }
            res[i] = count;
        }

        return res;
    }
};

// Segment Tree  TC:O(nlgn) SC:O(n) 注意updateRange就是將這範圍的都改成某個值 而不是delta
using LL = long long;
class SegTreeNode
{
    public:
    SegTreeNode* left = NULL;
    SegTreeNode* right = NULL;
    int start, end;
    LL info;  // the sum value over the range
    bool lazy_tag; 
    LL lazy_val;
        
    SegTreeNode(int a, int b, int val)  // init for range [a,b] with val
    {                 
        lazy_tag = 0;
        lazy_val = 0;
        start = a, end = b;
        if (a==b)
        {
            info = val;
            return;
        }        
        int mid = (a+b)/2;
        if (left==NULL)
        {
            left = new SegTreeNode(a, mid, val);
            right = new SegTreeNode(mid+1, b, val);            
            info = left->info + right->info;  // check with your own logic
        }        
    }    
    
    SegTreeNode(int a, int b, vector<int>& val)  // init for range [a,b] with the same-size array val
    {                 
        lazy_tag = 0;
        lazy_val = 0;
        start = a, end = b;
        if (a==b)
        {
            info = val[a];
            return;
        }        
        int mid = (a+b)/2;
        if (left==NULL)
        {
            left = new SegTreeNode(a, mid, val);
            right = new SegTreeNode(mid+1, b, val);            
            info = left->info + right->info;  // check with your own logic
        }        
    }    
    
    void pushDown()
    {
        if (lazy_tag==1 && left)
        {
            left->info = lazy_val * (left->end - left->start + 1);
            right->info = lazy_val * (right->end - right->start + 1);
            left->lazy_tag = 1; left->lazy_val = lazy_val;
            right->lazy_tag = 1; right->lazy_val = lazy_val;
            lazy_tag = 0;  lazy_val = 0;
        }        
    } 
    
    void updateRange(int a, int b, int val)     // set range [a,b] with val
    {        
        if (b < start || a > end ) // not covered by [a,b] at all
            return;        
        if (a <= start && end <=b)  // completely covered within [a,b]
        {
            info = val * (end-start+1);
            lazy_tag = 1;
            lazy_val = val;
            return;
        }

        if (left)
        {
            pushDown();        
            left->updateRange(a, b, val);
            right->updateRange(a, b, val);
            info = left->info + right->info;  // write your own logic            
        }        
    }
    
    LL queryRange(int a, int b)     // query the sum over range [a,b]
    {
        if (b < start || a > end )
        {
            return 0;  // check with your own logic
        }
        if (a <= start && end <=b)
        {
            return info;  // check with your own logic
        }          
        
        if (left)
        {
            pushDown();     
            LL ret = left->queryRange(a, b) + right->queryRange(a, b);        
            info = left->info + right->info;    // check with your own logic
            return ret;
        }
        
        return info;   // should not reach here
    }  
};

class Solution {
public:
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) 
    {
        SegTreeNode* root = new SegTreeNode(0, n-1, 1); 
        vector<int>rets;
        for (auto& q: queries)
        {
            int a = q[0], b = q[1];
            root->updateRange(a+1, b-1,0);
            rets.push_back(root->queryRange(0, n-1)-1);            
        }
        return rets;
        
    }
};
