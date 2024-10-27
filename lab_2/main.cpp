#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
int MAX = 1e8;


int main(){
    int n;
    cin >> n;
    vector<long long> dp(n+1,MAX);
    vector<int> pos(n+1,0);
    dp[n] = n;
    for (int i = n; i>0; i--)
    {
        if (dp[i-1]>dp[i]+i-1)
        {
            dp[i-1] = dp[i]+i-1;
            pos[i-1] = i;
        }if (i%3==0 and dp[i/3]>dp[i]+i/3)
        {
            dp[i/3] = dp[i]+i/3;
            pos[i/3] = i;
        }
        if(i%2==0 and dp[i/2]>dp[i]+i/2){
            dp[i/2] = dp[i]+i/2;
            pos[i/2] = i;
        }
        
    }
    cout << dp[1]-1 << endl;
    string res;
    int i = 1;    
    while(i!=n){
        int new_i = pos[i];
        //cout << new_i << " ";
        if (new_i == i+1){
            res += "1-";
        }else if(new_i == i*2){
            res += "2/";
        }else if(new_i == i*3){
            res += "3/";
        }
        res += " ";
        i = new_i;
    } 
    res = res.substr(0,res.size()-1);
    reverse(res.begin(), res.end());
    cout << res << endl;

    return 0;
}