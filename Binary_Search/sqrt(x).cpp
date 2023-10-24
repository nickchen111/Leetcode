/*


*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int mySqrt(int x) {
        int j = x/2;
        vector<int> store;
        for(int i = 0; i < j; i++){
           store.push_back(i*i);
        }
        auto pos = lower_bound(store.begin(),store.end(), x);
        prev(pos, 1);
        int y = store[pos - store.begin()];
        return y;
    }
};

int main(){
    int x = 20;
    Solution a;
    cout << a.mySqrt(x);
}