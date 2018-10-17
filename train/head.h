#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


typedef struct TrackNode{
        SDL_Rect data;
        int iStatus;
        struct TrackNode* next;
        }TrackList;

struct train{
        int iSpeed;
        SDL_Point Position;
        int iStartTime;
		int iDirection;
		int iWaitingTime;
		int iUpdate;
		int iControl;
		int iPriority;
		int iTimer;
		TrackList* pTrack;
        };

typedef struct TrainNode{
        struct train data;
        struct TrainNode* next;
        }TrainList;

struct match{
        SDL_Point common;
        SDL_Point probe[2];
        };

typedef struct MatchNode{
        struct match data;
        struct MatchNode* next;
        }MatchList;

typedef struct ConflictNode{
        TrainList* data;
        struct ConflictNode* next;
        }ConflictQueue;
