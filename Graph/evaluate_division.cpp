/*
399. Evaluate Division

*/



#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

//此題是在問給你一些node跟他們之間的edge edge的數據是兩點之間的計算除法 求現在任意給你很多對節點 他們的edge數據為何 如果不存在return -1
// dfs tc: o(e+ q*e) e為建立的時候所需時間 看有幾個pair要建立 q為他問你多少pair 如果每個都從頭到尾就要q*e sc:o(e)
class Solution {
public:
    vector<double> calcEquation(vector<vector<string>> equations, vector<double>& values, vector<vector<string>> queries) {
        //建立已知路徑
        unordered_map<string, unordered_map<string, double>> map;
        for(int i = 0; i < equations.size(); i++){
            const string& A = equations[i][0];
            const string& B = equations[i][1];
            const double k = values[i];
            map[A][B] = k;
            map[B][A] = 1.0/k;
        }
        vector<double> ans; //答案放置區
        //遍歷queries 
        for(auto a:queries){
            const string& X = a[0];
            const string& Y = a[1];
            if( !map.count(X) || !map.count(Y)){
                ans.push_back(-1.0);
                continue;
            }
            unordered_set<string> visited;  
            ans.push_back(dfs(X, Y, map, visited));
        }
        return ans;
    }
    double dfs(const string& A, const string& B, unordered_map<string, unordered_map<string, double>>& map, unordered_set<string>& visited){
        if(A==B) return 1.0;
        visited.insert(A);
        for(auto &pair:map[A]){
            const string& C = pair.first;
            if(visited.count(C)) continue;
            double d =  dfs(C, B, map, visited);
            if(d > 0) return d* map[A][C];
        }
        return -1.0;

    }
};

//花花版式 他的equation跟queries都是pair<string, string>
class Solution {
public:
    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
        //建立已知路徑
        unordered_map<string, unordered_map<string, double>> map;
        for(int i=0; i < equations.size(); i++){
            const string& a = equations[i].first;
            const string& b = equations[i].second;
            const double k = values[i];
            map[a][b] = k;
            map[b][a] = 1.0/k;
        }
        vector <double> ans;
        unordered_set <string> visited;
        for(auto& pair: queries){
            const string& x = pair.first;
            const string& y = pair.second;
            if(!map.count(x) || !map.count(y)) ans.push_back(-1.0);
            ans.push_back(dfs(map, visited, x, y ));
        }
        return ans;
    }
    double dfs(unordered_map<string, unordered_map<string, double>> map, unordered_set <string>& visited, const string& a,const string& b){
        if(a == b) return 1.0;
        visited.insert(a);
        for(auto& pair:map[a]){
            const string& c = pair.first;
            if(visited.count(c)) continue;
            double d = dfs(map, visited,c,b);
            if(d > 0) return d * map[a][c];
        }
        return -1.0;


    }
};
/*
解題思路
1.先把目前已知的路徑建立起來
2.遍歷queies的東東 看是要哪些字元之間
3.利用建立的路徑去尋找 如果是沒有在建立的檔案中出現的字元標示為找不到 找過的字元也要標記成visited過
4.一個一個去做dfs直到找到 如果沒找到一樣return 找不到
*/
// a [b,2.0]
// b [a, 0.5] [c, 3.0]
// c [b, 1/3]

//union find 難的跟鬼一樣 tc: o(e+q) sc:o(e)
class Solution2 {
public:
  vector<double> calcEquation(const vector<pair<string, string>>& equations, vector<double>& values, const vector<pair<string, string>>& queries) {
  // parents["A"] = {"B", 2.0} -> A = 2.0 * B
  // parents["B"] = {"C", 3.0} -> B = 3.0 * C
  unordered_map<string, pair<string, double>> parents;
 
  for (int i = 0; i < equations.size(); ++i) {
    const string& A = equations[i].first;
    const string& B = equations[i].second;
    const double k = values[i];
    // Neighter is in the forrest
    //建立既有的森林
    if (!parents.count(A) && !parents.count(B)) {
      parents[A] = {B, k};
      parents[B] = {B, 1.0};
    } else if (!parents.count(A)) {
      parents[A] = {B, k};
    } else if (!parents.count(B)) {
      parents[B] = {A, 1.0 / k};
    } else {
      auto& rA = find(A, parents);
      auto& rB = find(B, parents);      
      parents[rA.first] = {rB.first, k / rA.second * rB.second};
    }    
  }
 
 //看題目要求的pair是哪些
  vector<double> ans;
  for (const auto& pair : queries) {
    const string& X = pair.first;
    const string& Y = pair.second;
    if (!parents.count(X) || !parents.count(Y)) {
      ans.push_back(-1.0);
      continue;
    }
    auto& rX = find(X, parents); // {rX, X / rX}
    auto& rY = find(Y, parents); // {rY, Y / rY}
    if (rX.first != rY.first)
      ans.push_back(-1.0);//代表兩個不相連
    else // X / Y = (X / rX / (Y / rY))
      ans.push_back(rX.second / rY.second);
  }
  return ans;
}
private:
  pair<string, double>& find(const string& C, unordered_map<string, pair<string, double>>& parents) {
    if (C != parents[C].first) {
      const auto& p = find(parents[C].first, parents);
      parents[C].first = p.first;
      parents[C].second *= p.second;
    }
    return parents[C];
  }
};

//自己寫了一次用union find
class Solution {
public:
    vector<double> calcEquation(vector<vector<string>> equations, vector<double>& values, vector<vector<string>> queries) {
        //建立已知路徑
        unordered_map<string, pair<string, double>> parent;
        for(int i = 0; i < equations.size(); i++){
            const string& A = equations[i][0];
            const string& B = equations[i][1];
            const double k = values[i];
            if(!parent.count(A) && !parent.count(B)){
                parent[A] = {B,k};
                parent[B] = {B, 1.0};
            }
            else if(!parent.count(A) ){
                parent[A] = {B,k};
            }
            else if(!parent.count(B)){
                parent[B] = {A, 1.0/k};
            }
            else {
                auto& rA = find(A, parent);
                auto& rB = find(B, parent);
                parent[rA.first] ={rB.first, k/rA.second * rB.second};
            }
        }

        vector<double> ans;
        //開始測試queries裡面的東東
        for(const auto& pair: queries){
            const string& x = pair[0];
            const string& y = pair[1];
            if(!parent.count(x) || !parent.count(y)) {
                ans.push_back(-1.0);
                continue;
            }
            auto& ra = find(x, parent);
            auto& rb = find(y, parent);
            if(ra.first != rb.first) ans.push_back(-1.0);
            else ans.push_back(ra.second/rb.second);
        }
        return ans;
    }
    pair<string, double>&  find(const string&C, unordered_map<string, pair<string, double>>& parent){
        if(C != parent[C].first){
            const auto& p = find(parent[C].first, parent);
            parent[C].first = p.first;
            parent[C].second *= p.second;
        }
        return parent[C];
    }
};