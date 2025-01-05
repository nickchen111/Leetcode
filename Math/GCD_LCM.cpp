int gcd(int a, int b){
    while(b > 0){
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int gcd(int a, int b) {
    if(b == 0) return a;
    return gcd(b, a % b);
}



int LCM(int a, int b){
    return a*b/GCD(a,b);
}
