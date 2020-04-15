/* Developed by:
 * Valdez Bernal Maria Fernanda
 * Valdez Esquivel Melani Betsabee
 * Gonzalez Pardo Adrian
 * 3CV6 20-02
 * Last file update: 14-04-2020 */

#include "serverHeader.h"

void signalServer(int s){
  if(s==2){
    printf("\n\nServer down\nPlease wait for down the server...\n");
    bandera=0;
  }
}

void sleepT(int a){
  clock_t star=clock();
  while(clock()<star+a);
}

void printTrama(trama *tr){
  int i;
  for(i=0;i<tramaTamMax;i++){
    if(i%16==0){
      printf("\n");
    }
    printf(" %02X ",*(tr+i));
  }
  printf("\n");
}

void *threadFun(void *arg){
  int id=*((int*)arg),i=0,j,val=0,val2=1;
  trama *buffer,*valM;
  FILE *file;
  buffer=(trama*)malloc(sizeof(trama)*tramaTamMax);
  valM=(trama*)malloc(sizeof(trama)*tramaTamMax);
  printf("Image[%d]\n",id);
  if(buffer==NULL){
    printf("Error to allocating memory for the buffer\n");
    exit(EXIT_FAILURE);
  }
  for(j=0;j<tramaTamMax;j++){
    *(buffer+j)=0x00;
    *(valM+j)=0x00;
  }
  *(buffer)=((id+1)<<4)&0xf0;
  *(buffer)+=((imgs+id)->type)&0x0f;
  *(buffer+1)=0x00;
  *(buffer+2)=0x01;
  *(buffer+3)=((imgs+id)->segmentosMTU>>8)&0xff;
  *(buffer+4)=((imgs+id)->segmentosMTU)&0xff;
  while(bandera){
    sem_getvalue(&*(a),&val);
    if(val!=0){
      sem_wait(&*(a));
      file=fopen((imgs+id)->name,"rb");
      if(file==NULL){
        printf("Error to open the file\n");
        exit(EXIT_FAILURE);
      }
      i=0;
      *(buffer+1)=0x00;
      *(buffer+2)=0x01;
      while(fgets(valM,(imgs+id)->mtuMax,file)&&bandera){
        memcpy(buffer+5,valM+0,strlen(valM));
        sentData(buffer);
        i++;
        if(*(buffer+2)==0xff){
          *(buffer+1)+=1;
          *(buffer+2)=0;
        }else{
          *(buffer+2)+=1;
        }
        sleepT(20000);
        sem_post(&*(a));
      }
      fclose(file);
    }
  }
}

void sentData(char *n){
  if(sendto(sock,n,tramaTamMax,0,(struct sockaddr*)&sock_in,sinlen)==-1){
    printf("Error sendto\n");
    exit(EXIT_FAILURE);
  }
}

void onExit(){
  shutdown(sock,SHUT_RDWR);
  close(sock);
}

void initServerBroadcast(){
  int yes=1;
  sinlen=sizeof(struct sockaddr_in);
  memset(&sock_in,0,sinlen);

  if((sock=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP))==-1){
    printf("Error open socket\n");
    exit(EXIT_FAILURE);
  }

  sock_in.sin_addr.s_addr=htonl(INADDR_ANY);
  sock_in.sin_port=htons(0);
  sock_in.sin_family=PF_INET;

  if((status=bind(sock,(struct sockaddr *)&sock_in,sinlen))<0){
    printf("Error bind socket\n");
    exit(EXIT_FAILURE);
  }
  if((status=setsockopt(sock,SOL_SOCKET,SO_BROADCAST,&yes,sizeof(int)))==-1){
    printf("Error setsockopt\n");
    exit(EXIT_FAILURE);
  }
  sock_in.sin_addr.s_addr=htonl(-1); /* send message to 255.255.255.255 */
  sock_in.sin_port = htons(port); /* port number */
  sock_in.sin_family = PF_INET;
  printf("Server Broadcast port access: %d\n",htons(sock_in.sin_port));
}

void initServerMulticast(){
  unsigned char ttl = 3;
  unsigned char one = 1;
  sinlen=sizeof(struct sockaddr_in);
  struct in_addr iaddr;
  memset(&sock_in,0,sinlen);
  memset(&sock_in, 0, sizeof(struct sockaddr_in));
  memset(&imreq, 0, sizeof(struct ip_mreq));
  if((sock=socket(PF_INET,SOCK_DGRAM,0))==-1){
    printf("Error open socket\n");
    exit(EXIT_FAILURE);
  }

  sock_in.sin_family = PF_INET;
  sock_in.sin_port = htons(0);
  sock_in.sin_addr.s_addr = htonl(INADDR_ANY);

  iaddr.s_addr = INADDR_ANY; // use DEFAULT interface

  /* Configuracion del socket para multicast */
  if(setsockopt(sock, IPPROTO_IP, IP_MULTICAST_IF, &iaddr,sizeof(struct in_addr))==-1){
    printf("Error setsockopt, IP_MULTICAST_IF\n" ),exit(EXIT_FAILURE);
  }

  if(setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, &ttl,sizeof(unsigned char))==-1){

  }

  if(setsockopt(sock, IPPROTO_IP, IP_MULTICAST_LOOP,&one, sizeof(unsigned char))==-1){
    printf("Error setsockopt, IP_MULTICAST_LOOP\n" ),exit(EXIT_FAILURE);
  }

  sock_in.sin_family = PF_INET;
  sock_in.sin_addr.s_addr = inet_addr("226.0.0.1");
  sock_in.sin_port = htons(port);

  printf("Server Multicast port access: %d\n",htons(sock_in.sin_port));

}

void initSem(){
  if(sem_init(&*(a),0,1)==-1){
    printf("Error al abrir el primer semaforo :'v'\n");
    exit(EXIT_FAILURE);
  }
}

void tamFiles(int arg){
  FILE *file;
  int i,t;
  for(i=0;i<arg;i++){
    file=fopen((imgs+i)->name,"rb");
    if(file==NULL){
      exit(2);
    }
    t=0;
    while(fgetc(file)!=EOF)
      t++;
    (imgs+i)->tam=t;
    if((t/segmentos)>1495){
      (imgs+i)->segmentosMTU=1+(t/1495);
      (imgs+i)->mtuMax=1495;
    }else{
      (imgs+i)->mtuMax=1+(t/segmentos);
      (imgs+i)->segmentosMTU=segmentos;
    }
    fclose(file);
  }
}

int checkImages(int argc){
  int i;
  for(i=0;i<argc;i++){
    if((imgs+i)->type==0){
      printf("Error in file[%d]=%s\n",i,(imgs+i)->name);
      free(imgs);
      exit(1);
    }
  }
  return 0;
}

int isImageType(char *n){
  FILE *process;
  char *buff,*buffProcess;
  int i,j;
  buff=(char*)malloc(sizeof(char)*120);
  buffProcess=(char*)malloc(sizeof(char)*(tamJPEG+tamFile+strlen(n)+1));
  if(buff==NULL||buffProcess==NULL){
    free(buffProcess);free(buff);return -1;
  }
  for(i=0;i<(tamJPEG+tamFile+strlen(n));i++){
    *(buffProcess+i)=0;
  }
  memcpy(buffProcess+0,bufferFile+0,tamFile);
  memcpy(buffProcess+tamFile,n+0,strlen(n));
  for(j=0;j<4;j++){
    for(i=tamFile+strlen(n);i<tamFile+strlen(n)+tamJPEG;i++){
      *(buffProcess+i)=0;
    }
    memcpy(buffProcess+(tamFile+strlen(n)),(j==0)?(bufferJPEG+0):
      ((j==1)?(bufferJPG+0):((j==2)?(bufferPNG+0):(bufferGIF)))
      ,(j==0)?(tamJPEG):((j==1)?(tamJPG):((j==2)?(tamPNG):(tamGIF))));
    process=popen(buffProcess,"r");
    if(process==NULL){
      free(buffProcess);free(buff);return -2;
    }
    while(fgets(buff,120,process)){
      if(atoi(buff)>0){
        fclose(process);free(buff);free(buffProcess);return j+1;
      }
    }
    fclose(process);
  }
  free(buffProcess);
  free(buff);
  return 0;
}

void informationAbout(int argc){
  int i;
  for(i=0;i<argc;i++){
    printf("File name: %s\nSize file: %d bytes\nFormat file: %s\n"
    "Num of Segmets: %d\nMTU max for the file: %d\n\n",
    (imgs+i)->name,(imgs+i)->tam,((imgs+i)->type==1)?("JPEG"):
    (((imgs+i)->type==2)?("JPG"):(((imgs+i)->type==3)?("PNG"):("GIF"))),
    (imgs+i)->segmentosMTU,(imgs+i)->mtuMax);
  }
}
