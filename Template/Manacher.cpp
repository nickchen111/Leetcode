for(int i = 0, c = 0, r = 0, len; i < 2*n+1; i++) {
    len = r > i ? min(p[2*c-i], r-i) : 1;
    while(i + len < 2*n+1 && i - len >= 0 && t[i+len] == t[i-len]) {
        len ++;
    }
    if(i + len > r) {
        r = i + len;
        c = i;
    }
    p[i] = len;
}
