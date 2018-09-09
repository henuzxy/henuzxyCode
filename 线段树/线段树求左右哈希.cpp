#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
const ull B = 1e8+7;
const int MAX = 1e5+10;
#define lson (k*2)
#define rson (k*2+1)
char str[MAX];
ull Pow[MAX];
class Node{
public:
    int l,r;
    ull Lv,Rv;
    Node();
    int len(){
        return r-l+1;
    }
    int mid(){
        return (l+r)/2;
    }
};
Node tree[MAX*4];
void init(){
    Pow[0] = 1;
    for(int i=1;i<=(int)1e5;++i)
        Pow[i] = Pow[i-1]*B;
}
void PushUp(int k){
    int L = tree[lson].len();
    int R = tree[rson].len();
    tree[k].Lv = tree[lson].Lv + tree[rson].Lv*Pow[L];
    tree[k].Rv = tree[lson].Rv*Pow[R] + tree[rson].Rv;
}
void Build(int L,int R,int k){
    tree[k].l = L;
    tree[k].r = R;
    if(L == R){
        tree[k].Lv = (ull)str[L];
        tree[k].Rv = (ull)str[L];
        return;
    }
    int mid = (L+R)/2;
    Build(L,mid,lson);
    Build(mid+1,R,rson);
    PushUp(k);
}
void Update(int p,int k){
    if(tree[k].l == tree[k].r && tree[k].l == p){
        tree[k].Lv = (ull)str[p];
        tree[k].Rv = (ull)str[p];
        return;
    }
    int mid = tree[k].mid();
    if(p <= mid)    Update(p,lson);
    else    Update(p,rson);
    PushUp(k);
}
//这里要每个递归，都知道当前已经找到的区间值，所以是引用，或者指针。
ull QueryL(int L,int R,int k,int &len){
    if(L <= tree[k].l && tree[k].r <= R){
        ull temp = tree[k].Lv*Pow[len];
        len += tree[k].len();
        return temp;
    }
    int mid = tree[k].mid();
    ull res = 0;
    if(L <= mid)    res += QueryL(L,R,lson,len);
    if(R > mid)     res += QueryL(L,R,rson,len);
    return res;
}

ull QueryR(int L,int R,int k,int &len){
    if(L <= tree[k].l && tree[k].r <= R){
        ull temp = tree[k].Rv*Pow[len];
        len += tree[k].len();
        return temp;
    }
    int mid = tree[k].mid();
    ull res = 0;
    if(R > mid) res += QueryR(L,R,rson,len);
    if(L <= mid)    res += QueryR(L,R,lson,len);
    return res;
}
int main(void){
    init();
    scanf("%s",str+1);
    int N = strlen(str+1);
    Build(1,N,1);
    int Q;
    scanf("%d",&Q);
    char op[20];
    while(Q--){
        scanf("%s",op);
        if(strcmp(op,"palindrome?") == 0){
            int l,r;
            scanf("%d%d",&l,&r);
            int len = 0;
            ull Lv = QueryL(l,r,1,len);
            len = 0;
            ull Rv = QueryR(l,r,1,len);
            if(Lv == Rv)
                printf("Yes\n");
            else
                printf("No\n");
        }
        else{
            int op;
            char ch;
            scanf("%d %c",&op,&ch);
            str[op] = ch;
            Update(op,1);
        }
    }
    return 0;
}
Node::Node(){
    l = r = 0;
    Lv = Rv = 0;
}