OS FAT LAB

bash

#!/bin/bash

echo "Please enter a number:"
read number

# Check if the number is valid using if-else
if [ "$number" -lt 1 ]; then
  echo "Error: The number must be greater than or equal to 1."
elif [ "$number" -ge 1 ] && [ "$number" -le 5 ]; then
  # Use a for loop to print the squares from 1 to the number
  echo "The squares of numbers from 1 to $number are:"
  for ((i=1; i<=number; i++)); do
    square=$((i * i))
    echo "$i squared is $square"
  done

elif [ "$number" -ge 6 ] && [ "$number" -le 10 ]; then
  # Use a while loop to print numbers in reverse order
  echo "Printing numbers from $number to 1:"
  counter=$number
  while [ "$counter" -ge 1 ]; do
    echo "$counter"
    ((counter--))
  done

else
  # Prompt for a letter grade if the number is above 10
  echo "Please enter a letter grade (A, B, C, D, or F):"
  read grade

  # Use a case statement to give feedback based on the grade
  case $grade in
    A)
      echo "Excellent work!"
      ;;
    B)
      echo "Good job!"
      ;;
    C)
      echo "You passed."
      ;;
    D)
      echo "Needs improvement."
      ;;
    F)
      echo "Failing grade."
      ;;
    *)
      echo "Invalid grade entered."
      ;;
  esac
fi



FCFS non preemptive

#include <stdio.h>
 int main() {
 int n;
 printf("Enter number of processes: ");
 scanf("%d", &n);
 int at[n], bt[n], ct[n], tat[n], wt[n];
 int i;
 printf("Enter arrival times for each process: \n");
 for (i = 0; i < n; i++) {
 printf("Arrival time for P%d: ", i+1);
 scanf("%d", &at[i]);
 }
 printf("Enter burst times for each process: \n");
 for (i = 0; i < n; i++) {
 printf("Burst time for P%d: ", i+1);
 scanf("%d", &bt[i]);
 }
 ct[0] = at[0] + bt[0];
 for (i = 1; i < n; i++) {
 if (at[i] > ct[i-1]) {
 ct[i] = at[i] + bt[i];
 } else {
 ct[i] = ct[i-1] + bt[i];
 }
 }
 for (i = 0; i < n; i++) {
 tat[i] = ct[i]-at[i];
 wt[i] = tat[i]-bt[i];
 }
printf("\nP.No\tAT\tBT\tCT\tTAT\tWT\n");
 for (i = 0; i < n; i++) {
 printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], ct[i],
 tat[i], wt[i]);
 }
 return 0;
 }

SJF preemptive



 #include <stdio.h>
 #define MAX 100
 void findWaitingTime(int processes[], int n, int bt[], int wt[], int at[])
 {
 int remaining_time[MAX], complete = 0, t = 0, minm = MAX;
 int shortest = 0, finish_time;
 int check = 0;
 for (int i = 0; i < n; i++)
 remaining_time[i] = bt[i];
 while (complete != n) {
 for (int j = 0; j < n; j++) {
 if ((at[j] <= t) && (remaining_time[j] < minm) &&
 remaining_time[j] > 0) {
 minm = remaining_time[j];
 shortest = j;
 check = 1;
 }
 }
 if (check == 0) {
 t++;
 continue;
 }
 remaining_time[shortest]--;
 minm = remaining_time[shortest];
 if (minm == 0)
 minm = MAX;
 if (remaining_time[shortest] == 0) {
complete++;
 check = 0;
 finish_time = t + 1;
 wt[shortest] = finish_time-bt[shortest]-at[shortest];
 if (wt[shortest] < 0)
 wt[shortest] = 0;
 }
 t++;
 }
 }
 void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int
 tat[]) {
 for (int i = 0; i < n; i++)
 tat[i] = bt[i] + wt[i];
 }
 void findAverageTime(int processes[], int n, int bt[], int at[]) {
 int wt[MAX], tat[MAX], total_wt = 0, total_tat = 0;
 findWaitingTime(processes, n, bt, wt, at);
 findTurnAroundTime(processes, n, bt, wt, tat);
 printf("Processes Burst Time Arrival Time Waiting Time
 Turnaround Time\n");
 for (int i = 0; i < n; i++) {
 total_wt += wt[i];
 total_tat += tat[i];
 printf(" %d %d %d %d
 %d\n", processes[i], bt[i], at[i], wt[i], tat[i]);
 }
 printf("\nAverage Waiting Time = %.2f", (float)total_wt / n);
 printf("\nAverage Turnaround Time = %.2f\n", (float)total_tat / n);
 }
 int main() {
 int n;
printf("Enter the number of processes: ");
 scanf("%d", &n);
 int processes[n], burst_time[n], arrival_time[n];
 for (int i = 0; i < n; i++) {
 processes[i] = i + 1;
 printf("Enter burst time for process %d: ", i + 1);
 scanf("%d", &burst_time[i]);
 printf("Enter arrival time for process %d: ", i + 1);
 scanf("%d", &arrival_time[i]);
 }
 findAverageTime(processes, n, burst_time, arrival_time);
 return 0;
 }


Banker’s algo



#include <stdbool.h>
#define maxp 10
#define maxr 10

void calculateNeed(int need[maxp][maxr], int max[maxp][maxr], int allot[maxp][maxr], int n, int m) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - allot[i][j];
}

bool isSafe(int processes[], int avail[], int max[][maxr], int allot[][maxr], int n, int m) {
    int need[maxp][maxr], work[maxr];
    bool finish[maxp] = {false};
    int safeSeq[maxp], count = 0;

    calculateNeed(need, max, allot, n, m);

    for (int i = 0; i < m; i++) 
        work[i] = avail[i];

    while (count < n) {
        bool found = false;
        for (int p = 0; p < n; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < m; j++)
                    if (need[p][j] > work[j])
                        break;
                if (j == m) {
                    for (int k = 0; k < m; k++)
                        work[k] += allot[p][k];
                    safeSeq[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found) 
            return false;
    }

    printf("System is in a safe state. Safe sequence: ");
    for (int i = 0; i < n; i++) 
        printf("%d ", safeSeq[i]);
    printf("\n");

    return true;
}

int main() {
    int n, m, processes[maxp], avail[maxr], max[maxp][maxr], allot[maxp][maxr];

    printf("Enter number of processes and resources: ");
    scanf("%d %d", &n, &m);

    printf("Enter available resources: ");
    for (int i = 0; i < m; i++) 
        scanf("%d", &avail[i]);

    printf("Enter max and allocation matrices:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d max: ", i);
        for (int j = 0; j < m; j++) 
            scanf("%d", &max[i][j]);
        printf("Process %d allocation: ", i);
        for (int j = 0; j < m; j++) 
            scanf("%d", &allot[i][j]);
    }

    isSafe(processes, avail, max, allot, n, m);

    return 0;
}


Priority based scheduling    42


#include <stdio.h>

int main() {
    int n, i, j, pos, currentTime = 0, completedCount = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int at[n], bt[n], ct[n], tat[n], wt[n], prio[n], completed[n];
    for (i = 0; i < n; i++) completed[i] = 0;
    printf("Enter arrival times for each process: \n");
    for (i = 0; i < n; i++) {
        printf("Arrival time for P%d: ", i + 1);
        scanf("%d", &at[i]);
    }
    printf("Enter burst times for each process: \n");
    for (i = 0; i < n; i++) {
        printf("Burst time for P%d: ", i + 1);
        scanf("%d", &bt[i]);
    }
    printf("Enter priorities for each process: \n");
    for (i = 0; i < n; i++) {
        printf("Priority for P%d: ", i + 1);
        scanf("%d", &prio[i]);
    }
    while (completedCount < n) {
        pos = -1;
        for (j = 0; j < n; j++) {
            if (!completed[j] && at[j] <= currentTime) {
                if (pos == -1 || prio[j] < prio[pos]) pos = j;
                else if (prio[j] == prio[pos] && at[j] < at[pos]) pos = j;
            }
        }
        if (pos != -1) {
            ct[pos] = currentTime + bt[pos];
            tat[pos] = ct[pos] - at[pos];
            wt[pos] = tat[pos] - bt[pos];
            completed[pos] = 1;
            currentTime = ct[pos];
            completedCount++;
        } else {
            currentTime++;
        }
    }
    printf("\nP.No\tAT\tBT\tPriority\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n", i + 1, at[i], bt[i], prio[i], ct[i], tat[i], wt[i]);
    }
    return 0;
}



BEST fit worst fit   43


#include <stdio.h>

int main() {
    int m, n;

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);
    int blockSizes[m];
    for (int i = 0; i < m; i++) {
        printf("Enter size of block %d: ", i + 1);
        scanf("%d", &blockSizes[i]);
    }

    printf("\nEnter number of processes: ");
    scanf("%d", &n);
    int processSizes[n];
    for (int i = 0; i < n; i++) {
        printf("Enter size of process %d: ", i + 1);
        scanf("%d", &processSizes[i]);
    }

    int blockSizesCopy[m];

    // Run Best Fit
    for (int i = 0; i < m; i++) blockSizesCopy[i] = blockSizes[i];
    bestFit(blockSizesCopy, m, processSizes, n);

    // Run Worst Fit
    for (int i = 0; i < m; i++) blockSizesCopy[i] = blockSizes[i];
    worstFit(blockSizesCopy, m, processSizes, n);

    // Run First Fit
    for (int i = 0; i < m; i++) blockSizesCopy[i] = blockSizes[i];
    firstFit(blockSizesCopy, m, processSizes, n);

    return 0;
}

void bestFit(int blockSizes[], int m, int processSizes[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int bestIndex = -1;
        for (int j = 0; j < m; j++) {
            if (blockSizes[j] >= processSizes[i]) {
                if (bestIndex == -1 || blockSizes[j] < blockSizes[bestIndex]) {
                    bestIndex = j;
                }
            }
        }

        if (bestIndex != -1) {
            allocation[i] = bestIndex;
            blockSizes[bestIndex] -= processSizes[i];
        }
    }

    printf("\nBest Fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1) {
            printf("Process %d allocated to block %d\n", i + 1, allocation[i] + 1);
        } else {
            printf("Process %d not allocated\n", i + 1);
        }
    }
}

void worstFit(int blockSizes[], int m, int processSizes[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int worstIndex = -1;
        for (int j = 0; j < m; j++) {
            if (blockSizes[j] >= processSizes[i]) {
                if (worstIndex == -1 || blockSizes[j] > blockSizes[worstIndex]) {
                    worstIndex = j;
                }
            }
        }

        if (worstIndex != -1) {
            allocation[i] = worstIndex;
            blockSizes[worstIndex] -= processSizes[i];
        }
    }

    printf("\nWorst Fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1) {
            printf("Process %d allocated to block %d\n", i + 1, allocation[i] + 1);
        } else {
            printf("Process %d not allocated\n", i + 1);
        }
    }
}

void firstFit(int blockSizes[], int m, int processSizes[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSizes[j] >= processSizes[i]) {
                allocation[i] = j;
                blockSizes[j] -= processSizes[i];
                break;
            }
        }
    }

    printf("\nFirst Fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1) {
            printf("Process %d allocated to block %d\n", i + 1, allocation[i] + 1);
        } else {
            printf("Process %d not allocated\n", i + 1);
        }
    }
}



Round robin   45



#include <stdio.h>

void main() {
    int n, sq = 0, count = 0, i, qt, bt[10], at[10], tat[10];
    int wt[10], rbt[10], temp;
    float atat = 0, awt = 0;

    printf("Enter the number of processes\n");
    scanf("%d", &n);

    printf("Enter the burst time of processes\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
        rbt[i] = bt[i];
    }

    printf("Enter the quantum time\n");
    scanf("%d", &qt);

    while (1) {
        for (i = 0, count = 0; i < n; i++) {
            temp = qt;
            if (rbt[i] == 0) {
                count++;
                continue;
            }
            if (rbt[i] > qt)
                rbt[i] -= qt;
            else {
                temp = rbt[i];
                rbt[i] = 0;
            }
            sq += temp;
            tat[i] = sq;
        }
        if (n == count)
            break;
    }

    printf("\nProcess\tBurst Time\tTurn Around Time\tWaiting Time\n");
    for (i = 0; i < n; i++) {
        wt[i] = tat[i] - bt[i];
        awt += wt[i];
        atat += tat[i];
        printf("\n%d\t%d\t\t%d\t\t%d", i + 1, bt[i], tat[i], wt[i]);
        printf("\n");
    }

    awt /= n;
    atat /= n;
    printf("Average Waiting Time = %f\n", awt);
    printf("Average Turn Around Time = %f\n", atat);
}


SRTF cpu scheduling   48a



#include <stdio.h>

int main() {
    int n, i, j, currentTime = 0, completedCount = 0, min_bt, pos;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int at[n], bt[n], ct[n], tat[n], wt[n], rbt[n], completed[n];
    for (i = 0; i < n; i++) completed[i] = 0;
    printf("Enter arrival times for each process: \n");
    for (i = 0; i < n; i++) {
        printf("Arrival time for P%d: ", i + 1);
        scanf("%d", &at[i]);
    }
    printf("Enter burst times for each process: \n");
    for (i = 0; i < n; i++) {
        printf("Burst time for P%d: ", i + 1);
        scanf("%d", &bt[i]);
        rbt[i] = bt[i];
    }
    while (completedCount < n) {
        min_bt = 9999;
        pos = -1;
        for (j = 0; j < n; j++) {
            if (!completed[j] && at[j] <= currentTime && rbt[j] < min_bt) {
                min_bt = rbt[j];
                pos = j;
            }
        }
        if (pos != -1) {
            rbt[pos]--;
            currentTime++;
            if (rbt[pos] == 0) {
                ct[pos] = currentTime;
                tat[pos] = ct[pos] - at[pos];
                wt[pos] = tat[pos] - bt[pos];
                completed[pos] = 1;
                completedCount++;
            }
        } else {
            currentTime++;
        }
    }
    printf("\nP.No\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }
    return 0;
}

Preemptive priority based  49a


#include <stdio.h>

int main() {
    int n, i, j, currentTime = 0, completedCount = 0, min_priority, pos;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int at[n], bt[n], ct[n], tat[n], wt[n], rbt[n], prio[n], completed[n];
    for (i = 0; i < n; i++) completed[i] = 0;
    printf("Enter arrival times for each process: \n");
    for (i = 0; i < n; i++) {
        printf("Arrival time for P%d: ", i + 1);
        scanf("%d", &at[i]);
    }
    printf("Enter burst times for each process: \n");
    for (i = 0; i < n; i++) {
        printf("Burst time for P%d: ", i + 1);
        scanf("%d", &bt[i]);
        rbt[i] = bt[i];
    }
    printf("Enter priorities for each process: \n");
    for (i = 0; i < n; i++) {
        printf("Priority for P%d: ", i + 1);
        scanf("%d", &prio[i]);
    }
    while (completedCount < n) {
        min_priority = 9999;
        pos = -1;
        for (j = 0; j < n; j++) {
            if (!completed[j] && at[j] <= currentTime && prio[j] < min_priority) {
                min_priority = prio[j];
                pos = j;
            }
        }
        if (pos != -1) {
            rbt[pos]--;
            currentTime++;
            if (rbt[pos] == 0) {
                ct[pos] = currentTime;
                tat[pos] = ct[pos] - at[pos];
                wt[pos] = tat[pos] - bt[pos];
                completed[pos] = 1;
                completedCount++;
            }
        } else {
            currentTime++;
        }
    }
    printf("\nP.No\tAT\tBT\tPriority\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n", i + 1, at[i], bt[i], prio[i], ct[i], tat[i], wt[i]);
    }
    return 0;
}








 Shell script swap num    42b

#!/bin/bash

# Check if exactly two arguments are provided
if [ $# -ne 2 ]; then
    echo "Usage: $0 num1 num2"
    exit 1
fi

# Read the input numbers
num1=$1
num2=$2

# Swap the numbers
temp=$num1
num1=$num2
num2=$temp

# Display the swapped numbers
echo "After swapping:"
echo "num1 = $num1"
echo "num2 = $num2"



Shell script three num   45b


#!/bin/bash

if [ $# -ne 3 ]; then
    echo "Usage: $0 num1 num2 num3"
    exit 1
fi

num1=$1
num2=$2
num3=$3

if [ $num1 -ge $num2 ] && [ $num1 -ge $num3 ]; then
    greatest=$num1
elif [ $num2 -ge $num1 ] && [ $num2 -ge $num3 ]; then
    greatest=$num2
else
    greatest=$num3
fi

echo "The greatest number is: $greatest"





Shell Script fibonacci  49b


#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 number_of_terms"
    exit 1
fi

n=$1

if ! [[ "$n" =~ ^[0-9]+$ ]]; then
    echo "Error: Input must be a non-negative integer."
    exit 1
fi

a=0
b=1

echo "Fibonacci series up to $n terms:"

for (( i=0; i<n; i++ ))
do
    echo -n "$a "
    fn=$((a + b))
    a=$b
    b=$fn
done

echo



Shell script prime  55b


#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 number"
    exit 1
fi

num=$1

if ! [[ "$num" =~ ^[0-9]+$ ]]; then
    echo "Error: Input must be a non-negative integer."
    exit 1
fi

if [ $num -le 1 ]; then
    echo "$num is not a prime number."
    exit 0
fi

for (( i=2; i*i<=$num; i++ ))
do
    if [ $((num % i)) -eq 0 ]; then
        echo "$num is not a prime number."
        exit 0
    fi
done

echo "$num is a prime number."



Shell script reverse order  58b


#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 number"
    exit 1
fi

num=$1
reverse=0

while [ $num -gt 0 ]; do
    remainder=$((num % 10))
    reverse=$((reverse * 10 + remainder))
    num=$((num / 10))
done

echo "Reversed number: $reverse"



Shell script factorial  61b


#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 number"
    exit 1
fi

num=$1

if ! [[ "$num" =~ ^[0-9]+$ ]]; then
    echo "Error: Input must be a non-negative integer."
    exit 1
fi

factorial=1

for (( i=1; i<=num; i++ ))
do
    factorial=$((factorial * i))
done

echo "Factorial of $num is $factorial"


Shell script books  63b


#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 book_name"
    exit 1
fi

book=$1
available_books=("Data structure" "Operating system" "Discrete mathematics" "Algorithms")

found=0
for b in "${available_books[@]}"; do
    if [ "$b" == "$book" ]; then
        found=1
        break
    fi
done

if [ $found -eq 1 ]; then
    echo "The book '$book' is available."
else
    echo "Error: The book '$book' is not available."
fi







Threads odd even  52b


#include <stdio.h>
#include <pthread.h>

#define MAX 100

int odd_sum = 0, even_sum = 0;
int odd_numbers[MAX], even_numbers[MAX];
int odd_count = 0, even_count = 0;

void* find_odd_sum(void* arg) {
    for (int i = 1; i <= MAX; i++) {
        if (i % 2 != 0) {
            odd_sum += i;
            odd_numbers[odd_count++] = i;
        }
    }
    return NULL;
}

void* find_even_sum(void* arg) {
    for (int i = 1; i <= MAX; i++) {
        if (i % 2 == 0) {
            even_sum += i;
            even_numbers[even_count++] = i;
        }
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, find_odd_sum, NULL);
    pthread_create(&thread2, NULL, find_even_sum, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Sum of odd numbers: %d\n", odd_sum);
    printf("Sum of even numbers: %d\n", even_sum);

    printf("Odd numbers: ");
    for (int i = 0; i < odd_count; i++) {
        printf("%d ", odd_numbers[i]);
    }
    printf("\n");

    printf("Even numbers: ");
    for (int i = 0; i < even_count; i++) {
        printf("%d ", even_numbers[i]);
    }
    printf("\n");

    return 0;
}

Thread mean max  59b


#include <stdio.h>
#include <pthread.h>

#define SIZE 10

int numbers[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
double mean = 0;
int max_value = 0;

void* calculate_mean(void* arg) {
    int sum = 0;
    for (int i = 0; i < SIZE; i++) {
        sum += numbers[i];
    }
    mean = (double)sum / SIZE;
    return NULL;
}

void* calculate_max(void* arg) {
    max_value = numbers[0];
    for (int i = 1; i < SIZE; i++) {
        if (numbers[i] > max_value) {
            max_value = numbers[i];
        }
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, calculate_mean, NULL);
    pthread_create(&thread2, NULL, calculate_max, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Mean of the numbers: %.2f\n", mean);
    printf("Maximum value: %d\n", max_value);

    return 0;
}


 Fork orphan   47b



#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        // Fork failed
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("This is the child process. PID: %d\n", getpid());
        sleep(5); // Sleep to ensure the parent process terminates first
        printf("Child process is now orphaned. PID: %d, Parent PID: %d\n", getpid(), getppid());
    } else {
        // Parent process
        printf("This is the parent process. PID: %d\n", getpid());
        printf("Parent process is terminating.\n");
    }

    return 0;
}



Fork Zombie   48b


#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        // Fork failed
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("This is the child process. PID: %d\n", getpid());
        printf("Child process is terminating.\n");
    } else {
        // Parent process
        printf("This is the parent process. PID: %d\n", getpid());
        sleep(10); // Sleep to keep the parent process alive
        printf("Parent process is terminating.\n");
    }

    return 0;
}

