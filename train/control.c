#include "head.h"
#include "control.h"

extern int track_inf[16][10];
extern int track[16][10];
extern int signal[16][10];


MatchList* MatchSearch(MatchList* m,SDL_Point common,SDL_Point probe[])
{
    MatchList* p;
    p=m;
    while(p!=NULL&&!(common.x==p->data.common.x&&common.y==p->data.common.y))
        p=p->next;

    if(p!=NULL)
    {
        probe[0]=p->data.probe[0];
        probe[1]=p->data.probe[1];
    }

    return p;
}


void SetSignal(MatchList* m,int i,int j)
{
    SDL_Point common,probe[2];

    if(track[i][j]==3)
    {
        signal[i][j]=1;

        common.x=i*60,common.y=j*60;
        Ergodic(m,common,1);
    }
    else if(track[i][j]==2)
    {
        common.x=i*60,common.y=j*60;
        MatchSearch(m,common,probe);
        signal[probe[0].x/60][probe[0].y/60]=1;
        signal[probe[1].x/60][probe[1].y/60]=1;
        Ergodic(m,probe[0],1);
        Ergodic(m,probe[1],1);
    }
}

void Ergodic(MatchList* m,SDL_Point common,int i)
{
    MatchList* p;
    p=m;
    SDL_Point temp;
    temp=common;

    while(p!=NULL)
    {
        if(common.x==p->data.common.x&&common.y==p->data.common.y&&signal[p->data.probe[0].x/60][p->data.probe[0].y/60]!=i)
        {
            signal[p->data.probe[0].x/60][p->data.probe[0].y/60]=i;
            temp.x=p->data.probe[0].x,temp.y=p->data.probe[0].y;
            Ergodic(m,temp,i);
        }
        p=p->next;
    }
}



void ConflictFree(ConflictQueue* q)
{
    ConflictQueue *p;
    p=q;
    while(p->next!=NULL)
    {   q=p->next;
        p->next=p->next->next;
        free(q);
    }
    q=p;
}

void DealConflict(ConflictQueue* q,int i)
{
    ConflictQueue *p,*most;
    int quit=0,x,y;
    SDL_Event e;

    switch(i)
    {
    case 1:
        most=GetFirst(q);
        most->data->data.iPriority--;
        if(most->data->data.iPriority==0)
            most->data->data.iPriority+=5;
        p=q;
        while(p!=NULL)
        {
            if(p!=most)
                p->data->data.iUpdate=0;
            p=p->next;
        }

        break;
    case 2:
        most=GetFast(q);

        p=q;
        while(p!=NULL)
        {
            if(p!=most)
                p->data->data.iUpdate=0;
            p=p->next;
        }
        break;
    case 3:;
        while(!quit)
        {
            while(SDL_PollEvent(&e))
            {
                if(e.type==SDL_MOUSEBUTTONDOWN)
                    if(e.button.button==SDL_BUTTON_LEFT)
                    {
                        SDL_GetMouseState(&x,&y);
                        p=q;
                        while(p!=NULL&&!quit)
                        {
                        if(x>=p->data->data.Position.x&&x<=(p->data->data.Position.x+60)&&y>=p->data->data.Position.y&&y<=(p->data->data.Position.y+60))
                        {
                            most=p;
                            quit=1;
                        }
                        p=p->next;
                        }

                        if(quit)
                        {
                            p=q;
                            while(p!=NULL)
                            {
                                if(p!=most)
                                    p->data->data.iUpdate=0;
                                p=p->next;
                            }
                        }
                    }
                SDL_Delay(5);
            }
        }
    }
}

ConflictQueue*  GetFast(ConflictQueue* q)
{
    ConflictQueue *p,*temp;
    temp=q;

    p=q;
    while(p!=NULL)
    {
        if(p->data->data.iSpeed>temp->data->data.iSpeed)
            temp=p;
        p=p->next;
    }

    return temp;
}

ConflictQueue*  GetFirst(ConflictQueue* q)
{
    ConflictQueue *p,*temp;
    temp=q;

    p=q;
    while(p!=NULL)
    {
        if(p->data->data.iPriority>temp->data->data.iPriority)
            temp=p;
        p=p->next;
    }

    return temp;
}
