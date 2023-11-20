/*
2305. Fair Distribution of Cookies
*/

// TC:O(k*2^n) SC:(2^n)
class Solution {
    int k;
public:
    int distributeCookies(vector<int>& cookies, int k) {
        //此即分配問題 並且將分配到最多的盡量最小化
        this->k = k;
        int n = cookies.size();
        sort(cookies.rbegin(),cookies.rend());
        int low = cookies[n-1];
        int high = accumulate(cookies.begin(),cookies.end(), 0);
        while(low < high){
            int mid = low + (high-low)/2;
            vector<int> child(k,0);
            if(backtrack(cookies,child,0,mid)){
                high = mid;
            }
            else low = mid+1;
        }

        return high;
    }

    bool backtrack(vector<int>& cookies, vector<int>& child, int cur, int th){
        //都分完了
        if(cur == cookies.size()) return true;

        bool flag = 0;
        for(int i = 0; i<k; i++){
            if(child[i]+cookies[cur] > th) continue;
            if(child[i] == 0){
                if(flag) return false;
                else flag = 1;
            }

            child[i]+=cookies[cur];
            if(backtrack(cookies,child,cur+1,th)) return true;
            child[i]-=cookies[cur];
        }

        return false;
    }
};
