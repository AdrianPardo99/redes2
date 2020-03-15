#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>


/* Secciones criticas de los 5 productores y consumidores */
char sec1[4]={0,0,0,0},sec2[4]={0,0,0,0};

/* Semaforos para trabajar */
sem_t a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,gl,gl2,se1,sc1,se2,sc2;
/* a-i es para ambas secciones criticas en productores
 * a-d es para letras
 * e-h es para numeros
 * i-l es para consumir letras
 * m-p es para consumir numeros */
/* Contador de numero de elementos que los consumidores tienen de ambas
 * secciones criticas */
int t=0;

/* Descriptor de funciones */
void *productores(void*);
void *consumidores(void*);

int main(int argc, char const *argv[]) {
  /* Apuntadores de los productores y consumidores */
  pthread_t *arrT;
  int *id,ii,val;
  arrT=(pthread_t*)malloc(sizeof(pthread_t)*10);
  id=(int*)malloc(sizeof(int)*4);
  /* Incializacion de los semaforos */
  if(sem_init(&a,0,1)==-1){
    printf("Error al abrir el primer semaforo :'v'\n");
    exit(EXIT_FAILURE);
  }
  if(sem_init(&b,0,1)==-1){
    printf("Error al abrir el segundo semaforo :'v'\n");
    exit(EXIT_FAILURE);
  }
  if(sem_init(&c,0,1)==-1){
    printf("Error al abrir el tercer semaforo :'v'\n");
    exit(EXIT_FAILURE);
  }
  if(sem_init(&d,0,1)==-1){
    printf("Error al abrir el cuarto semaforo :'v'\n");
    exit(EXIT_FAILURE);
  }
  if(sem_init(&e,0,1)==-1){
    printf("Error al abrir el quinto semaforo :'v'\n");
    exit(EXIT_FAILURE);
  }
  if(sem_init(&f,0,1)==-1){
    printf("Error al abrir el sexto semaforo :'v'\n");
    exit(EXIT_FAILURE);
  }
  if(sem_init(&g,0,1)==-1){
    printf("Error al abrir el septimo semaforo :'v'\n");
    exit(EXIT_FAILURE);
  }
  if(sem_init(&h,0,1)==-1){
    printf("Error al abrir el octavo semaforo :'v'\n");
    exit(EXIT_FAILURE);
  }

  if(sem_init(&gl,0,1)==-1){
    printf("Error al abrir el noveno semaforo :'v'\n");
    exit(EXIT_FAILURE);
  }

  if(sem_init(&se1,0,1)==-1){
    printf("Error al abrir el noveno semaforo :'v'\n");
    exit(EXIT_FAILURE);
  }

  if(sem_init(&se2,0,1)==-1){
    printf("Error al abrir el noveno semaforo :'v'\n");
    exit(EXIT_FAILURE);
  }

  if(sem_init(&i,0,0)==-1){
    printf("Error al abrir el primer semaforo :'v'\n");
    exit(EXIT_FAILURE);
  }
  if(sem_init(&j,0,0)==-1){
    printf("Error al abrir el segundo semaforo :'v'\n");
    exit(EXIT_FAILURE);
  }
  if(sem_init(&k,0,0)==-1){
    printf("Error al abrir el tercer semaforo :'v'\n");
    exit(EXIT_FAILURE);
  }
  if(sem_init(&l,0,0)==-1){
    printf("Error al abrir el cuarto semaforo :'v'\n");
    exit(EXIT_FAILURE);
  }
  if(sem_init(&m,0,0)==-1){
    printf("Error al abrir el quinto semaforo :'v'\n");
    exit(EXIT_FAILURE);
  }
  if(sem_init(&n,0,0)==-1){
    printf("Error al abrir el sexto semaforo :'v'\n");
    exit(EXIT_FAILURE);
  }
  if(sem_init(&o,0,0)==-1){
    printf("Error al abrir el septimo semaforo :'v'\n");
    exit(EXIT_FAILURE);
  }
  if(sem_init(&p,0,0)==-1){
    printf("Error al abrir el octavo semaforo :'v'\n");
    exit(EXIT_FAILURE);
  }

  if(sem_init(&gl2,0,0)==-1){
    printf("Error al abrir el noveno semaforo :'v'\n");
    exit(EXIT_FAILURE);
  }

  if(sem_init(&sc1,0,0)==-1){
    printf("Error al abrir el octavo semaforo :'v'\n");
    exit(EXIT_FAILURE);
  }

  if(sem_init(&sc2,0,0)==-1){
    printf("Error al abrir el noveno semaforo :'v'\n");
    exit(EXIT_FAILURE);
  }

  /* Hilos de productores */
  for(ii=0;ii<5;ii++){
    *(id+ii)=ii;
    pthread_create(&*(arrT+ii),NULL,productores,(void*)&*(id+ii));
  }
  /* Hilos de consumidores */
  for(ii=0;ii<5;ii++){
    *(id+ii)=ii;
    pthread_create(&*(arrT+5+ii),NULL,consumidores,(void*)&*(id+ii));
  }

  /* En espera de que finalicen la tarea los productores */
  for(ii=0;ii<5;ii++){
    pthread_join(*(arrT+ii),NULL);
  }
  /* En espera de que finalicen la tarea los consumidores */
  for(ii=0;ii<5;ii++){
    pthread_join(*(arrT+ii+5),NULL);
    sem_getvalue(&gl2,&val);
    if(val==1){
      sem_wait(&gl2);
      sem_post(&gl);
    }else{
      sem_wait(&gl);
      sem_wait(&gl2);
    }
  }
  /* Destruccion de los semaforos */
  sem_destroy(&a);
  sem_destroy(&b);
  sem_destroy(&c);
  sem_destroy(&d);
  sem_destroy(&e);
  sem_destroy(&f);
  sem_destroy(&g);
  sem_destroy(&h);

  sem_destroy(&i);
  sem_destroy(&j);
  sem_destroy(&k);
  sem_destroy(&l);
  sem_destroy(&m);
  sem_destroy(&n);
  sem_destroy(&o);
  sem_destroy(&p);
  sem_destroy(&gl);
  sem_destroy(&gl2);

  sem_destroy(&se1);
  sem_destroy(&se2);
  sem_destroy(&sc1);
  sem_destroy(&sc2);

  free(id);
  free(arrT);
  return 0;
}


/* Hilo de productor que produce letra y numero dependiendo su identificador */
void *productores(void *arg){
  int id=*((int*)arg),jj=0,val=-1;
  printf("Proceso init en productor %d\n",id );
  while(jj<10000){
    sem_getvalue(&gl,&val);
    if(val!=0){
      sem_wait(&gl);
      sem_getvalue(&se1,&val);
      if(val!=0){
        sem_wait(&se1);
        while(1){
          sem_getvalue(&a,&val);
          if(val!=0&&*(sec1)==0){
            sem_wait(&a);
            *(sec1)='a'+id;
            sem_post(&i);
            break;
          }
          sem_wait(&b);
          if(val!=0&&*(sec1+1)==0){
            sem_wait(&b);
            *(sec1+1)='a'+id;
            sem_post(&j);
            break;
          }
          sem_wait(&c);
          if(val!=0&&*(sec1+2)==0){
            sem_wait(&c);
            *(sec1+2)='a'+id;
            sem_post(&k);
            break;
          }
          sem_wait(&d);
          if(val!=0&&*(sec1+3)==0){
            sem_wait(&d);
            *(sec1+3)='a'+id;
            sem_post(&l);
            break;
          }
        }
        sem_post(&sc1);
      }
      sem_getvalue(&se2,&val);
      if(val!=0){
        sem_wait(&se2);
        while(1){
          sem_getvalue(&e,&val);
          if(val!=0&&*(sec2)==0){
            sem_wait(&e);
            *(sec2)='1'+id;
            sem_post(&m);
            break;
          }
          sem_getvalue(&f,&val);
          if(val!=0&&*(sec2+1)==0){
            sem_wait(&f);
            *(sec2+1)='1'+id;
            sem_post(&n);
            break;
          }
          sem_getvalue(&g,&val);
          if(val!=0&&*(sec2+2)==0){
            sem_wait(&g);
            *(sec2+2)='1'+id;
            sem_post(&o);
            break;
          }
          sem_getvalue(&h,&val);
          if(val!=0&&*(sec2+3)==0){
            sem_wait(&h);
            *(sec2+3)='1'+id;
            sem_post(&p);
            break;
          }
        }
        sem_post(&sc2);
      }
      jj++;
      sem_post(&gl2);
    }
  }
  printf("Proceso finish en productor %d\n",id);
  return 0;
}

/* Consumidor que consume letra y numero */
void *consumidores(void *arg){
  int id=*((int*)arg),val=-1;
  printf("Proceso init en consumidor %d\n",id );
  FILE *f1,*f2;
  char *name[]={"a.txt","b.txt","c.txt","d.txt","e.txt"};
  char *name2[]={"1.txt","2.txt","3.txt","4.txt","5.txt"};
  while(t<50000){
    sem_getvalue(&gl2,&val);
    if(val!=0){
      if(t==50000){
        break;
      }
      sem_wait(&gl2);
      sem_getvalue(&sc1,&val);
      if(val!=0){
        sem_wait(&sc1);
        while(1){
          if(t==50000){
            break;
          }
          sem_getvalue(&i,&val);
          if(val!=0){
            sem_wait(&i);
            f1=fopen(name[*(sec1)-'a'],"a");
            fprintf(f1, "Consumidor %d consumiendo %c\n",id,*(sec1));
            *(sec1)=0;
            fclose(f1);
            sem_post(&a);
            break;
          }
          sem_getvalue(&j,&val);
          if(val!=0){
            sem_wait(&j);
            f1=fopen(name[*(sec1+1)-'a'],"a");
            fprintf(f1, "Consumidor %d consumiendo %c\n",id,*(sec1+1));
            *(sec1+1)=0;
            fclose(f1);
            sem_post(&b);
            break;
          }
          sem_getvalue(&k,&val);
          if(val!=0){
            sem_wait(&k);
            f1=fopen(name[*(sec1+2)-'a'],"a");
            fprintf(f1, "Consumidor %d consumiendo %c\n",id,*(sec1+2));
            *(sec1+2)=0;
            fclose(f1);
            sem_post(&c);
            break;
          }
          sem_getvalue(&l,&val);
          if(val!=0){
            sem_wait(&l);
            f1=fopen(name[*(sec1+3)-'a'],"a");
            fprintf(f1, "Consumidor %d consumiendo %c\n",id,*(sec1+3));
            *(sec1+3)=0;
            fclose(f1);
            sem_post(&d);
            break;
          }
        }
        sem_post(&se1);
      }
      sem_getvalue(&sc2,&val);
      if(val!=0){
        sem_wait(&sc2);
        while(1){
          if(t==50000){
            break;
          }
          sem_getvalue(&m,&val);
          if(val!=0){
            sem_wait(&m);
            f2=fopen(name2[*(sec2)-'1'],"a");
            fprintf(f2, "Consumidor %d consumiendo %c\n",id,*(sec2));
            *(sec2)=0;
            fclose(f2);
            sem_post(&e);
            break;
          }
          sem_getvalue(&n,&val);
          if(val!=0){
            sem_wait(&n);
            f2=fopen(name2[*(sec2+1)-'1'],"a");
            fprintf(f2, "Consumidor %d consumiendo %c\n",id,*(sec2+1));
            *(sec2+1)=0;
            fclose(f2);
            sem_post(&f);
            break;
          }
          sem_getvalue(&o,&val);
          if(val!=0){
            sem_wait(&o);
            f2=fopen(name2[*(sec2+2)-'1'],"a");
            fprintf(f2, "Consumidor %d consumiendo %c\n",id,*(sec2+2));
            *(sec2+2)=0;
            fclose(f2);
            sem_post(&g);
            break;
          }
          sem_getvalue(&p,&val);
          if(val!=0){
            sem_wait(&p);
            f2=fopen(name2[*(sec2+3)-'1'],"a");
            fprintf(f2, "Consumidor %d consumiendo %c\n",id,*(sec2+3));
            *(sec2+3)=0;
            fclose(f2);
            sem_post(&h);
            break;
          }
        }
        sem_post(&se2);
      }
      t++;
      if(t==50000){
        sem_post(&gl2);
        break;
      }
      sem_post(&gl);
    }
  }
  sem_destroy(&a);
  sem_destroy(&b);
  sem_destroy(&c);
  sem_destroy(&d);
  sem_destroy(&e);
  sem_destroy(&f);
  sem_destroy(&g);
  sem_destroy(&h);

  sem_destroy(&i);
  sem_destroy(&j);
  sem_destroy(&k);
  sem_destroy(&l);
  sem_destroy(&m);
  sem_destroy(&n);
  sem_destroy(&o);
  sem_destroy(&p);
  sem_destroy(&gl);
  sem_destroy(&gl2);
  sem_destroy(&se1);
  sem_destroy(&se2);
  sem_destroy(&sc1);
  sem_destroy(&sc2);
  exit(0);
  return 0;
}
