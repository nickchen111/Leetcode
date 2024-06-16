/*
3187. Peaks in Array
*/

// TC:O(n + m log n) SC:O(n)
using LL = long long;
class SegTreeNode
{
    public:
    SegTreeNode* left = NULL;
    SegTreeNode* right = NULL;
    int start, end;
    LL info;  // the sum value over the range
    
        
    SegTreeNode(int a, int b, int val)  // init for range [a,b] with val
    {                 
       
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

    
    void updateRange(int a, int b, int val)     // set range [a,b] with val
    {        
        if (b < start || a > end ) // not covered by [a,b] at all
            return;        
        if (a <= start && end <=b)  // completely covered within [a,b]
        {
            info = val * (end-start+1);
            return;
        }

        if (left)
        {     
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
            LL ret = left->queryRange(a, b) + right->queryRange(a, b);        
            info = left->info + right->info;    // check with your own logic
            return ret;
        }
        
        return info;   // should not reach here
    }  
};

class Solution {
public:
    vector<int> countOfPeaks(vector<int>& nums, vector<vector<int>>& queries) 
    {
        int n = nums.size();
        vector<int>vals(n, 0);
        for (int i=1; i<n-1; i++)
        {
            if (nums[i]>nums[i-1] && nums[i]>nums[i+1])
                vals[i] = 1;
        }
        
        
        SegTreeNode* root = new SegTreeNode(0, n-1, vals); 
        
        vector<int>rets;
        for (auto query: queries)
        {
            if (query[0]==1)
            {
                int a = query[1], b = query[2];
                
                if (a+1<=b-1)
                    rets.push_back(root->queryRange(a+1, b-1));
                else
                    rets.push_back(0);
            }
                
            else
            {
                int i = query[1];
                nums[i] = query[2];
                
                if (i>=1 && i<n-1)
                {
                    int j = i;
                    int v = (nums[j]>nums[j-1] && nums[j]>nums[j+1]);
                    root->updateRange(j,j,v);                    
                }
                if (i-1>=1 && i-1<n-1)
                {
                    int j = i-1;
                    int v = (nums[j]>nums[j-1] && nums[j]>nums[j+1]);
                    root->updateRange(j,j,v);                    
                }
                if (i+1>=1 && i+1<n-1)
                {
                    int j = i+1;
                    int v = (nums[j]>nums[j-1] && nums[j]>nums[j+1]);
                    root->updateRange(j,j,v);                    
                }
                
            }                
        }
        
        return rets;
        
    }
};

/*
問說按照query順序 每當queries[i][0] = 1 時判斷出他給出的區間有多少個peak
queries[i][0] = 2 時要去更改array的某個index
問說按照queries[i][0] = 1 的每個順序有多少個peak
肯定是可以用presum快速算出peak數量
*/
