#include "includes/philosophers.h"

// void* func(void* arg)
// {
//     // detach the current thread 
//     // from the calling thread 
//     pthread_detach(pthread_self()); 
//     printf("Inside the thread\n"); 
//     // exit the current thread 
//     pthread_exit(NULL);
// }
// void fun()
// {
//     pthread_t ptid; 
//     // Creating a new thread 
// /*     while (n > 0)
//     {
//         printf("here\n");
//         n--;
//     } */
//     pthread_create(&ptid, NULL, &func, NULL);
//     printf("This line may be printed"
//            " before thread terminates\n");
//     // The following line terminates 
//     // the thread manually 
//     // pthread_cancel(ptid); 
//     // Compare the two threads created 
//     if(pthread_equal(ptid, pthread_self())) 
//         printf("Threads are equal\n"); 
//     else
//         printf("Threads are not equal\n"); 
//     // Waiting for the created thread to terminate 
//     pthread_join(ptid, NULL); 
//     printf("This line will be printed"
//            " after thread ends\n"); 
//     pthread_exit(NULL); 
// } 

//every philo needs a thread_create and a thread_exit
void* func(void* arg)
{
    pthread_detach(pthread_self()); 
  
    printf("Inside the thread\n");
    pthread_exit(NULL);//only exits if its another thread other than main
}

void fun()
{
    pthread_t ptid; 

    pthread_create(&ptid, NULL, &func, NULL);//last parameter can be arguments sent into func
    printf("This line may be printed"
           " before thread terminates\n");

    if(pthread_equal(ptid, pthread_self())) 
        printf("Threads are equal\n"); 
    else
        printf("Threads are not equal\n"); 

    pthread_join(ptid, NULL);//if a create happened, a join to the same ptid needs to happen?
    //the thread_join pauses executor until thread ptid is done, 
    //  then does the rest of the program
    //2nd parameter is to work with the return of func
  
    printf("This line will be printed"
           " after thread ends\n"); 
  
    pthread_exit(NULL);
}

int main(int ac) 
{ 
    fun();
    pthread_exit(NULL);//basically clears this thread, unnecessary in main because the return already does this
    printf("another hi\n");
    return 0; 
} 