/*
逆元(Inverse element)就是在mod意义下，不能直接除以一个数，而要乘以它的逆元。
比如a ∗ b ≡ 1 ( m o d p ) a*b≡1 (mod p)a∗b≡1(modp)，那么a，b互为模n意义下的逆元
根据费马小定理：若p为素数，则有a ^(p − 1) ≡ 1 ( m o d p ) 故a * (a^(p − 2)) ≡ 1 ( m o d p ) 
因此，pow(a, p - 2)就是a在mod p意义下的逆元啦。
当然pow要用快速幂
*/

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

LL getInv(LL a,LL mod)
{
	return qkpow(a,mod-2,mod);
}
