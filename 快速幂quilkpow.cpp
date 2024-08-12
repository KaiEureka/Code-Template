typedef long long LL;   //  视数据大小的情况而定

LL powerMod(LL x, LL n, LL m)
{
    LL res = 1;
    while (n > 0){
        if  (n & 1) //  判断是否为奇数，若是则true
            res = (res * x) % m;
        x = (x * x) % m;
        n >>= 1;    //  相当于n /= 2;
    }
    return res;
}
