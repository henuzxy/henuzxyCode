const int MAX = 2e5+10;
int a[MAX];
int lp[MAX<<2],rp[MAX<<2],mi[MAX<<2];
int lMax[MAX],rMax[MAX];
void pushup(int i){
    mi[i] = min(mi[i<<1],mi[i<<1|1]);
}
void build(int l,int r,int i){
    lp[i] = l;
    rp[i] = r;
    if(l == r){
        mi[i] = a[l];
        return;
    }
    int mid = (l+r)>>1;
    build(l,mid,i<<1);
    build(mid+1,r,i<<1|1);
    pushup(i);
}
int query(int l,int r,int i){
    if(l <= lp[i] && rp[i] <= r){
        return mi[i];
    }
    int mid = (lp[i]+rp[i]) >> 1;//左区间的右边界
    int res = INT_MAX;
    if(l <= mid){
        res = min(res,query(l,r,i<<1));
    }
    if(mid < r){
        res = min(res,query(l,r,i<<1|1));
    }
    return res;
}