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
        int f,s;cin>>f>>s;

		int n = f+s;
        vector<vector<int>>dist(n,vector<int>(n));
        for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            cin>>dist[i][j];
        }
        
        vector< pair<int,int> >wts(s);
        for(auto &i: wts){
            cin>>i.ff;cin>>i.se;
        }
        int mxCost;cin>>mxCost;
        
        int ans = -1;
        
        set<pair <int,pair<pair<vector<int>,pair<vector<int>,vector<string> > > ,pair<int,int> >> >st;
        vector<int>vis(n,0);
        vector<int>wf(f,0);
        vector<string>anss;
        vector<string>pat = {"0"};
        pair<int,int> p = {0,0}; // state 0, wt = 0
        
        map<pair <vector<int>, pair<int,int> >, bool> m;

        st.insert({0,{{vis,{wf,pat}},p}});

        while(!st.empty()){
            auto state = *st.begin();
            int cost = state.first;
            auto sec = state.second;
            auto v = sec.first.first;
            auto fwt = sec.first.second.first;
            auto path = sec.first.second.second;
            int node = sec.second.first;
            int wt = sec.second.second;
            st.erase(st.begin());

            auto tt = mp(v,mp(node,wt));
            if(m.find(tt) != m.end())continue;
            m[tt] = 1;

            if(ans != -1 && cost > ans)break;
            if(node<f){
                wt-= fwt[node];
                fwt[node] = 0;
                bool f1 = 0,f2 = 0;
                for(int i=f; i<n; i++){
                    if(v[i] == 1 && i == n-1){
                        f1 = 1;
                    }
                    else if(v[i] == 1)continue;
                    else break;
                }
                if(f1){
                    vector<int>temp(f,0);
                    if(fwt == temp)f2 = 1;
                }
                if(f1 && f2 && ans == -1){
                    ans=cost;
                    anss = path;
                }
                else if(f1 && f2){
                    anss = min(path, anss);
                }
            }
            
            
            
            for(int i=0; i<n; i++){
                
                   
            
                if(i<f){
                    if(fwt[i]){
                        
                        path.push_back(to_string(i));
                        auto stt = mp(cost+dist[node][i], mp(mp(v,mp(fwt,path)), mp(i,wt) ) );
                        path.pop_back();
                        st.insert(stt);
                    }
                }
                else{
                    if(i!= node && v[i] == 0 && (wt+wts[i-f].ff)<= mxCost ){
                        v[i] = 1;
                        fwt[ wts[i-f].se ] += wts[i-f].ff;
                        path.push_back(to_string(i));
                        auto stt = mp(cost+dist[node][i], mp(mp(v,mp(fwt,path)), mp(i,wt+wts[i-f].ff) ) );
                        st.insert(stt);
                        fwt[ wts[i-f].se ] -= wts[i-f].ff;
                        path.pop_back();
                        v[i] = 0;
                    }
                }
            }

        }
        for(auto i: anss)cout<<i<<" ";
        cout<<"\n";
        // ans is the soultion to Q3
        //cout<<ans<<endl;	
	}
}