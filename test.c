#include <stdio.h>

int main()
{
    for(int i =0 ; i< 3; ++i)
    {
        int x,y;
        if(i != 2)
            fscanf(stdin,"(%d,%d) ",&x,&y);
        else
        {
            fscanf(stdin,"(%d,%d)",&x,&y);
        }
        
        printf("%d %d\n",x,y);
    }
}