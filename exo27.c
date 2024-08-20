#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<openssl/md5.h>

#define Max_threads 10
#define Max_nonces 5 

char hash[1+2*MD5_DIGEST_LENGTH] = {0};
int found_nonces[Max_nonces] = {0};
int found_count = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

char* md5hash(const char *str) {
    unsigned char md5[MD5_DIGEST_LENGTH] = {0};
    MD5((const unsigned char *)str, strlen(str), md5);
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        sprintf(hash + 2 * i, "%02x", md5[i]);
    }
    return hash;
}

int zeros(const char*s,int n){
    for(int i=0;i<n;i++){
        if(s[i]!="0"){
            return 0;
        }
    }
    return 1;
}

void *bruteForce(void*arguments){
    int thread_id = *(int*)arguments;
    int start = thread_id;
    int step = Max_threads;
    int zero = 6;

    char str[128];
    int count = 0;
    while (found_count<Max_nonces)
    {
        sprintf(str,"%d",start);
        md5hash(str);
        if(zeros(hash,zero)){
            pthread_mutex_lock(&mutex);
            found_nonces[found_count] = start;
            printf("Nonce found :%d\n",found_nonces[found_count]);
            found_count++;
            pthread_mutex_unlock(&mutex);
        }
        start+=step;

    }
    return NULL;
    
}

int main(){
    pthread_t threads [Max_threads];
    int thread_ids[Max_threads];

    for(int i=0;i<Max_threads;i++){
        thread_ids[i] = i;
        if(pthread_create(&threads[i],NULL,bruteForce,(void *)&thread_ids[i])!=0){
            perror("threads_create");
            exit(EXIT_FAILURE);
        }
    }
    for (size_t i = 0; i < Max_threads; i++)
    {
        if(pthread_join(threads[i],NULL)!=0){
            perror("pthread joined");
            exit(EXIT_FAILURE);
        }
    }
    return 0;
    
}