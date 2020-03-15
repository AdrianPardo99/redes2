#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>


/* Secciones criticas de los 5 productores y consumidores */
char sec1[4]={0,0,0,0},sec2[4]={0,0,0,0};

/* Semaforos para trabajar */
sem_t a,b;

/* Contador de numero de elementos que los consumidores tienen de ambas
 * secciones criticas */
int t=0;

/* Descriptor de funciones */
void *productores(void*);
void *consumidores(void*);

int main(int argc, char const *argv[]) {
  /* Apuntadores de los productores y consumidores */
  pthread_t *arrT;
  int *id,i,val;
  arrT=(pthread_t*)malloc(sizeof(pthread_t)*10);
  id=(int*)malloc(sizeof(int)*4);
  /* Incializacion de los semaforos */
  if(sem_init(&a,0,1)==-1){
    printf("Error al abrir el primer semaforo :'v'\n");
    exit(EXIT_FAILURE);
  }
  if(sem_init(&b,0,0)){
    printf("Error al abrir el segundo semaforo :'v'\n");
    exit(EXIT_FAILURE);
  }

  /* Hilos de productores */
  for(i=0;i<5;i++){
    *(id+i)=i;
    pthread_create(&*(arrT+i),NULL,productores,(void*)&*(id+i));
  }
  /* Hilos de consumidores */
  for(i=0;i<5;i++){
    *(id+i)=i;
    pthread_create(&*(arrT+5+i),NULL,consumidores,(void*)&*(id+i));
  }

  /* En espera de que finalicen la tarea los productores */
  for(i=0;i<5;i++){
    pthread_join(*(arrT+i),NULL);
    sem_getvalue(&a,&val);
    sem_wait(&a);
    sem_post(&b);
  }

  /* En espera de que finalicen la tarea los consumidores */
  for(i=0;i<5;i++){
    pthread_join(*(arrT+i+5),NULL);
    sem_getvalue(&b,&val);
    if(val==1){
      sem_wait(&b);
      sem_post(&a);
    }else{
      sem_wait(&a);
      sem_post(&b);
    }
  }
  /* Destruccion de los semaforos */
  sem_destroy(&a);
  sem_destroy(&b);
  free(id);
  free(arrT);
  return 0;
}


/* Hilo de productor que produce letra y numero dependiendo su identificador */
void *productores(void *arg){
  int id=*((int*)arg),j=0,k=0,i=0,val;
  printf("Proceso init en productor %d\n",id );
  while(i<10000){
    sem_getvalue(&a,&val);
    if(val!=0){
      sem_wait(&a);
      for(j=0;j<4;j++){
        if(*(sec1+j)==0){
          *(sec1+j)='a'+id;
          for(k=0;k<4;k++){
            if(*(sec2+k)==0){

              *(sec2+k)='1'+id;
              i++;
              break;
            }
          }
        }
      }
      sem_post(&b);
    }
  }
  printf("Proceso finish en productor %d\n",id);
  return 0;
}

/* Consumidor que consume letra y numero */
void *consumidores(void *arg){
  int id=*((int*)arg),j,k,val;
  printf("Proceso init en consumidor %d\n",id );
  FILE *f1,*f2;
  while(t<50000){
    sem_getvalue(&b,&val);
    if(val!=0){
      if(t==50000){
        break;
      }
      sem_wait(&b);
      for(j=0;j<4;j++){

        if(t==50000){
          break;
        }
        if(*(sec1+j)!=0){
          if(*(sec1+j)=='a'){
            f1=fopen("a.txt","a");
          }else if(*(sec1+j)=='b'){
            f1=fopen("b.txt","a");
          }else if(*(sec1+j)=='c'){
            f1=fopen("c.txt","a");
          }else if(*(sec1+j)=='d'){
            f1=fopen("d.txt","a");
          }else if(*(sec1+j)=='e'){
            f1=fopen("e.txt","a");
          }
          for(k=0;k<4;k++){
            if(*(sec2+k)!=0){
              if(*(sec2+k)=='1'){
                f2=fopen("1.txt","a");
              }else if(*(sec2+k)=='2'){
                f2=fopen("2.txt","a");
              }else if(*(sec2+k)=='3'){
                f2=fopen("3.txt","a");
              }else if(*(sec2+k)=='4'){
                f2=fopen("4.txt","a");
              }else if(*(sec2+k)=='5'){
                f2=fopen("5.txt","a");
              }
              fprintf(f2, "Consumidor %d consumiendo %c\n",id,*(sec2+k));
              fprintf(f1, "Consumidor %d consumiendo %c\n",id, *(sec1+j));

              *(sec1+j)=0;
              *(sec2+k)=0;
              fclose(f1);
              fclose(f2);
              t++;
              break;
            }
          }
        }
      }
      sem_post(&a);
    }else if(t==50000){
      break;
    }
  }
  printf("Proceso finish en consumidor %d\n",id);
  sem_getvalue(&a,&val);
  if(val==1){
    sem_wait(&a);
    sem_post(&b);
  }else{
    sem_wait(&b);
    sem_post(&a);
  }
  return 0;
}
