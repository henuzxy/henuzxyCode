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
void quickSort(vector<int> &vec,int l,int r){
    if(l >= r){
        return;
    }
    int m = partition(vec,l,r);
    quickSort(vec,l,m-1);
    quickSort(vec,m+1,r);
}

int main(void){
    vector<int> vec{5,4,3,2,1};
    quickSort(vec,0,vec.size()-1);
    for(int i=0;i<vec.size();i++){
        cout << vec[i] << " ";
    }
    cout << endl;

    return 0;
}