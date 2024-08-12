/*
    |kmp算法|
    |字符串匹配|
    |17/1/21ztx|
*/

void getnext(char str[maxn], int nextt[maxn]) {
    int j = 0, k = -1;
    nextt[0] = -1;
    while (j < m) {
        if (k == -1 || str[j] == str[k]) {
            j++;
            k++;
            nextt[j] = k;
        }
        else
            k = nextt[k];
    }
}

void kmp(int a[maxn], int b[maxn]) {    
    int nextt[maxm];    
    int i = 0, j = 0;    
    getnext(b, nextt);    
    while (i < n) {    
        if (j == -1 || a[i] == b[j]) { // 母串不动，子串移动    
            j++;    
            i++;    
        }    
        else {    
            // i不需要回溯了    
            // i = i - j + 1;    
            j = nextt[j];    
        }    
        if (j == m) {    
            printf("%d\n", i - m + 1); // 母串的位置减去子串的长度+1    
            return;    
        }    
    }    
    printf("-1\n");
}    

/*
    KMP扩展
*/

/*
#include<iostream>    
#include<cstring>    

using namespace std;

const int MM=100005;    

int next[MM],extand[MM];    
char S[MM],T[MM];    

void GetNext(const char *T) {    
    int len = strlen(T),a = 0;    
    next[0] = len;    
    while(a < len - 1 && T[a] == T[a + 1]) a++;    
    next[1] = a;    
    a = 1;    
    for(int k = 2; k < len; k ++) {    
        int p = a + next[a] - 1,L = next[k - a];    
        if( (k - 1) + L >= p) {    
            int j = (p - k + 1) > 0 ? (p - k + 1) : 0;    
            while(k + j < len && T[k + j] == T[j]) j++;    
            next[k] = j;    
            a = k;    
        }else next[k] = L;    
    }    
}    
void GetExtand(const char *S,const char *T) {    
    GetNext(T);    
    int slen = strlen(S),tlen = strlen(T),a = 0;    
    int MinLen = slen < tlen ? slen : tlen;    
    while(a < MinLen && S[a] == T[a]) a++;    
    extand[0] = a;     
    a = 0;    
    for(int k = 1; k < slen; k ++) {    
        int p = a + extand[a] - 1, L = next[k - a];    
        if( (k - 1) + L >= p) {    
            int j = (p - k + 1) > 0 ? (p - k + 1) : 0;    
            while(k + j < slen && j < tlen && S[k + j] == T[j]) j ++;    
            extand[k] = j;    
            a = k;    
        } else    
            extand[k] = L;    
    }    
}    
void show(const int *s,int len){    
    for(int i = 0; i < len; i ++)    
            cout << s[i] << ' ';    
    cout << endl;    
}    

int main() {    
    while(cin >> S >> T) {    
        GetExtand(S,T);    
        show(next,strlen(T));    
        show(extand,strlen(S));    
    }    
    return 0;    
}   
*/