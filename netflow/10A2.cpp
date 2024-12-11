#include<bits/stdc++.h>
using namespace std;
int N,M,S,E,C,sum, tot=1,head[20020],now[20020];
struct A{
    int to,nxt,w;
}e[20020];
void add(int S,int E,int C){
    e[++tot].to=E;
    e[tot].w=C;
    e[tot].nxt=head[S];
    head[S]=tot;
}
int dep[20020];
int bfs(){
    memset(dep,-1,sizeof(dep));
    dep[1]=1;
    queue<int> q;
    q.push(1);
    now[1]=head[1];
    while(!q.empty()){
        int u=q.front();
        q.pop();
//      cout<<"u:"<<u<<endl;
        for(int i=head[u];i!=-1;i=e[i].nxt){
            int v=e[i].to;
            if(e[i].w &&dep[v]==-1){
                q.push(v);
                now[v]=head[v];
                dep[v]=dep[u]+1;
                if(v==M) return 1;
            }
        }
    }
    return 0;
}
int dfs(int u,int in){
//  cout<<"u:"<<u<<" in:"<<in<<endl;
    if(u==M) return in;
    int out=0;
    for(int i=now[u];i &&in;i=e[i].nxt){
        now[u]=i;
        int v=e[i].to;
        if(e[i].w &&dep[v]==dep[u]+1){
            int maxx=dfs(v,min(in,e[i].w));
            if(!maxx) dep[v]=-1;
            e[i].w-=maxx;
            e[i^1].w+=maxx;
            in-=maxx;
            out+=maxx;
        }
    }
    return out;
}
int main(){
    memset(head,-1,sizeof(head));
    memset(now,-1,sizeof(now));
    scanf("%d %d",&M,&N);
    int source, sink;
    scanf("%d %d",&source, &sink);
    while(N--){
        scanf("%d %d %d",&S,&E,&C);
        add(S,E,C);
        add(E,S,0);
    }
    while(bfs()){
        sum+=dfs(1,1e8);
    }
    cout<<sum;
}
