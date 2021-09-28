// Written by Hardik Bajaj, IIT2019039, IIIT Allahabad


#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define pb push_back
#define ff first
#define se second
#define mp make_pair
#define M 1000000007

int main()
{

	ios::sync_with_stdio(0);
    cin.tie(0);

	#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	freopen("output.txt", "w", stdout);
	#endif

	int t;cin>>t;
	while(t--){
		int n;cin>>n;
        vector<vector<int>>dist(n,vector<int>(n));
        for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            cin>>dist[i][j];
        }
        vector<int>wts(n,-1);
        for(int i=1; i<n; i++){
            cin>>wts[i];
        }
        int mxCost;cin>>mxCost;
        
        int ans = -1;
        
        set<pair <int,pair<vector<int> ,pair<int,int> >> >s;
        vector<int>vis(n,0);
        pair<int,int> p = {0,0}; // state 0, wt = 0
        
        s.insert({0,{vis,p}});

        while(!s.empty()){
            auto state = *s.begin();
            int cost = state.first;
            auto sec = state.second;
            auto v = sec.first;
            int node = sec.second.first;
            int wt = sec.second.second;
            s.erase(s.begin());
            if(node == 0){
                for(int i=1; i<n; i++){
                    if(v[i] == 1 && i == n-1){
                        ans = cost;
                    }
                    if(v[i] == 1)continue;
					else break;
                }
            }
            
            if(ans != -1)break;

            if(node == 0){
                wt = 0;
                for(int i=1; i<n; i++){
                    if(v[i] == 0 && (wt+ wts[i]) <= mxCost){
                        v[i] = 1;
                        s.insert({cost+dist[node][i],{v,{i,wt+wts[i]}} });
                        v[i] = 0;
                    }
                }
            }
            else{
                
                 s.insert({cost+dist[node][0],{v,{0 ,wt}} });
                for(int i=1; i<n; i++){
                    
                       
                    
                    if(i!= node && v[i] == 0 && (wt+ wts[i]) <= mxCost){

                        if(i != 0) v[i] = 1;
                        s.insert({cost+dist[node][i],{v,{i,wt+wts[i]}} });
                        v[i] = 0;
                    }
                }
            }

        }
        cout<<ans<<endl;
		
	}
}