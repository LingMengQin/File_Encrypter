#include <stdio.h>

/**
 * @brief 
 * This module can show a for loop progress through a ProgressBar
 * example:
 * ~~~C
 *      int maxCount = MAXCOUNT;
 *      InitProgressBar(maxCount,  50);
 *      for(int i = 0; i < maxCount; i++){
 *          UpdateProgressBar(i);
 *      }
 * ~~~
 * output:
 * --------------------------------------------------
 * =============
 */


static unsigned __int64 interval = 0;
static unsigned __int64 _maxcount = 0;
static unsigned __int64 _count = 0;

void InitProgressBar(__int64 maxCount, __int8 theNumberOfBarPoints){
    _count = 0;
    if(maxCount < theNumberOfBarPoints)
        theNumberOfBarPoints = maxCount;
    _maxcount = maxCount;
    interval = maxCount / theNumberOfBarPoints;
    for(__int8 i = 0; i < theNumberOfBarPoints; i++)    
        printf("_");
    printf("\n");
    return ;
}
static void _UpdateProgressBar(){
    if(_count % interval == 0)
        printf("=");
    return ;
}
void UpdateProgressBar(__int64 count){
    while(_count < count){
        _count++;
        _UpdateProgressBar();
    }
    return ;
}