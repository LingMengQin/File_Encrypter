void ErrorHandling(string message);
void Exit_manual(int exitcode);
void Delay(int second);

void InitProgressBar(__int64 maxCount, __int8 theNumberOfBarPoints);
void ProgressBar_Update();
void UpdateProgressBar(__int64 count);

int64_t GetFileSize(FILE *file);