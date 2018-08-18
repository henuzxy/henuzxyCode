#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdio>
#include<algorithm>
#include<set>
using namespace std;
const int MAX = 10010;
const double eps = 1e-6;
#define lson (k*2)
#define rson (k*2+1)
//#define LOCAL
class Node{
public:
    int l,r;
    int s;
    int num;
    double sum;
    int mid(){
        return (l+r)/2;
    }
};
Node tree[MAX*4];
class LineX{
public:
    double lx,rx,y;
    int s;
    LineX();
    LineX(double _lx,double _rx,double _y,int _s);
};
LineX lineX[MAX];
class LineY{
public:
    double ly,ry,x;
    int s;
    LineY();
    LineY(double _ly,double _ry,double _x,int _s);
};
LineY lineY[MAX];
double posX[MAX],posY[MAX];
bool operator < (LineX A,LineX B){
    if(abs(A.y-B.y) < eps)
        return A.s > B.s;
    return B.y-A.y > eps;
}
bool operator < (LineY A,LineY B){
    if(abs(A.x-B.x) < eps)
        return A.s > B.s;
    return B.x-A.x > eps;
}
void Build(int L,int R,int k){
    tree[k].l = L;tree[k].r = R;
    tree[k].sum = 0;tree[k].num = 0;
    tree[k].s = 0;
    if(L + 1 == R)  return;
    int mid = (L+R)/2;
    Build(L,mid,lson);
    Build(mid,R,rson);
}
void PushUp(int k,int p){
    if(tree[k].s > 0){
        if(p == 1)
            tree[k].sum = posX[tree[k].r]-posX[tree[k].l];
        else
            tree[k].sum = posY[tree[k].r]-posY[tree[k].l];
        tree[k].num = 1;
    }
    else if(tree[k].l + 1 == tree[k].r){
        tree[k].sum = 0;
        tree[k].num = 0;
    }
    else{
        tree[k].sum = tree[lson].sum + tree[rson].sum;
        tree[k].num = tree[lson].num + tree[rson].num;
    }
}
void Insert_Line(int L,int R,int k,int s,int p){
    if(L <= tree[k].l && tree[k].r <= R){
        tree[k].s += s;
        PushUp(k,p);
        return;
    }
    int mid = tree[k].mid();
    if(L < mid) Insert_Line(L,R,lson,s,p);
    if(R > mid) Insert_Line(L,R,rson,s,p);
    PushUp(k,p);
}
int main(void){
    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
      //  freopen("out.txt","w",stdout);
    #endif
    int N;
    scanf("%d",&N);
    double x1,y1,x2,y2;
    for(int i=1;i<=N;++i){
        scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
        lineX[i] = LineX(x1,x2,y1,1);
        lineY[i] = LineY(y1,y2,x1,1);
        posX[i] = x1;posY[i] = y1;
        lineX[N+i] = LineX(x1,x2,y2,-1);
        lineY[N+i] = LineY(y1,y2,x2,-1);
        posX[N+i] = x2;posY[N+i] = y2;
    }
    sort(posX+1,posX+2*N+1);
    sort(posY+1,posY+2*N+1);
    sort(lineX+1,lineX+2*N+1);
    sort(lineY+1,lineY+2*N+1);
    Build(1,2*N,1);
    double last = 0;
    double res = 0;
    for(int i=1;i<=2*N;++i){
        //cout << lineX[i].lx << " " << lineX[i].rx << endl;
        int lx = lower_bound(posX+1,posX+2*N+1,lineX[i].lx)-posX;
        int rx = lower_bound(posX+1,posX+2*N+1,lineX[i].rx)-posX;
        //cout << lx << " " << rx << endl;
        Insert_Line(lx,rx,1,lineX[i].s,1);
        res += abs(tree[1].sum-last);
        last = tree[1].sum;
    }
    for(int i=1;i<=2*N;++i){
        int ly = lower_bound(posY+1,posY+2*N+1,lineY[i].ly)-posY;
        int ry = lower_bound(posY+1,posY+2*N+1,lineY[i].ry)-posY;
        Insert_Line(ly,ry,1,lineY[i].s,0);
        res += abs(tree[1].sum-last);
        last = tree[1].sum;
    }
    cout << res << endl;
    return 0;
}
LineX::LineX(){
    lx = rx = y = 0;
    s = 0;
}
LineX::LineX(double _lx,double _rx,double _y,int _s){
    lx = _lx;rx = _rx;y = _y;
    s = _s;
}
LineY::LineY(){
    ly = ry = x = 0;
    s = 0;
}
LineY::LineY(double _ly,double _ry,double _x,int _s){
    ly = _ly;ry = _ry;x = _x;
    s = _s;
}
