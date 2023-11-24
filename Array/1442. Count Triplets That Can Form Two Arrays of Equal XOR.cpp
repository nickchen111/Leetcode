/*
1442. Count Triplets That Can Form Two Arrays of Equal XOR
*/

// TC:O(n^2) SC:O(n)
class Solution {
public:
    int countTriplets(vector<int>& arr) {
        int n = arr.size();
        unordered_map<int,vector<int>> map;
        map[0].push_back(-1);//這裡需要特別注意整段XOR為0時需要給他一個idx
        int res = 0;
        int xor_sum = 0;
        for(int k = 0; k<n; k++){
            xor_sum^=arr[k];
            for(int i:map[xor_sum^0]){
                res+=(k-i-1);
            }
            map[xor_sum].push_back(k);
        }

        return res;
    }
};

/*
a = 之前的數一直XOR 直到j以前
b = 之前的數一直XOR 直到k為止
會發現其實j是個假命題 他可以在i 到 k之間任意一個點上
此題考察XOR了解程度 A^0 = A -> A^A = 0;

*/
