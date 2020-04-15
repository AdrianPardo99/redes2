/* Developed by:
 * Valdez Bernal Maria Fernanda
 * Valdez Esquivel Melani Betsabee
 * Gonzalez Pardo Adrian
 * 3CV6 20-02
 * Last file update: 15-04-2020 */

#include "clienteHeader.h"

int main(int argc,char **argv){
  if(argc<3){
    printf("Error\nUsage: %s "
      "<typeServer(0 multicast / 1 broadcast)> <PORT>\n",
      *argv);
    exit(EXIT_FAILURE);
  }

  int i,typ=atoi(*(argv+1));
  port=atoi(*(argv+2));
  if(typ<0 || typ>1){
    printf("Error because the typeServer cannot be that option...\n");
    exit(EXIT_FAILURE);
  }
  if(port<=0){
    printf("Error because the port cannot be that option...\n");
    exit(EXIT_FAILURE);
  }

  threadID=(pthread_t*)malloc(sizeof(pthread_t)*5);
  id=(int*)malloc(sizeof(int)*5);
  buffer=(char**)malloc(sizeof(char*)*5);
  imgs=(imagen*)malloc(sizeof(imagen)*5);
  if(threadID==NULL||id==NULL||buffer==NULL||imgs==NULL){
    printf("Error allocating memory in the threads or the int ids or"
      "the buffer for the images or the structures for the images\n");
    exit(EXIT_FAILURE);
  }

  (!typ)?(initClienteMulticast()):(initClienteBroadcast());
  for(i=0;i<5;i++){
    *(id+i)=i;
    pthread_create(&*(threadID+i),0,hiloCliente,(void*)&*(id+i));
  }
  for(i=0;i<5;i++){
    pthread_join(*(threadID+i),NULL);
  }
  onExit();
  free(threadID);
  free(id);
  free(buffer);
  free(imgs);
}
