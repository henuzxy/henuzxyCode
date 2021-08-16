void preKmp(char *src, int m, int *rule){
  int i=0,j=-1;
  rule[0]=j;
  while(i<m){
      while(j!=-1 && src[j] != src[i])
          j=rule[j];
      i++,j++;
      if(j>=m)
          rule[i]=rule[j-1];
      else
          rule[i]=j;
  }
}
int kmp(char *src, int m, char *dest, int n)//’‚¿Ôdest «ƒ∏¥Æ
{
    int recount=0;
    int rule[MAX];
    preKmp(src,m,rule);
    int i=0, j=0;
    while(i<n){
        while(j!=-1 && src[j] != dest[i]){
            j = rule[j];
        }
        i++,j++;
        if(j==m){
            recount++;
            j=rule[j];
        }
    }
    return recount;
}