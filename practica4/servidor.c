/* Developed by:
 * Valdez Bernal Maria Fernanda
 * Valdez Esquivel Melani Betsabee
 * Gonzalez Pardo Adrian
 * 3CV6 20-02
 * Last file update: 14-04-2020 */

#include "serverHeader.h"

int main(int argc, char *argv[]) {
  if(argc<8){
    printf("Usage %s <PICTURE-0> <PICTURE-1> <PICTURE-2> <PICTURE-3>"
      " <PICTURE-4> <typeServer(0 multicas / 1 broadcast)> <PORT>\n",*argv);
    exit(1);
  }
  signal(SIGINT,signalServer);
  int i,typ=atoi(*(argv+6));
  port=atoi(*(argv+7));
  if(typ<0 || typ>1){
    printf("Error because the typeServer cannot be that option...\n");
    exit(EXIT_FAILURE);
  }
  if(port<=0){
    printf("Error because the port cannot be that option...\n");
    exit(EXIT_FAILURE);
  }


  imgs=(images*)malloc(sizeof(images)*(argc-1));
  if(imgs==NULL){
    printf("Error allocating memory in the struct\n");
    exit(1);
  }
  for(i=1;i<6;i++){
    (imgs+i-1)->name=*(argv+i);
    (imgs+i-1)->type=isImageType(*(argv+i));
  }
  checkImages(5);
  tamFiles(5);
  informationAbout(5);
  threadID=(pthread_t*)malloc(sizeof(pthread_t)*5);
  id=(int*)malloc(sizeof(int)*5);
  a=(sem_t*)malloc(sizeof(sem_t));
  if(threadID==NULL||a==NULL||id==NULL){
    printf("Error allocating memory in the threads or the semaphores "
      "or the int ids\n");
    exit(1);
  }
  initSem();
  bandera=1;
  (!typ)?(initServerMulticast()):(initServerBroadcast());
  for(i=0;i<5;i++){
    *(id+i)=i;
    pthread_create(&*(threadID+i),0,threadFun,(void*)&*(id+i));
  }
  for(i=0;i<5;i++){
    pthread_join(*(threadID+i),NULL);
  }
  onExit();
  sem_destroy(&*(a));
  free(threadID);
  free(id);
  free(a);
  free(imgs);
  return 0;
}
