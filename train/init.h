
void RenderCopy(SDL_Renderer* renderer,SDL_Texture* texture1,SDL_Texture* texture2,SDL_Texture* texture,SDL_Rect* pr,int i,int x,int y);
void TrackInsert(TrackList* t,SDL_Rect r);
void TrainInsert(TrainList* t,FILE* fp,TrackList* q,int x,int y);
TrackList* JudgeTrack(TrackList* t,int x,int y);
void RenderTrack(SDL_Renderer* renderer,SDL_Texture* texture[14]);

void MatchInsert(MatchList* m,struct match x);
void MatchInit(MatchList* m,TrackList* t);

void ConflictInsert(ConflictQueue* q,TrainList* x);
