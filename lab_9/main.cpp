#include <iostream>
#include <vector>
#include <limits>
#include <queue>

using ll = long long;

static const ll INF = std::numeric_limits<ll>::max();

bool bfs(std::vector<int>& parent,const std::vector<std::vector<int>>& graph,const std::vector<std::vector<ll>>& cap,const int s,const int e){
    std::fill(parent.begin(),parent.end(),-1);
    std::queue<int> q;
    q.push(s);
    parent[s] = s;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int node:graph[u]){
            if(cap[u][node]>0 and parent[node]==-1){
                parent[node] = u;
                if(node==e){
                    return true;
                }
                q.push(node);
            }
        }
    }
    return false;
}

ll ford_falkerson(const std::vector<std::vector<int>>& graph,std::vector<std::vector<ll>>& cap,const int s,const int e){
    std::vector<int> parent(cap.size());
    ll ans = 0;
    while(bfs(parent,graph,cap,s,e)){
        ll min_flow = INF;
        int cur_node = e;
        while(cur_node!=s){
            int next_node = parent[cur_node];
            min_flow = std::min(min_flow,cap[next_node][cur_node]);
            cur_node = next_node;
        }
        cur_node = e;
        while (cur_node!=s)
        {
            int next_node = parent[cur_node];
            cap[next_node][cur_node] -= min_flow;
            cap[cur_node][next_node] += min_flow;
            cur_node = next_node;
        }
        ans += min_flow;
    }
    return ans;
}

int main(){
    int n,m;
    std::cin >> n >> m;
    std::vector<std::vector<ll>> cap(n, std::vector<ll>(n,0));
    std::vector<std::vector<int>> graph(n);
    for(int i = 0;i<m;i++){
        int f,s;
        ll c;
        std::cin >> f >> s >> c;
        f--;
        s--;
        cap[f][s] += c;
        graph[f].push_back(s);
        graph[s].push_back(f);
    }
    ll ans = ford_falkerson(graph,cap,0,n-1);
    std::cout << ans << std::endl;
    return 0;
}