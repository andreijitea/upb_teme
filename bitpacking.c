#include <stdio.h>
#include <stdlib.h>
#include "timelib.h"
#define MASK_DAY 31
#define MASK_MONTH 15
#define MASK_YEAR 63
#define DATE_SIZE 15
#define UINT_SIZE 32

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main()
{
    int nr_task, N, M = 0;
    char months[12][20] = {"ianuarie", "februarie", "martie",
                                "aprilie", "mai", "iunie",
                                "iulie", "august", "septembrie",
                                "octombrie", "noiembrie", "decembrie"};
    scanf("%d", &nr_task);
    scanf("%d", &N);

    unsigned int *nums = calloc(N, sizeof(unsigned int));
    TDateTimeTZ *dates = calloc(N, sizeof(TDateTimeTZ));

    if (nr_task == 7) {
        for (int i = 0; i < N; i++)
            scanf("%d", &nums[i]);

    } else if (nr_task == 8) {
        char digit_num = 0, pos_num = 0, b1 = 0;
        int bi = 0;
        int packets_size = (N * DATE_SIZE + UINT_SIZE - 1) / UINT_SIZE;
        int bits_size = (N + UINT_SIZE - 1) / UINT_SIZE;
        unsigned int *packets = calloc(packets_size, sizeof(unsigned int));
        unsigned int *bits = calloc(bits_size, sizeof(unsigned int));
        char *control_bits = calloc(N, sizeof(char));

        for (int i = 0; i < packets_size; i++) {
            scanf("%d", &packets[i]);
        }
        for (int i = 0; i < bits_size; i++) {
            scanf("%d", &bits[i]);
        }

        for (int i = 0, bi = -1; i < N; i++) {
            if (i % UINT_SIZE == 0)
                bi++;
            control_bits[i] = (bits[bi] & (1 << (i % UINT_SIZE))) >> (i % UINT_SIZE);
        }

        for (int i = 0, pi = 0, ni = 0; i < N * DATE_SIZE; i++) {
            if (i % UINT_SIZE == 0 && i != 0)
                pi++;
            if (i % DATE_SIZE == 0 && i != 0) {
                printf("%d %d %d\n", nums[ni], b1%2, control_bits[bi]);
                if (b1 % 2 == control_bits[bi]) {
                    M++;
                    ni++;
                }
                else {
                    nums[ni] = 0;
                }
                bi++;
                pos_num = 0;
                b1 = 0;
            }
            digit_num = (packets[pi] & (1 << (i % UINT_SIZE))) >> (i % UINT_SIZE);
            nums[ni] += digit_num << pos_num;
            if (digit_num)
                b1++;
            pos_num++;
        }
        if (b1 % 2 == control_bits[bi]) {
            M++;
        }

        free(packets);
        free(bits);
        free(control_bits);
    }
    N=M;
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
	
    return 0;
}
