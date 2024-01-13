#include <stdio.h>
#include <stdlib.h>
#include "timelib.h"
#define MASK_DAY 31
#define MASK_MONTH 15
#define MASK_YEAR 63

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main()
{
    int nr_task;
    scanf("%d", &nr_task);

    if (nr_task == 7) {
        char months[12][20] = {"ianuarie", "februarie", "martie",
                                "aprilie", "mai", "iunie",
                                "iulie", "august", "septembrie",
                                "octombrie", "noiembrie", "decembrie"};
        int N = 0;
        scanf("%d", &N);
        unsigned int *nums = calloc(N, sizeof(unsigned int));
        TDateTimeTZ *dates = calloc(N, sizeof(TDateTimeTZ));

        for (int i = 0; i < N; i++) {
            scanf("%d", &nums[i]);

        }
        qsort(nums, N, sizeof(unsigned int), cmp);
        for (int i = 0; i < N; i++) {
            dates[i].date.day = nums[i] & MASK_DAY;
            dates[i].date.month = (nums[i] & (MASK_MONTH << 5)) >> 5;
            dates[i].date.year = 1970 + ((nums[i] & (MASK_YEAR << 9)) >> 9);
        }
        for (int i = 0; i < N; i++)
            printf("%d %s %d\n", dates[i].date.day, months[dates[i].date.month - 1], dates[i].date.year);

        free(nums);
        free(dates); 
    } else if (nr_task == 8) {

    }
	
	
    return 0;
}
