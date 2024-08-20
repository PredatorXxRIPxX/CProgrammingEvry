#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>


#define Max_Sizes 1000
#define Max_Threads 10

int tableau[Max_Sizes];
int taille_tableau;
sem_t semaphore;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int comparision (const void *a,const void *b){
    return (*(int*)a-*(int*)b);
}

int partition(int debut,int fin){
    int pivot = tableau[fin];
    int i = debut -1;
    for(int j = debut ; j<fin;j++){
        if(tableau[j]<pivot){
            i++;
            int temp = tableau[i];
            tableau[i]=tableau[j];
            tableau [j] = temp;
        }
    }
    int temp = tableau[i+1];
    tableau[i+1] = tableau[fin];
    tableau[fin] = temp;
    return i+1; 
}

void trier_le_tableau(int debut,int fin){
    if(debut<fin){
        int index = partition(debut,fin);
        pthread_t thread1 , thread2;

        pthread_create(&thread1,trier_le_tableau,debut,index-1);
        pthread_create(&thread2,trier_le_tableau,index+1,fin);        

        pthread_join(thread1,NULL);
        pthread_join(thread2,NULL);


    }
}

void *detecter_fin_tri(void *arguments){
    while(1){
        sem_wait(&semaphore);

        int value;
        sem_getvalue(&semaphore,&value);
        if(value == 0){
            pthread_cond_signal(&condition);
            break;
        }
    }
    return NULL;
}

int main(){
    printf("donner la taille de tableau: ");
    scanf("%d",&taille_tableau);

    printf("entrer les elements du tableau");
    for(int i=0 ; i<taille_tableau ; i++){
        scanf("%d",&tableau[i]);
    }

    trier_le_tableau(0,taille_tableau-1);
    sem_init(&semaphore,0,taille_tableau);

    pthread_t detector_Threads;
    pthread_create(&detector_Threads,NULL,detecter_fin_tri,NULL);
    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&condition,&mutex);
    pthread_mutex_unlock(&mutex);

    printf("tableau triee :\n");
    for(int i = 0;i<taille_tableau;i++){
        printf("%d",tableau[i]);

    }
    printf("\n");

    sem_destroy(&semaphore);
    pthread_cond_destroy(&condition);
    pthread_mutex_destroy(&mutex);

    return 0;

}