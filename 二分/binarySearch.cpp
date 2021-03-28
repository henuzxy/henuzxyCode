#include <bits/stdc++.h>

using namespace std;
int lowerBound(vector<int> &vec,int target){
    int l = 0,r = (int)vec.size();
    while(l < r){
        int m = l + (r-l)/2;
        if(vec[m] < target){
            l = m+1;
        }else{
            r = m;
        }
    }
    return l;
}
int upperBound(vector<int> &vec,int target){
    int l = 0,r = (int)vec.size();
    while(l < r){
        int m = l + (r-l)/2;
        if(vec[m] <= target){
            l = m+1;
        }else{
            r = m;
        }
    }
    return l;
}

int main(void){
    vector<int> vec{1,2,3,4,4,4,4,5,5,6};
    cout << lowerBound(vec,4) << endl;
    cout << upperBound(vec,4) << endl;
    return 0;
}