#include "head.h"
#include "init.h"
#include "run.h"
#include "control.h"

int track_inf[16][10]={{0}};
int track[16][10]={{0}};
int signal[16][10]={{0}};

int iStrategy;
FILE* fp;


int main(int argc,char *argv[])
{
    int i;

    TrackList *pTrack,*pTemp;
    pTrack=(TrackList*)malloc(sizeof(TrackList));
    pTrack->next=NULL;

    TrainList* pTrain,*p;
    pTrain=(TrainList*)malloc(sizeof(TrainList));
    pTrain->next=NULL;

    MatchList* pMatch;
    pMatch=(MatchList*)malloc(sizeof(MatchList));
    pMatch->next=NULL;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window=SDL_CreateWindow("My Railway",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,1200,720,SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Rect button,r,r0;
    SDL_Event event;

    SDL_Surface* surface[23],* surface_open[20];
    surface[0]=SDL_LoadBMP("cross_.bmp");
    surface[1]=SDL_LoadBMP("long_.bmp");
    surface[2]=SDL_LoadBMP("up_left_.bmp");
    surface[3]=SDL_LoadBMP("up_right_.bmp");
    surface[4]=SDL_LoadBMP("down_left_.bmp");
    surface[5]=SDL_LoadBMP("down_right_.bmp");
    surface[6]=SDL_LoadBMP("cross_c_.bmp");
    surface[7]=SDL_LoadBMP("long_c_.bmp");
    surface[8]=SDL_LoadBMP("station_.bmp");
    surface[9]=SDL_LoadBMP("up_left_c_.bmp");
    surface[10]=SDL_LoadBMP("up_right_c_.bmp");
    surface[11]=SDL_LoadBMP("down_left_c_.bmp");
    surface[12]=SDL_LoadBMP("down_right_c_.bmp");

    surface[13]=SDL_LoadBMP("train_.bmp");
    surface[14]=SDL_LoadBMP("train_2_.bmp");

    surface[15]=SDL_LoadBMP("background_3_.bmp");

    surface[16]=SDL_LoadBMP("button_help_1_.bmp");
    surface[17]=SDL_LoadBMP("button_help_2_.bmp");
    surface[18]=SDL_LoadBMP("button_ok_1_1.bmp");
    surface[19]=SDL_LoadBMP("button_ok_1_2.bmp");
    surface[20]=SDL_LoadBMP("button_pause_2_1.bmp");
    surface[21]=SDL_LoadBMP("button_pause_2_2.bmp");
    surface[22]=SDL_LoadBMP("button_revise_2_1.bmp");
    surface[23]=SDL_LoadBMP("button_revise_2_2.bmp");
    surface[24]=SDL_LoadBMP("button_run_2_1.bmp");
    surface[25]=SDL_LoadBMP("button_run_2_2.bmp");

    surface[26]=SDL_LoadBMP("title.bmp");

    surface[27]=SDL_LoadBMP("hint_1.bmp");
    surface[28]=SDL_LoadBMP("hint_2.bmp");
    surface[29]=SDL_LoadBMP("hint_3.bmp");

    surface_open[0]=SDL_LoadBMP("open_1.bmp");
    surface_open[1]=SDL_LoadBMP("open_2.bmp");
    surface_open[2]=SDL_LoadBMP("open_3.bmp");
    surface_open[3]=SDL_LoadBMP("open_4.bmp");
    surface_open[4]=SDL_LoadBMP("open_5.bmp");
    surface_open[5]=SDL_LoadBMP("open_6.bmp");
    surface_open[6]=SDL_LoadBMP("open_7.bmp");
    surface_open[7]=SDL_LoadBMP("open_8.bmp");
    surface_open[8]=SDL_LoadBMP("open_9.bmp");
    surface_open[9]=SDL_LoadBMP("open_10.bmp");
    surface_open[10]=SDL_LoadBMP("open_11.bmp");
    surface_open[11]=SDL_LoadBMP("open_12.bmp");
    surface_open[12]=SDL_LoadBMP("open_13.bmp");
    surface_open[13]=SDL_LoadBMP("open_14.bmp");
    surface_open[14]=SDL_LoadBMP("open_15.bmp");
    surface_open[15]=SDL_LoadBMP("open_16.bmp");
    surface_open[16]=SDL_LoadBMP("open_17.bmp");
    surface_open[17]=SDL_LoadBMP("open_18.bmp");
    surface_open[18]=SDL_LoadBMP("open_19.bmp");
    surface_open[19]=SDL_LoadBMP("open_20.bmp");
    SDL_SetColorKey(surface[13],SDL_TRUE,SDL_MapRGB(surface[13]->format,255,255,0));
    SDL_SetColorKey(surface[16],SDL_TRUE,SDL_MapRGB(surface[16]->format,255,255,255));
    SDL_SetColorKey(surface[17],SDL_TRUE,SDL_MapRGB(surface[17]->format,255,255,255));
    SDL_SetColorKey(surface[18],SDL_TRUE,SDL_MapRGB(surface[18]->format,255,255,255));
    SDL_SetColorKey(surface[27],SDL_TRUE,SDL_MapRGB(surface[27]->format,0,0,0));
    SDL_SetColorKey(surface[28],SDL_TRUE,SDL_MapRGB(surface[28]->format,0,0,0));
    SDL_SetColorKey(surface[29],SDL_TRUE,SDL_MapRGB(surface[29]->format,0,0,0));

    SDL_Texture* texture[30],* texture_open[20];
    for(i=0;i<30;i++)
    {
        texture[i]=SDL_CreateTextureFromSurface( renderer, surface[i] );
        SDL_FreeSurface(surface[i]);
    }
    for(i=0;i<20;i++)
    {
        texture_open[i]=SDL_CreateTextureFromSurface( renderer, surface_open[i] );
        SDL_FreeSurface(surface_open[i]);
    }

    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);

    int state=0;
    bool quit=false;
    bool quit1=false,quit2=false;
    i=0;

    while(!quit){
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT){
                quit=true;
                quit1=true;
            }
            else if(event.type==SDL_MOUSEBUTTONDOWN){
                state=1;
            }
        }
        switch(state){
        case 0:
            SDL_RenderCopy(renderer,texture[26],NULL,NULL);
            SDL_RenderPresent(renderer);
            break;
        case 1:
            SDL_RenderCopy(renderer,texture_open[i],NULL,NULL);
            SDL_RenderPresent(renderer);
            SDL_Delay(20);
            i++;
            if(i==20){
                quit=true;
            }
            break;
        }
        SDL_RenderClear(renderer);
    }

    SDL_RenderCopy(renderer,texture[15],NULL,NULL);
    button.x=70,button.y=625,button.w=50,button.h=50;
    SDL_RenderCopy(renderer,texture[18],NULL,&button);

    SDL_RenderPresent(renderer);

    Uint32 StartTime;
    r.x=1200,r.y=100,r.w=250,r.h=500;
    while(r.x>950)
    {
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer,texture[15],NULL,NULL);
        button.x=70,button.y=625,button.w=50,button.h=50;
        SDL_RenderCopy(renderer,texture[18],NULL,&button);

        SDL_RenderCopy(renderer,texture[27],NULL,&r);

        SDL_RenderPresent(renderer);

        SDL_Delay(5);
        r.x-=2;

        if(SDL_PollEvent(&event)&&event.type==SDL_MOUSEBUTTONDOWN)
            break;
    }

    StartTime=SDL_GetTicks();
    while((SDL_GetTicks()-StartTime)<5000)
    {
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer,texture[15],NULL,NULL);
        button.x=70,button.y=625,button.w=50,button.h=50;
        SDL_RenderCopy(renderer,texture[18],NULL,&button);
        r.x=950;
        SDL_RenderCopy(renderer,texture[27],NULL,&r);

        SDL_RenderPresent(renderer);
        SDL_Delay(5);

        if(SDL_PollEvent(&event)&&event.type==SDL_MOUSEBUTTONDOWN)
            break;
    }

    r.x=950,r.y=100,r.w=250,r.h=500;
    while(r.x<=1200)
    {
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer,texture[15],NULL,NULL);
        button.x=70,button.y=625,button.w=50,button.h=50;
        SDL_RenderCopy(renderer,texture[18],NULL,&button);

        SDL_RenderCopy(renderer,texture[27],NULL,&r);

        SDL_RenderPresent(renderer);

        SDL_Delay(5);
        r.x+=2;

        if(SDL_PollEvent(&event)&&event.type==SDL_MOUSEBUTTONDOWN)
        {

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer,texture[15],NULL,NULL);
        button.x=70,button.y=625,button.w=50,button.h=50;
        SDL_RenderCopy(renderer,texture[18],NULL,&button);

        SDL_RenderPresent(renderer);
        break;
        }
    }

    int x,y,x0,y0;
    while(!quit1)//取轨道的左上角点和右下角点
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type==SDL_QUIT)
                quit1=true;
            else if(event.type==SDL_MOUSEBUTTONDOWN)
            {
                SDL_GetMouseState(&x0,&y0);
                if(event.button.button==SDL_BUTTON_LEFT&&x0<960&&y0<600)
                {
                    quit2=false;
                    while(!quit2)
                    {
                        while(SDL_PollEvent(&event))
                        {
                            if(event.type==SDL_MOUSEBUTTONUP)
                            {
                                if(event.button.button==SDL_BUTTON_LEFT)
                                    SDL_GetMouseState(&x,&y);
                                    quit2=true;
                            }
                        }
                    }

                    x0=x0/60*60,y0=y0/60*60,x=x/60*60,y=y/60*60;

                    r.x=x0,r.y=y0,r.w=x-x0,r.h=y-y0;
                    TrackInsert(pTrack,r);

                    if(x>x0&&y>y0&&x<960&&y<600){//画轨道

                    r.x=x0,r.y=y0,r.w=60,r.h=60;
                    RenderCopy(renderer,texture[2],texture[9],texture[8],&r,3,r.x/60,r.y/60);
                    for(r.x=x0+60;r.x<x;r.x+=60)
                        RenderCopy(renderer,texture[0],texture[6],texture[8],&r,1,r.x/60,r.y/60);

                    r.x=x0;
                    for(r.y=y0+60;r.y<y;r.y+=60)
                        RenderCopy(renderer,texture[1],texture[7],texture[8],&r,2,r.x/60,r.y/60);

                    r.x=x,r.y=y0;
                    RenderCopy(renderer,texture[3],texture[10],texture[8],&r,4,r.x/60,r.y/60);
                    for(r.y=y0+60;r.y<y;r.y+=60)
                        RenderCopy(renderer,texture[1],texture[7],texture[8],&r,2,r.x/60,r.y/60);


                    r.x=x0,r.y=y;
                    RenderCopy(renderer,texture[4],texture[11],texture[8],&r,5,r.x/60,r.y/60);
                    for(r.x=x0+60;r.x<x;r.x+=60)
                        RenderCopy(renderer,texture[0],texture[6],texture[8],&r,1,r.x/60,r.y/60);

                    r.x=x,r.y=y;
                    RenderCopy(renderer,texture[5],texture[12],texture[8],&r,6,r.x/60,r.y/60);

                    SDL_RenderPresent(renderer);

                    SDL_Delay(10);}
                }
                else if(event.button.button==SDL_BUTTON_LEFT&&x0>=70&&x0<=120&&y0>=625&&y0<=675)//点击按钮
                {
                    MatchInit(pMatch,pTrack->next);

                    r.x=1200,r.y=100,r.w=250,r.h=500;
                    while(r.x>950)
                    {
                        SDL_RenderClear(renderer);

                        SDL_RenderCopy(renderer,texture[15],NULL,NULL);
                        button.x=70,button.y=625,button.w=50,button.h=50;
                        SDL_RenderCopy(renderer,texture[18],NULL,&button);
                        RenderTrack(renderer,texture);
                        SDL_RenderCopy(renderer,texture[28],NULL,&r);

                        SDL_RenderPresent(renderer);

                        SDL_Delay(5);
                        r.x-=2;

                        if(SDL_PollEvent(&event)&&event.type==SDL_MOUSEBUTTONDOWN)
                            break;
                    }

                    StartTime=SDL_GetTicks();
                    while((SDL_GetTicks()-StartTime)<5000)
                    {
                        SDL_RenderClear(renderer);

                        SDL_RenderCopy(renderer,texture[15],NULL,NULL);
                        button.x=70,button.y=625,button.w=50,button.h=50;
                        SDL_RenderCopy(renderer,texture[18],NULL,&button);
                        RenderTrack(renderer,texture);
                        r.x=950;
                        SDL_RenderCopy(renderer,texture[28],NULL,&r);

                        SDL_RenderPresent(renderer);
                        SDL_Delay(5);

                        if(SDL_PollEvent(&event)&&event.type==SDL_MOUSEBUTTONDOWN)
                            break;
                    }

                    r.x=950,r.y=100,r.w=250,r.h=500;
                    while(r.x<=1200)
                    {
                        SDL_RenderClear(renderer);

                        SDL_RenderCopy(renderer,texture[15],NULL,NULL);
                        button.x=70,button.y=625,button.w=50,button.h=50;
                        SDL_RenderCopy(renderer,texture[18],NULL,&button);
                        RenderTrack(renderer,texture);
                        SDL_RenderCopy(renderer,texture[28],NULL,&r);

                        SDL_RenderPresent(renderer);

                        SDL_Delay(5);
                        r.x+=2;

                        if(SDL_PollEvent(&event)&&event.type==SDL_MOUSEBUTTONDOWN)
                        {

                        SDL_RenderClear(renderer);

                        SDL_RenderCopy(renderer,texture[15],NULL,NULL);
                        button.x=70,button.y=625,button.w=50,button.h=50;
                        SDL_RenderCopy(renderer,texture[18],NULL,&button);
                        RenderTrack(renderer,texture);
                        SDL_RenderPresent(renderer);
                        break;
                        }
                    }

                    quit2=false;
                    while(!quit2)//放置火车
                    {
                        while(SDL_PollEvent(&event))
                        {
                            if(event.type==SDL_MOUSEBUTTONDOWN)
                            {
                                SDL_GetMouseState(&x0,&y0);
                                if(event.button.button==SDL_BUTTON_LEFT&&
                                   x0<960&&
                                   ((pTemp=JudgeTrack(pTrack->next,x0/60*60,y0/60*60))!=NULL)&&
                                   track[x0/60][y0/60]==1&&
                                   pTemp->iStatus==0)
                                {
                                    pTemp->iStatus=1;
                                    r.x=x0/60*60,r.y=y0/60*60,r.w=60,r.h=60;
                                    SDL_RenderCopy(renderer,texture[13],NULL,&r);
                                    SDL_RenderPresent(renderer);
                                    system("init.exe");
                                    fp=fopen("config.txt","r");
                                    TrainInsert(pTrain,fp,pTemp,r.x,r.y);
                                    fclose(fp);
                                }
                                else if(event.button.button==SDL_BUTTON_LEFT&&x0>=70&&x0<=120&&y0>=625&&y0<=675)
                                {
                                    system("strategy.exe");
                                    fp=fopen("strategy.txt","r");
                                    fscanf(fp,"%d",&iStrategy);
                                    fclose(fp);

    r.x=1200,r.y=100,r.w=250,r.h=500;
    while(r.x>950)
    {
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer,texture[15],NULL,NULL);
        button.x=70,button.y=625,button.w=50,button.h=50;
        SDL_RenderCopy(renderer,texture[18],NULL,&button);

        RenderTrack(renderer,texture);

        p=pTrain->next;
        while(p!=NULL)
        {
            r0.x=p->data.Position.x,r0.y=p->data.Position.y,r0.w=60,r0.h=60;
            SDL_RenderCopy(renderer,texture[13],NULL,&r0);
            p=p->next;
        }

        SDL_RenderCopy(renderer,texture[29],NULL,&r);

        SDL_RenderPresent(renderer);

        SDL_Delay(5);
        r.x-=2;

        if(SDL_PollEvent(&event)&&event.type==SDL_MOUSEBUTTONDOWN)
            break;
    }

    StartTime=SDL_GetTicks();
    while((SDL_GetTicks()-StartTime)<5000)
    {
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer,texture[15],NULL,NULL);
        button.x=70,button.y=625,button.w=50,button.h=50;
        SDL_RenderCopy(renderer,texture[18],NULL,&button);

        RenderTrack(renderer,texture);

        p=pTrain->next;
        while(p!=NULL)
        {
            r0.x=p->data.Position.x,r0.y=p->data.Position.y,r0.w=60,r0.h=60;
            SDL_RenderCopy(renderer,texture[13],NULL,&r0);
            p=p->next;
        }

        r.x=950;
        SDL_RenderCopy(renderer,texture[29],NULL,&r);

        SDL_RenderPresent(renderer);
        SDL_Delay(5);

        if(SDL_PollEvent(&event)&&event.type==SDL_MOUSEBUTTONDOWN)
            break;
    }

    r.x=950,r.y=100,r.w=250,r.h=500;
    while(r.x<=1200)
    {
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer,texture[15],NULL,NULL);
        button.x=70,button.y=625,button.w=50,button.h=50;
        SDL_RenderCopy(renderer,texture[18],NULL,&button);

        RenderTrack(renderer,texture);

        p=pTrain->next;
        while(p!=NULL)
        {
            r0.x=p->data.Position.x,r0.y=p->data.Position.y,r0.w=60,r0.h=60;
            SDL_RenderCopy(renderer,texture[13],NULL,&r0);
            p=p->next;
        }

        SDL_RenderCopy(renderer,texture[29],NULL,&r);

        SDL_RenderPresent(renderer);

        SDL_Delay(5);
        r.x+=2;

        if(SDL_PollEvent(&event)&&event.type==SDL_MOUSEBUTTONDOWN)
        {

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer,texture[15],NULL,NULL);
        button.x=70,button.y=625,button.w=50,button.h=50;
        SDL_RenderCopy(renderer,texture[18],NULL,&button);

        SDL_RenderPresent(renderer);
        break;
        }
    }

                                    Run(renderer,pTrain->next,texture,pMatch->next);
                                    quit2=true;
                                    quit1=true;
                                }
                            }
                            SDL_Delay(10);
                        }
                        SDL_Delay(10);
                    }
                }
            }
        }
        SDL_Delay(10);
    }

    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}







