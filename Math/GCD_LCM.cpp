int gcd(int a, int b){
    while(b > 0){
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}


int LCM(int a, int b){
    return a*b/GCD(a,b);
}
