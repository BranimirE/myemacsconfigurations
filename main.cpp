#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define MAX 100000
#define MOD 1000000009LL
typedef long long int Number;
Number v[MAX + 5];
int c[100];
int n;
Number bags;
Number mod(Number a, Number b){
  Number ans = a % b;
  if(ans < 0)
    ans += b;
  return ans;
}
Number dp[101][101];
Number f[MAX + 5];
Number pow(Number b, Number e){
  if(e == 0) return 1LL;
  Number ans = pow(b, (e >> 1LL));
  ans = ans * ans;
  if(ans >= MOD) ans %= MOD;
  if(e & 1){ 
    ans = ans * b;
    if(ans >= MOD) ans %= MOD;
  }
  return ans;
}
Number C(Number n, Number k){
  return (f[n] * pow((f[k] * f[n-k]) % MOD , MOD - 2)) % MOD;
}
Number solve(int pos, int obj){
  if(pos == bags) 
    return Number(obj == 0);
  Number &ans = dp[pos][obj];
  if(ans != -1) 
    return ans;
  //cout << "calculando pos = " << pos << " obj = " << obj << endl;
  ans = solve(pos + 1, obj);
  for(int cant = 1; cant <= c[pos]; cant++)
    ans = (ans + (solve(pos + 1, mod(obj - pos * cant, bags)) * C(c[pos], cant))) % MOD;
  return ans;
}
int main(){
  int t;
  int q;
  f[0] = 1;
  for(int i = 1; i <= MAX; i++)
    f[i] = (i * f[i-1]) % MOD;
  scanf("%d", &t);
  while(t--){
    scanf("%d%d", &n, &q);
    for(int i = 0; i < n; i++)
      scanf("%lld", &v[i]);
    while(q--){
      scanf("%lld", &bags);
      memset(c, 0, sizeof(c));
      //cout << "lee query" << endl;
      for(int i = 0; i < n; i++)
        c[mod(v[i], bags)]++;
      //cout << "saca acumulada" << endl;
      memset(dp, -1, sizeof(dp));
      //cout << "llamando solve(0, 0)" << endl;
      printf("%lld\n", solve(0, 0));
    }
  }
  return 0;
}
