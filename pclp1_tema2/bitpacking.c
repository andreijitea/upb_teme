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
    int nr_task, N, M = -1;
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
        char digit_num = 0, pos_num = 0;
        int packets_size = (N * DATE_SIZE + UINT_SIZE - 1) / UINT_SIZE;
        int bits_size = (packets_size + UINT_SIZE - 1) / UINT_SIZE;
        unsigned int *packets = calloc(packets_size, sizeof(unsigned int));
        unsigned int *bits = calloc(bits_size, sizeof(unsigned int));
        char *control_bits = calloc(packets_size, sizeof(char));
        char *skip = calloc(packets_size, sizeof(char));
        int *all_nums = calloc(2*N, sizeof(int));

        for (int i = 0; i < packets_size; i++) {
            scanf("%d", &packets[i]);
        }
        for (int i = 0; i < bits_size; i++) {
            scanf("%d", &bits[i]);
        }

        for (int i = 0, bi = 0; i < packets_size; i++) {
            if (i % UINT_SIZE == 0 && i != 0)
                bi++;
            control_bits[i] = (bits[bi] & (1 << (i % UINT_SIZE))) >> (i % UINT_SIZE);
        }
        //printf("N %d ps %d\n", N, packets_size);
        int i = 0, pi = 0, ni = 0, b1 = 0;
        for (; i <= packets_size * UINT_SIZE && pi < packets_size; i++) {
            if (i % UINT_SIZE == 0 && i != 0) {
                //printf("%u %d %d\n", packets[pi], b1, control_bits[pi]);
                if (b1 % 2 != control_bits[pi]) {
                    skip[pi] = 1;
                }
                pi++;
                b1 = 0;
            }
            if (i % DATE_SIZE == 0 && i != 0) {
                ni++;
                pos_num = 0;
            }
            digit_num = (packets[pi] & (1 << (i % UINT_SIZE))) >> (i % UINT_SIZE);
            if (ni < N) {
            all_nums[ni] += digit_num << pos_num;
            pos_num++;
            }
            //printf("digit %d i %d\n", digit_num, i);
            if (digit_num)
                b1++;
        }
        //printf("last %u %d %d\n", packets[pi], b1, control_bits[pi]);
    
        for (int j = 0, k = 0; j < packets_size; j++) {
            //printf("skip %d\n", skip[j]);
            if (j < 8)
                k = 2*j;
            else
                k = 2*j +1;
            if (skip[j] == 1) {
                if (j % 7 == 0 && j % 2 == 1) {
                    all_nums[k+3] = -1;
                }
                all_nums[k] = -1;
                all_nums[k+1] = -1;
                all_nums[k+2] = -1;
                
            }
        }
        M = 0;
        for (int j = 0; j < N; j++) {
            //printf("all %d\n", all_nums[j]);
            if (all_nums[j] == -1) {
                continue;
            }
            nums[M] = all_nums[j];
            M++;
        }

        free(packets);
        free(bits);
        free(control_bits);
        free(skip);
        free(all_nums);
    }

    if (M != -1)
        N = M;
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
