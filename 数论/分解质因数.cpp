vector<ll> fenjie(ll x){
    vector<ll> vec;
    ll i = 2;
    while(i*i <= x){
        while(x % i == 0){
            vec.push_back(i);
            x /= i;
        }
        i++;
    }
    if(x > 1)   vec.push_back(x);
    return vec;
}