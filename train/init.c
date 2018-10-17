#include "head.h"
#include "init.h"
#include "control.h"
#include "run.h"

extern int track_inf[16][10];
extern int track[16][10];
extern int signal[16][10];


void RenderCopy(SDL_Renderer* renderer,SDL_Texture* texture1,SDL_Texture* texture2,SDL_Texture* texture,SDL_Rect* pr,int i,int x,int y)
{
    if(track_inf[x][y]==0)
    {
        SDL_RenderCopy(renderer,texture1,NULL,pr);
        track_inf[x][y]=i;
        track[x][y]=1;
    }
    else if(track_inf[x][y]==i)
    {
        SDL_RenderCopy(renderer,texture2,NULL,pr);
        track[x][y]=2;
    }
    else
    {
        SDL_RenderCopy(renderer,texture,NULL,pr);
        track_inf[x][y]=7;
        track[x][y]=3;
    }

}

void TrackInsert(TrackList* t,SDL_Rect r)
{
    TrackList* p;
    p=(TrackList*)malloc(sizeof(TrackList));
    p->data=r;
    p->iStatus=0;
    p->next=t->next;
    t->next=p;
}

void TrainInsert(TrainList* t,FILE* fp,TrackList* q,int x,int y)
{
    TrainList* p;
    p=(TrainList*)malloc(sizeof(TrainList));
    p->data.pTrack=q;
    fscanf(fp,"%d %d %d %d",&p->data.iSpeed,&p->data.iStartTime,&p->data.iDirection,&p->data.iWaitingTime);
    p->data.iSpeed*=10;
    p->data.Position.x=x;
    p->data.Position.y=y;
    p->data.iUpdate=1;
    p->data.iControl=1;
    p->data.iPriority=5;
    p->next=t->next;
    t->next=p;
}

TrackList* JudgeTrack(TrackList* t,int x,int y)
{
    TrackList* p;
    p=t;
    while(p!=NULL)
    {
        if((x==p->data.x&&y>=p->data.y&&y<=(p->data.y+p->data.h))||
           (x==(p->data.x+p->data.w)&&y>=p->data.y&&y<=(p->data.y+p->data.h))||
           (y==p->data.y&&x>=p->data.x&&x<=(p->data.x+p->data.w))||
           (y==(p->data.y+p->data.h)&&x>=p->data.x&&x<=(p->data.x+p->data.w))
          )
            return p;

        p=p->next;
    }
    return NULL;
}

void RenderTrack(SDL_Renderer* renderer,SDL_Texture* texture[14])
{
    int i,j;
    SDL_Rect r;
    for(i=0;i<16;i++)
        for(j=0;j<10;j++)
        {
            r.x=i*60,r.y=j*60,r.w=60,r.h=60;
            if(track[i][j]==1)
            {
                if(track_inf[i][j]==1)
                    SDL_RenderCopy(renderer,texture[0],NULL,&r);
                else if(track_inf[i][j]==2)
                    SDL_RenderCopy(renderer,texture[1],NULL,&r);
                else if(track_inf[i][j]==3)
                    SDL_RenderCopy(renderer,texture[2],NULL,&r);
                else if(track_inf[i][j]==4)
                    SDL_RenderCopy(renderer,texture[3],NULL,&r);
                else if(track_inf[i][j]==5)
                    SDL_RenderCopy(renderer,texture[4],NULL,&r);
                else if(track_inf[i][j]==6)
                    SDL_RenderCopy(renderer,texture[5],NULL,&r);
            }
            else if(track[i][j]==2)
            {
                if(track_inf[i][j]==1)
                    SDL_RenderCopy(renderer,texture[6],NULL,&r);
                else if(track_inf[i][j]==2)
                    SDL_RenderCopy(renderer,texture[7],NULL,&r);
                else if(track_inf[i][j]==3)
                    SDL_RenderCopy(renderer,texture[9],NULL,&r);
                else if(track_inf[i][j]==4)
                    SDL_RenderCopy(renderer,texture[10],NULL,&r);
                else if(track_inf[i][j]==5)
                    SDL_RenderCopy(renderer,texture[11],NULL,&r);
                else if(track_inf[i][j]==6)
                    SDL_RenderCopy(renderer,texture[12],NULL,&r);
            }
            else if(track[i][j]==3)
                SDL_RenderCopy(renderer,texture[8],NULL,&r);
        }
}


void MatchInsert(MatchList* m,struct match x)
{
    MatchList* p;
    p=(MatchList*)malloc(sizeof(MatchList));
    p->data=x;
    p->next=m->next;
    m->next=p;
}

void MatchInit(MatchList* m,TrackList* t)
{
    int i,j,i0,j0,x,y;
    struct match p;
    for(i=0;i<16;i++)
        for(j=0;j<10;j++)
        {
            if(track[i][j]==2)
            {
                p.common.x=i*60,p.common.y=j*60;

                i0=i,j0=j;
                while(track[i0][j0]!=3)
                {
                    Explore(JudgeTrack(t,i0*60,j0*60),1,i0*60,j0*60,&x,&y);
                    i0=x/60,j0=y/60;
                }
                p.probe[0].x=i0*60,p.probe[0].y=j0*60;

                i0=i,j0=j;
                while(track[i0][j0]!=3)
                {
                    Explore(JudgeTrack(t,i0*60,j0*60),0,i0*60,j0*60,&x,&y);
                    i0=x/60,j0=y/60;
                }
                p.probe[1].x=i0*60,p.probe[1].y=j0*60;

                MatchInsert(m,p);

                p.common.x=p.probe[1].x,p.common.y=p.probe[1].y;
                MatchInsert(m,p);
                p.common.x=p.probe[0].x,p.common.y=p.probe[0].y;
                p.probe[0]=p.probe[1];
                MatchInsert(m,p);
            }
            else if(track[i][j]==3)
            {
                p.common.x=i*60,p.common.y=j*60;

                Explore(NULL,0,i*60,j*60,&x,&y);
                if(track[x/60][y/60]==3)
                {
                    p.probe[0].x=x,p.probe[0].y=y;
                    MatchInsert(m,p);
                }

                Explore(NULL,1,i*60,j*60,&x,&y);
                if(track[x/60][y/60]==3)
                {
                    p.probe[0].x=x,p.probe[0].y=y;
                    MatchInsert(m,p);
                }

                Explore(NULL,2,i*60,j*60,&x,&y);
                if(track[x/60][y/60]==3)
                {
                    p.probe[0].x=x,p.probe[0].y=y;
                    MatchInsert(m,p);
                }

                Explore(NULL,3,i*60,j*60,&x,&y);
                if(track[x/60][y/60]==3)
                {
                    p.probe[0].x=x,p.probe[0].y=y;
                    MatchInsert(m,p);
                }
            }
        }
}

void ConflictInsert(ConflictQueue* q,TrainList* x)
{
    ConflictQueue* p;
    p=(ConflictQueue*)malloc(sizeof(ConflictQueue));
    p->data=x;
    p->next=q->next;
    q->next=p;
}
