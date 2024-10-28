// 原汁原味Z function模板
auto cal_z = [&](string& t) -> vector<int> {
      vector<int> z(n);
      z[0] = n;
      for(int i = 1, c = 1, r = 1, len; i < n; i++) {
          len = r > i ? min(z[i-c], r-i) : 0;
          while(i + len < n && t[len] == t[i+len]) {
              len ++;
          }
          if(i + len > r) {
              r = i + len;
              c = i;
          }
          z[i] = len;
      }

      return z;
  };
   
 // e 陣列
auto cal_e = [&](string& s, vector<int>& z, string& t) -> vector<int> {
      vector<int> e(m);
      for(int i = 0, c = 0, r = 0, len; i < m; i++) {
          len = r > i ? min(z[i-c], r-i) : 0;
          while(i + len < m && t[len] == s[i + len]) {
              len ++;
          }
          if(i + len > r) {
              r = i + len;
              c = i;
          }
          e[i] = len;
      } 
      return e;
  };
