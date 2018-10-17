
MatchList* MatchSearch(MatchList* m,SDL_Point common,SDL_Point* probe);
void SetSignal(MatchList* m,int i,int j);
void Ergodic(MatchList* m,SDL_Point common,int i);
void ConflictFree(ConflictQueue* q);
void DealConflict(ConflictQueue* q,int i);
ConflictQueue*  GetFast(ConflictQueue* q);
ConflictQueue*  GetFirst(ConflictQueue* q);
