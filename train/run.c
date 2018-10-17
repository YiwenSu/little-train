#include "head.h"
#include "run.h"
#include "control.h"
#include "init.h"

extern int track_inf[16][10];
extern int track[16][10];
extern int signal[16][10];

extern int iStrategy;;
extern FILE* fp;


void Run(SDL_Renderer* renderer,TrainList* t,SDL_Texture* texture[15],MatchList* m)
{
    int Time=0,iPause=0;
    SDL_Rect r,button;
    TrainList* p;
    int x,y;
    int i,j;
    ConflictQueue* pConflict;
    pConflict=(ConflictQueue*)malloc(sizeof(ConflictQueue));
    pConflict->next=NULL;
    SDL_Point common;
    SDL_Event e;
    int quit=0;
    FILE* log=fopen("log.txt","w");

    Uint32 StartTime=SDL_GetTicks();
    while(!quit)
    {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,texture[15],NULL,NULL);
        RenderTrack(renderer,texture);

        if(iPause==0){

        button.x=70,button.y=625,button.w=50,button.h=50;
        SDL_RenderCopy(renderer,texture[20],NULL,&button);


        for(i=0;i<16;i++)
                for(j=0;j<12;j++)
                    signal[i][j]=0;

        p=t;
        while(p!=NULL)
        {
            if(p->data.Position.x%60==0&&p->data.Position.y%60==0)
                SetSignal(m,p->data.Position.x/60,p->data.Position.y/60);
            else if(p->data.Position.x%60==0&&p->data.Position.y%60!=0)
            {
                SetSignal(m,p->data.Position.x/60,p->data.Position.y/60);
                SetSignal(m,p->data.Position.x/60,p->data.Position.y/60+1);
            }
            else
            {
                SetSignal(m,p->data.Position.x/60,p->data.Position.y/60);
                SetSignal(m,p->data.Position.x/60+1,p->data.Position.y/60);
            }
            p=p->next;
        }

        p=t;
        while(p!=NULL)
        {
        if(p->data.Position.x%60==0&&p->data.Position.y%60==0)
        {
            Explore(p->data.pTrack,p->data.iDirection,p->data.Position.x,p->data.Position.y,&x,&y);
            if(track[p->data.Position.x/60][p->data.Position.y/60]==1&&track[x/60][y/60]==3)
            {
                if(signal[x/60][y/60]==0)
                {
                    signal[x/60][y/60]=2;
                    common.x=x,common.y=y;
                    Ergodic(m,common,2);
                    ConflictInsert(pConflict,p);
                }
                else if(signal[x/60][y/60]==2)
                {
                    ConflictInsert(pConflict,p);
                }
            }
        }
        p=p->next;
        }

        if(pConflict->next!=NULL)
            if(pConflict->next->next!=NULL)
                DealConflict(pConflict->next,iStrategy);

        ConflictFree(pConflict);


        for(i=0;i<16;i++)
                for(j=0;j<10;j++)
                    signal[i][j]=0;

        p=t;
        while(p!=NULL)
        {
            if(p->data.Position.x%60==0&&p->data.Position.y%60==0)
                SetSignal(m,p->data.Position.x/60,p->data.Position.y/60);
            else if(p->data.Position.x%60==0&&p->data.Position.y%60!=0)
            {
                SetSignal(m,p->data.Position.x/60,p->data.Position.y/60);
                SetSignal(m,p->data.Position.x/60,p->data.Position.y/60+1);
            }
            else
            {
                SetSignal(m,p->data.Position.x/60,p->data.Position.y/60);
                SetSignal(m,p->data.Position.x/60+1,p->data.Position.y/60);
            }
            p=p->next;
        }

        p=t;
        while(p!=NULL)
        {
            if(p->data.Position.x%60==0&&p->data.Position.y%60==0)
            {
                Explore(p->data.pTrack,p->data.iDirection,p->data.Position.x,p->data.Position.y,&x,&y);
                if(track[p->data.Position.x/60][p->data.Position.y/60]==1&&track[x/60][y/60]==3&&signal[x/60][y/60]==1)
                    p->data.iUpdate=0;
                if(track[p->data.Position.x/60][p->data.Position.y/60]==3&&p->data.iControl==1)
                {
                    p->data.iTimer=SDL_GetTicks();
                    p->data.iControl=0;
                }
                else if(track[p->data.Position.x/60][p->data.Position.y/60]==3&&p->data.iControl==0&&(SDL_GetTicks()-p->data.iTimer)>p->data.iWaitingTime*1000)
                    p->data.iControl=1;
            }

            if(Time%(1000/(p->data.iSpeed))<10&&(p->data.iUpdate==1)&&(p->data.iControl==1)&&(SDL_GetTicks()-StartTime)>(p->data.iStartTime*1000))
                UpdatePosition(p);

            p->data.iUpdate=1;

            r.x=p->data.Position.x,r.y=p->data.Position.y,r.w=60,r.h=60;
            SDL_RenderCopy(renderer,texture[13],NULL,&r);
            p=p->next;
        }
        }

        else
        {
        button.x=30,button.y=625,button.w=50,button.h=50;
        SDL_RenderCopy(renderer,texture[24],NULL,&button);
        button.x=100,button.y=625,button.w=50,button.h=50;
        SDL_RenderCopy(renderer,texture[18],NULL,&button);

        p=t;
        while(p!=NULL)
        {
            r.x=p->data.Position.x,r.y=p->data.Position.y,r.w=60,r.h=60;
            SDL_RenderCopy(renderer,texture[13],NULL,&r);
            p=p->next;
        }
        }

        fprintf(log,"Time:%d\t\tStrategy:%d\n",(SDL_GetTicks()-StartTime),iStrategy);
        p=t;
        i=1;
        while(p!=NULL)
        {
            fprintf(log,"Train %d:  Position:(%d,%d)\tDirection:",i,p->data.Position.x,p->data.Position.y);
            if(p->data.iDirection==0)
                fprintf(log,"clockwise\tStatus:");
            else
                fprintf(log,"counterclockwise\tStatus:");

            if(iPause==0&&p->data.iControl==1&&p->data.iUpdate==1&&(SDL_GetTicks()-StartTime)>(p->data.iStartTime*1000))
                fprintf(log,"run-");
            else
                fprintf(log,"pause-");

            if(track[p->data.Position.x/60][p->data.Position.y/60]==1)
                fprintf(log,"private track\n");
            else if(track[p->data.Position.x/60][p->data.Position.y/60]==2)
                fprintf(log,"common track\n");
            else if(track[p->data.Position.x/60][p->data.Position.y/60]==3)
                fprintf(log,"station\n");

            i++;
            p=p->next;
        }
        fprintf(log,"\n");

        SDL_RenderPresent(renderer);
        Time+=10;
        SDL_Delay(10);

        while(SDL_PollEvent(&e))
        {
            if(e.type==SDL_QUIT)
                quit=1;
            else if(e.type==SDL_MOUSEBUTTONDOWN)
            {
                SDL_GetMouseState(&x,&y);
                if(e.button.button==SDL_BUTTON_LEFT){
                if(y>600){
                if(iPause==0)
                {
                    if(x>=70&&x<=120&&y>=625&&y<=675)
                        iPause=1;
                }
                else
                {
                    if(x>=30&&x<=80&&y>=625&&y<=675)
                        iPause=0;
                    else if(x>=100&&x<=150&&y>=625&&y<=675)
                    {
                        system("strategy.exe");
                        fp=fopen("strategy.txt","r");
                        fscanf(fp,"%d",&iStrategy);
                        fclose(fp);
                    }
                }}
                else
                {
                    p=t;
                    while(p!=NULL)
                    {
                        if(x>=p->data.Position.x&&x<=(p->data.Position.x+60)&&y>=p->data.Position.y&&y<=(p->data.Position.y+60))
                            (p->data.iControl)*=(-1);
                        p=p->next;
                    }
                }}
                else if(e.button.button==SDL_BUTTON_RIGHT&&iPause==1)
                {
                    p=t;
                    while(p!=NULL)
                    {
                        if(x>=p->data.Position.x&&x<=(p->data.Position.x+60)&&y>=p->data.Position.y&&y<=(p->data.Position.y+60))
                        {
                            system("init.exe");
                            fp=fopen("config.txt","r");
                            fscanf(fp,"%d %d %d %d",&p->data.iSpeed,&p->data.iStartTime,&p->data.iDirection,&p->data.iWaitingTime);
                            p->data.iSpeed*=10;
                            fclose(fp);
                        }
                        p=p->next;
                    }
                }
            }
        }
    }
    fclose(log);
}

void UpdatePosition(TrainList* t)
{
    if(t->data.iDirection==0)
    {
        if(t->data.Position.y==t->data.pTrack->data.y&&t->data.Position.x<(t->data.pTrack->data.x+t->data.pTrack->data.w))
            t->data.Position.x++;
        else if(t->data.Position.x==(t->data.pTrack->data.x+t->data.pTrack->data.w)&&t->data.Position.y<(t->data.pTrack->data.y+t->data.pTrack->data.h))
            t->data.Position.y++;
        else if(t->data.Position.y==(t->data.pTrack->data.y+t->data.pTrack->data.h)&&t->data.Position.x>t->data.pTrack->data.x)
            t->data.Position.x--;
        else
            t->data.Position.y--;
    }
    else
    {
        if(t->data.Position.y==t->data.pTrack->data.y&&t->data.Position.x>t->data.pTrack->data.x)
            t->data.Position.x--;
        else if(t->data.Position.x==(t->data.pTrack->data.x+t->data.pTrack->data.w)&&t->data.Position.y>t->data.pTrack->data.y)
            t->data.Position.y--;
        else if(t->data.Position.y==(t->data.pTrack->data.y+t->data.pTrack->data.h)&&t->data.Position.x<(t->data.pTrack->data.x+t->data.pTrack->data.w))
            t->data.Position.x++;
        else
            t->data.Position.y++;
    }
}




void Explore(TrackList* t,int direction,int x0,int y0,int* x,int* y)
{
    if(t!=NULL){
    if(direction==0)
    {
        if(y0==t->data.y&&x0<(t->data.x+t->data.w))
            *x=x0+60,*y=y0;
        else if(x0==(t->data.x+t->data.w)&&y0<(t->data.y+t->data.h))
            *x=x0,*y=y0+60;
        else if(y0==(t->data.y+t->data.h)&&x0>t->data.x)
            *x=x0-60,*y=y0;
        else
            *x=x0,*y=y0-60;
    }
    else
    {
        if(y0==t->data.y&&x0>t->data.x)
            *x=x0-60,*y=y0;
        else if(x0==(t->data.x+t->data.w)&&y0>t->data.y)
            *x=x0,*y=y0-60;
        else if(y0==(t->data.y+t->data.h)&&x0<(t->data.x+t->data.w))
            *x=x0+60,*y=y0;
        else
            *x=x0,*y=y0+60;
    }}
    else
    {
        switch(direction)
        {
        case 0:
            *x=x0+60,*y=y0;
            break;
        case 1:
            *x=x0-60,*y=y0;
            break;
        case 2:
            *x=x0,*y=y0+60;
            break;
        case 3:
            *x=x0,*y=y0-60;
            break;
        }
    }
}

