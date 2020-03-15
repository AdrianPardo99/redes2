/*Developed by:
 * Valdez Bernal Maria Fernanda
 * Valdez Esquivel Melani Betsabee
 * Gonzalez Pardo Adrian
 * 3CV6 20-02
 * Last file update: 17-02-2020 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "color.h"
#define tam 500000
#define bufLine 100

/* Variables en las que cada una se podra trabajar diversas cosas como:
 *  -archivos para la lectura de la llamada ls
 *  -result para resguardar en cadena el tamaño de palabras que hay en el archivo
 *  -bufferThread para resguardar cada una de las palabras que existe en el
 *    archivo de texto
 */
char **archivos,**result,***bufferThread;
FILE **arrFp;
int *taFileLines;
void *threadLec(void*);

int main(int argc,char *argv[]){
  /* Variable para uso de procesos y de archivos */
  FILE *fp;
  int coun=0,numThread,i,*arrT,n,j,tTotal=0;
  char path[tam],inst[tam],*match,inst2[tam];
  pthread_t *arrThreads;
  /* Abre comando en el flujo de datos */
  fp = popen("ls -a | grep txt", "r");
  if (fp == NULL) {
    printf(BRED"Fallo abrir flujo\n"KNRM);
    exit(EXIT_FAILURE);
  }
  /* Lectura y conteo */
  while(fgets(path,tam,fp)!=NULL){
    coun++;
  }
  printf("Conteo de archivos: %d\n",coun);
  /* close */
  pclose(fp);
  fp = popen("ls -a | grep .txt", "r");
  if (fp == NULL) {
    printf(BRED"Fallo abrir flujo 2\n"KNRM);
    exit(EXIT_FAILURE);
  }
  archivos=(char**)malloc(sizeof(char*)*coun);
  /* Asignacion de memoria del buffer de archivos */
  for(i=0;i!=coun;i++){
    *(archivos+i)=(char*)malloc(sizeof(char)*tam);
  }
  i=0;
  /* Resguardo de archivos en el buffer de archivos */
  while(fgets(*(archivos+i++),tam,fp)!=NULL);
  /* Modificacion del ultimo caracter evitan el new line y cambiandolo por null
  */
  for(i=0;i!=coun;i++){
    *(*(archivos+i)+(strlen(*(archivos+i))-1))='\0';
  }
  pclose(fp);
  /* Solicitud de teclado del numero de threads a trabajar */
  printf("Ingresa el numero de hilos con los que deseas trabajar\n");
  scanf("%d",&numThread);
  if(numThread<=0){
    printf(BRED"Error please enter a positive integer\n"KNRM);
    exit(EXIT_FAILURE);
  }else if(numThread>coun){
    printf(BRED"Error the num of threads cannot be more bigger than the num "
      "of the files\n"KNRM);
    exit(EXIT_FAILURE);
  }
  /* Creacion de buffer result con respecto al numero de archivos que hay */
  result=(char**)malloc(sizeof(char*)*coun);
  for(i=0;i<coun;i++){
    *(result+i)=(char*)malloc(sizeof(char)*bufLine);
  }
  /* Creacion de threads dinamicos */
  arrThreads=(pthread_t*)malloc(sizeof(pthread_t)*numThread);
  arrT=(int*)malloc(sizeof(int)*numThread);
  arrFp=(FILE**)malloc(sizeof(FILE*)*numThread);
  n=0;
  /* Creacion del buffer en el que se planea resguardar la informacion del
   *  thread
   */
  bufferThread=(char***)malloc(sizeof(char**)*coun);
  taFileLines=(int*)malloc(sizeof(int)*coun);
  /* Planificacion sin semaforos y multithreading */
  while(n<coun){
    for(i=0;i<numThread;i++){
      *(arrT+i)=n;
      if(n==coun){
        n++;
        break;
      }
      pthread_create(&*(arrThreads+i),NULL,threadLec,(void*)&*(arrT+i));
      n++;
    }
    for(j=0;j<i;j++){
      pthread_join(*(arrThreads+j),NULL);
    }
  }
  /* Conteo de los resultados del tamaño de cada archivo */
  for(i=0;i<coun;i++){
    tTotal+=atoi(*(result+i));
  }
  printf("Estadistica final con numero de palabras de todos los archivos: %d\n",
    tTotal);
  /* Ejecucion de lectura de archivos */
  memcpy(inst2+0,"cat *.txt |sed -e 's/[¿?.-\\—\\,()¡!\\:\\;]/ /g'  | tr '[:space:]' "
    "'[\n*]'  | grep -v '^\\s*$' | sort | uniq -c | sort -bnr\0",
    strlen("cat *.txt |sed -e 's/[¿?.-\\—\\,()¡!\\:\\;]/ /g'  | tr '[:space:]' "
    "'[\n*]'  | grep -v '^\\s*$' | sort | uniq -c | sort -bnr\0"));
  fp = popen(inst2, "r");
  if (fp == NULL) {
    printf(BRED"Fallo abrir el ultimo flujo\n"KNRM);
    exit(EXIT_FAILURE);
  }
  /* Impresion del buffer si hay alguna coincidencia con las palabras
   * solicitadas por el profesor
   */
   int k,c=0,l;
   char *mal;
   mal=(char*)malloc(sizeof(char)*100);
  while(fgets(path,tam,fp)!=NULL){
    *(path+strlen(path)-1)='\0';
    match=strstr(path," amor\0");
    if(match!=NULL&&(strlen(match)==strlen(" amor"))){
      for(l=0;l<strlen(path);l++){
        if(*(path+l)>='0'&&*(path+l)<='9'){
          break;
        }
      }
      for(k=l;k<strlen(path);k++){
        if(*(path+k)==' '){
          break;
        }
        mal[c++]=*(path+k);
      }
      c=0;
      printf("%s porcentaje total: %f\n",path,atof(mal)/tTotal);
      continue;
    }
    match=strstr(path," Amor\0");
    if(match!=NULL&&(strlen(match)==strlen(" Amor"))){
      for(l=0;l<strlen(path);l++){
        if(*(path+l)>='0'&&*(path+l)<='9'){
          break;
        }
      }
      for(k=l;k<strlen(path);k++){
        if(*(path+k)==' '){
          break;
        }
        mal[c++]=*(path+k);
      }
      c=0;
      printf("%s porcentaje total: %f\n",path,atof(mal)/tTotal);
      continue;
    }
    match=strstr(path," Alegria\0");
    if(match!=NULL&&(strlen(match)==strlen(" Alegria"))){
      for(l=0;l<strlen(path);l++){
        if(*(path+l)>='0'&&*(path+l)<='9'){
          break;
        }
      }
      for(k=l;k<strlen(path);k++){
        if(*(path+k)==' '){
          break;
        }
        mal[c++]=*(path+k);
      }
      c=0;
      printf("%s porcentaje total: %f\n",path,atof(mal)/tTotal);
      continue;
    }
    match=strstr(path," Alegría\0");
    if(match!=NULL&&(strlen(match)==strlen(" Alegría"))){
      for(l=0;l<strlen(path);l++){
        if(*(path+l)>='0'&&*(path+l)<='9'){
          break;
        }
      }
      for(k=l;k<strlen(path);k++){
        if(*(path+k)==' '){
          break;
        }
        mal[c++]=*(path+k);
      }
      c=0;
      printf("%s porcentaje total: %f\n",path,atof(mal)/tTotal);
      continue;
    }
    match=strstr(path," alegria\0");
    if(match!=NULL&&(strlen(match)==strlen(" alegria"))){
      for(l=0;l<strlen(path);l++){
        if(*(path+l)>='0'&&*(path+l)<='9'){
          break;
        }
      }
      for(k=l;k<strlen(path);k++){
        if(*(path+k)==' '){
          break;
        }
        mal[c++]=*(path+k);
      }
      c=0;
      printf("%s porcentaje total: %f\n",path,atof(mal)/tTotal);
      continue;
    }
    match=strstr(path," alegría\0");
    if(match!=NULL&&(strlen(match)==strlen(" alegría"))){
      for(l=0;l<strlen(path);l++){
        if(*(path+l)>='0'&&*(path+l)<='9'){
          break;
        }
      }
      for(k=l;k<strlen(path);k++){
        if(*(path+k)==' '){
          break;
        }
        mal[c++]=*(path+k);
      }
      c=0;
      printf("%s porcentaje total: %f\n",path,atof(mal)/tTotal);
      continue;
    }
    match=strstr(path," Enojo\0");
    if(match!=NULL&&(strlen(match)==strlen(" Enojo"))){
      for(l=0;l<strlen(path);l++){
        if(*(path+l)>='0'&&*(path+l)<='9'){
          break;
        }
      }
      for(k=l;k<strlen(path);k++){
        if(*(path+k)==' '){
          break;
        }
        mal[c++]=*(path+k);
      }
      c=0;
      printf("%s porcentaje total: %f\n",path,atof(mal)/tTotal);
      continue;
    }
    match=strstr(path," enojo\0");
    if(match!=NULL&&(strlen(match)==strlen(" enojo"))){
      for(l=0;l<strlen(path);l++){
        if(*(path+l)>='0'&&*(path+l)<='9'){
          break;
        }
      }
      for(k=l;k<strlen(path);k++){
        if(*(path+k)==' '){
          break;
        }
        mal[c++]=*(path+k);
      }
      c=0;
      printf("%s porcentaje total: %f\n",path,atof(mal)/tTotal);
      continue;
    }
    match=strstr(path," Ira\0");
    if(match!=NULL&&(strlen(match)==strlen(" Ira"))){
      for(l=0;l<strlen(path);l++){
        if(*(path+l)>='0'&&*(path+l)<='9'){
          break;
        }
      }
      for(k=l;k<strlen(path);k++){
        if(*(path+k)==' '){
          break;
        }
        mal[c++]=*(path+k);
      }
      c=0;
      printf("%s porcentaje total: %f\n",path,atof(mal)/tTotal);
      continue;
    }
    match=strstr(path," ira\0");
    if(match!=NULL&&(strlen(match)==strlen(" ira"))){
      for(l=0;l<strlen(path);l++){
        if(*(path+l)>='0'&&*(path+l)<='9'){
          break;
        }
      }
      for(k=l;k<strlen(path);k++){
        if(*(path+k)==' '){
          break;
        }
        mal[c++]=*(path+k);
      }
      c=0;
      printf("%s porcentaje total: %f\n",path,atof(mal)/tTotal);
      continue;
    }
    match=strstr(path," Sueño\0");
    if(match!=NULL&&(strlen(match)==strlen(" Sueño"))){
      for(l=0;l<strlen(path);l++){
        if(*(path+l)>='0'&&*(path+l)<='9'){
          break;
        }
      }
      for(k=l;k<strlen(path);k++){
        if(*(path+k)==' '){
          break;
        }
        mal[c++]=*(path+k);
      }
      c=0;
      printf("%s porcentaje total: %f\n",path,atof(mal)/tTotal);
      continue;
    }
    match=strstr(path," sueño\0");
    if(match!=NULL&&(strlen(match)==strlen(" sueño"))){
      for(l=0;l<strlen(path);l++){
        if(*(path+l)>='0'&&*(path+l)<='9'){
          break;
        }
      }
      for(k=l;k<strlen(path);k++){
        if(*(path+k)==' '){
          break;
        }
        mal[c++]=*(path+k);
      }
      c=0;
      printf("%s porcentaje total: %f\n",path,atof(mal)/tTotal);
      continue;
    }
    match=strstr(path," Aburrimiento\0");
    if(match!=NULL&&(strlen(match)==strlen(" Aburrimiento"))){
      for(l=0;l<strlen(path);l++){
        if(*(path+l)>='0'&&*(path+l)<='9'){
          break;
        }
      }
      for(k=l;k<strlen(path);k++){
        if(*(path+k)==' '){
          break;
        }
        mal[c++]=*(path+k);
      }
      c=0;
      printf("%s porcentaje total: %f\n",path,atof(mal)/tTotal);
      continue;
    }
    match=strstr(path," aburrimiento\0");
    if(match!=NULL&&(strlen(match)==strlen(" aburrimiento"))){
      for(l=0;l<strlen(path);l++){
        if(*(path+l)>='0'&&*(path+l)<='9'){
          break;
        }
      }
      for(k=l;k<strlen(path);k++){
        if(*(path+k)==' '){
          break;
        }
        mal[c++]=*(path+k);
      }
      c=0;
      printf("%s porcentaje total: %f\n",path,atof(mal)/tTotal);
      continue;
    }
  }
  pclose(fp);

  for(i=0;i<coun;i++){
    free(*(result+i));
    free(*(archivos+i));
  }
  free(arrThreads);
  free(arrT);
  free(result);
  free(archivos);
  return 0;
}

void *threadLec(void *arg){
  /* Threads donde se analiza cada archivo separando el numero de palabras
   *  de cada archivo como la estadistica de las palabras que hay
   * Por otro lado tambien se crean archivos en los cuales se escribe el
   *  resultado del analisis del archivo.
   */
  char inst[tam],inst2[tam];
  int *id=(int*)arg,i;
  /* Mide palabras */
  memcpy(inst+0,"cat ",strlen("cat "));
  memcpy(inst+strlen(inst),*(archivos+*id),strlen(*(archivos+*id)));
  memcpy(inst+strlen(inst),"| sed -e 's/[¿?.-\\—\\,()¡!\\:\\;]/ /g' | tr '[:space:]'"
    " '[\\n*]'  | grep -v '^\\s*$' | sort | uniq -c | sort -bnr| wc -l",
    strlen("| sed -e 's/[¿?.-\\—\\,()¡!\\:\\;]/ /g' | tr '[:space:]' '[\\n*]'  | "
    "grep -v '^\\s*$' | sort | uniq -c | sort -bnr | wc -l"));
  *(arrFp+*id)=popen(inst,"r");
  if(*(arrFp+*id) == NULL){
    printf(BRED"Fallo abrir flujo de conteo total de palabras "
      "con id=%d del archivo: %s\n"KNRM,*id,*(archivos+*id));
    exit(EXIT_FAILURE);
  }
  while(fgets(*(result+*id),bufLine,*(arrFp+*id))!=NULL){
    *(*(result+*id)+(strlen(*(result+*id))-1))='\0';
    *(taFileLines+*id)=atoi(*(result+*id));
  }

  printf("Hilo: %d, para trabjar con archivo: %s\n"
    "Palabras del archivo  %d\n\n",*id,*(archivos+*id),*(taFileLines+*id));
  *(bufferThread+*id)=(char**)malloc(sizeof(char*)**(taFileLines+*id));
  for(i=0;i<*(taFileLines+*id);i++){
    *(*(bufferThread+*id)+i)=(char*)malloc(sizeof(char)*tam);
  }
  pclose(*(arrFp+*id));

  memcpy(inst2+0,"cat ",strlen("cat "));
  memcpy(inst2+strlen(inst2),*(archivos+*id),strlen(*(archivos+*id)));
  memcpy(inst2+strlen(inst2),"| sed -e 's/[¿?.-\\—\\,()¡!\\:\\;]/ /g' |"
    " tr '[:space:]' '[\\n*]'  | grep -v '^\\s*$' | sort | uniq -c | sort "
    "-bnr\0",strlen("| sed -e 's/[¿?.-\\—\\,()¡!\\:\\;]/ /g' | tr '[:space:]'"
    " '[\\n*]'  | grep -v '^\\s*$' | sort | uniq -c | sort -bnr\0"));
  *(arrFp+*id)=popen(inst2,"r");
  if(*(arrFp+*id) == NULL){
    printf(BRED"Fallo abrir flujo de separacion de letras "
      "con id=%d del archivo: %s\n"KNRM,*id,*(archivos+*id));
    exit(EXIT_FAILURE);
  }
  i=0;
  /* Llenado de buffer de cada archivo para los archivos de estadistica */
  while(fgets(*(*(bufferThread+*id)+i++),tam,*(arrFp+*id))){
    *(*(*(bufferThread+*id)+i-1)+strlen(*(*(bufferThread+*id)+i-1))-1)='\0';
  }
  pclose(*(arrFp+*id));

  /* Llenado de archivos de estadistica */
  char nameFile[tam];
  memcpy(nameFile+0,"outputEstadistica-",strlen("outputEstadistica-"));
  memcpy(nameFile+strlen(nameFile),*(archivos+*id),strlen(*(archivos+*id)));
  nameFile[strlen(nameFile)-4]='\0';
  memcpy(nameFile+strlen(nameFile),".csv",strlen(".csv"));
  *(arrFp+*id)=fopen(nameFile,"w");
  if(*(arrFp+*id)==NULL){
    printf(BRED"Fallo abrir flujo de escritura de la estadistica "
      "con id=%d del archivo: %s\n"KNRM,*id,*(archivos+*id));
    exit(EXIT_FAILURE);
  }
  fprintf(*(arrFp+*id), "Archivo: %s con numero total de palabras: %d\n"
    ,*(archivos+*id),*(taFileLines+*id));
  int j,c=0,l,k;
  char mal[100];
  for(i=0;i<*(taFileLines+*id);i++){
    for(l=0;l<strlen(*(*(bufferThread+*id)+i));l++){
      if(*(*(*(bufferThread+*id)+i)+l)>='0'&&*(*(*(bufferThread+*id)+i)+l)<='9'){
        break;
      }
    }
    for(k=l;k<strlen(*(*(bufferThread+*id)+i));k++){
      if(*(*(*(bufferThread+*id)+i)+k)==' '){
        break;
      }
      mal[c++]=*(*(*(bufferThread+*id)+i)+k);
    }
    c=0;
    fprintf(*(arrFp+*id),"%s porcentaje total: %f\n",*(*(bufferThread+*id)+i),atof(mal)/ *(taFileLines+*id));


  }
  fclose(*(arrFp+*id));


}
