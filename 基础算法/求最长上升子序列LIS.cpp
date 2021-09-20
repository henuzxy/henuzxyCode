using namespace std;
const int INF = 0x3f3f3f3f;
const int MAX = 1010;
int a[MAX],dp[MAX],N;
int LIS(){
    //dp[i] 表示构成i+1长度的末尾最小值，因为末尾值越小越有优势
    fill(dp,dp+N,INF);
    for(int i=0;iN;++i){
        lower_bound(dp,dp+N,a[i]) = a[i];
    }
    return lower_bound(dp,dp+N,INF)-dp;
}
