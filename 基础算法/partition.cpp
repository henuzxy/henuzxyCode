#include <bits/stdc++.h>

using namespace std;
int partition(vector<int> &vec,int l,int r){
    int i = l;
    int j = r;
    int temp = vec[l];
    while(i < j){
        while(vec[j] >= temp && i < j){
            j -= 1;
        }
        vec[i] = vec[j];
        while(vec[i] < temp && i < j){
            i += 1;
        }
        vec[j] = vec[i];
    }
    vec[i] = temp;
    return i;
}