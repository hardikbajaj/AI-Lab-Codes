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
        
        set<pair <int,pair<pair< vector<bool>,vector<string> > ,pair<int,int> >> >s;

        map< pair <int,pair<vector<bool> ,pair<int,int> >>  , bool >m ;
        vector<bool>vis(n,0);
        pair<int,int> p = {0,0}; // state 0, wt = 0
        vector<string> anss;
        vector<string>temp = {"0"};
        m[{0,{vis,p}}] = 1;
        s.insert({0,{{vis,temp},p}});
        
        auto prev = *s.begin();

        while(!s.empty()){
            
            auto state = *s.begin();
            int cost = state.first;
            auto sec = state.second;
            auto v = sec.first.first;
            auto path = sec.first.second;
            int node = sec.second.first;
            int wt = sec.second.second; 
            auto statte = mp(cost,mp(v,mp(node,wt)));
            
          
            
            s.erase(s.begin());
            if(m.find(statte) != m.end())continue;
            m[statte] = 1;
            if(node == 0 && ans ==-1){
                for(int i=1; i<n; i++){
                    if(v[i] == 1 && i == n-1){
                        ans = cost;
                        anss = path;
                    }
                    if(v[i] == 1)continue;
					else break;
                }
            }
            
            else if(ans != -1 && ans < cost){
                break;
            }
            else if(node == 0 && ans != -1 && ans == cost){
                 for(int i=1; i<n; i++){
                    if(v[i] == 1 && i == n-1){
                        anss = min(path, anss);
                    }
                    if(v[i] == 1)continue;
					else break;
                }
            }

            if(node == 0){
                wt = 0;
                for(int i=1; i<n; i++){
                    if(v[i] == 0 && (wt+ wts[i]) <= mxCost){
                        v[i] = 1;
                        
                         path.push_back(to_string(i));
                         auto stt = mp(cost+dist[node][i],mp(mp(v,path),mp(i,wt+wts[i])) );
                        
                        s.insert(stt);
                        
                        path.pop_back();
                        v[i] = 0;
                    }
                }
            }
            else{
                
                path.push_back("0");
                auto sttt  =  mp(cost+dist[node][0],mp(mp(v,path),mp(0 ,wt)) );
               
                path.pop_back();
                s.insert(sttt);
                
                for(int i=1; i<n; i++){ 
                    
                    if(i!= node && v[i] == 0 && (wt+ wts[i]) <= mxCost){

                        v[i] = 1;
                       path.push_back(to_string(i));
                        auto stt = mp(cost+dist[node][i],mp(mp(v,path),mp(i,wt+wts[i])) );
                        s.insert(stt);
                        path.pop_back();
                        v[i] = 0;
                    }
                }
            }

        }
    
        for(auto i: anss)cout<<i<<" ";
       
        cout<<"\n";
      
		
	}
}