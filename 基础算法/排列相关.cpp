//N个数的全排列
void dfs(int start,int& N){
    if(start == N+1){
        show(G);
        return;
    }
    for(int i=1;i<=N;i++){
        if(!used[i]){
            G.push_back(i);
            used[i] = true;
            dfs(start+1,N);
            G.pop_back();
            used[i] = false;
        }
    }
}


//把N个东西分给M个人的，全排列
//G size is M,用来存储每个人分配的和
//参考例题： https://leetcode.com/problems/fair-distribution-of-cookies/
void dfs(int start,vector<int> &nums,vector<int> &G,int &N,int &M){
    if(start == N+1){
        //res 
        return;
    }
    for(int i=1;i<=M;i++){
        G[i] += nums[i];
        dfs(start+1,nums,G,N,M);
        G[i] -= nums[i];
    }
}

