#include<iostream>
#include<queue>
using namespace std;

struct INFO{
    int ry,rx,by,bx,cnt;
};
int dy[4] = {-1,1,0,0};
int dx[4] = {0,0,-1,1};
char map[11][11];
INFO start;

int bfs(){
    int ret = -1;
    int visited[10][10][10][10] = {0,};
    visited[start.ry][start.rx][start.by][start.bx] = 1;
    queue<INFO> q;
    q.push(start);
    while(!q.empty()){
        INFO cur = q.front(); q.pop();
        if(cur.cnt > 10){
            break;
        }
        if(map[cur.ry][cur.rx] == 'O' && map[cur.by][cur.bx] != 'O'){
            ret = cur.cnt;
            break;
        }
        for(int dir = 0; dir < 4; dir++){
            int next_ry = cur.ry;
            int next_rx = cur.rx;
            int next_by = cur.by;
            int next_bx = cur.bx;
            
            while(1){
                if(map[next_ry][next_rx] != '#' && map[next_ry][next_rx] != 'O'){
                    next_ry += dy[dir]; next_rx += dx[dir];
                }else{
                    if(map[next_ry][next_rx] == '#'){
                        next_ry -= dy[dir]; next_rx -= dx[dir];
                    }
                    break;
                }
            }
            
            while(1){
                if(map[next_by][next_bx] != '#' && map[next_by][next_bx] != 'O'){
                    next_by += dy[dir]; next_bx += dx[dir];
                }else{
                    if(map[next_by][next_bx] == '#'){
                        next_by -= dy[dir]; next_bx -= dx[dir];
                    }
                    break;
                }
            }
            
            if(next_ry == next_by && next_rx == next_bx){
                if(map[next_ry][next_rx] != 'O'){
                    int red_dist = abs(next_ry - cur.ry) + abs(next_rx - cur.rx);
                    int blue_dist = abs(next_by - cur.by) + abs(next_bx - cur.bx);
                    if(red_dist > blue_dist){
                        next_ry -= dy[dir]; next_rx -= dx[dir];
                    }else{
                        next_by -= dy[dir]; next_bx -= dx[dir];
                    }
                }
            }
            
            if(visited[next_ry][next_rx][next_by][next_bx] == 0){
                visited[next_ry][next_rx][next_by][next_bx] = 1;
                q.push({next_ry,next_rx,next_by,next_bx,cur.cnt+1});
            }
        }
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int n,m;
    cin>>n>>m;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin>>map[i][j];
            if(map[i][j] == 'R'){
                start.ry = i;
                start.rx = j;
            }
            if(map[i][j] == 'B'){
                start.by = i;
                start.bx = j;
            }
        }
    }
    start.cnt = 0;
    int ans = bfs();
    cout<<ans;
    return 0;
}
