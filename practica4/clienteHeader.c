/* Developed by:
 * Valdez Bernal Maria Fernanda
 * Valdez Esquivel Melani Betsabee
 * Gonzalez Pardo Adrian
 * 3CV6 20-02
 * Last file update: 15-04-2020 */

#include "clienteHeader.h"

void changeColor(int des){
  switch (des) {
    case 0:
      printf("%s",BBLU);
    break;
    case 1:
      printf("%s",BYEL);
    break;
    case 2:
      printf("%s",BGRN);
    break;
    case 3:
    printf("%s",BCYN);
    break;
    case 4:
      printf("%s",BMAG);
    break;
    default:
      printf("%s",KNRM);
  }
}

void printTrama(trama *tr,int size){
  int i;
  for(i=0;i<size;i++){
    (i==0)?(changeColor(0)):((i>0&&i<=2)?(changeColor(1)):
      ((i>=3&&i<=4)?(changeColor(2)):((i>=5&&i<=6)?(changeColor(3)):
      (changeColor(4)))));
    printf(" %.2X ",*(tr+i));
    if((i+1)%16==0){
      printf("\n");
    }
  }
  changeColor(-1);
  printf("\n");
}

trama *reciveClient(){
  trama *datos;
  datos=(trama*)malloc(sizeof(trama)*tramaTamMax);
  if(datos==NULL){
    printf("Error allocating memory for datos\n");
    exit(EXIT_FAILURE);
  }
  if(recvfrom(sock,datos,tramaTamMax,0,(struct sockaddr*)&sock_in,&sinlen)==-1){
    printf("Error recvfrom\n"),exit(EXIT_FAILURE);
  }
  return datos;
}

void onExit(){
  shutdown(sock,SHUT_RDWR);
  close(sock);
}


int checkPosition(int n,int tam){
  return (n-1)*(tam-5);
}


void initClienteBroadcast(){
  sinlen=sizeof(struct sockaddr_in);
  memset(&sock_in,0,sinlen);

  if((sock=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP))==-1){
    printf("Error open socket\n");
    exit(EXIT_FAILURE);
  }

  sock_in.sin_addr.s_addr=htonl(INADDR_ANY);
  sock_in.sin_port=htons(port);
  sock_in.sin_family=PF_INET;

  if((status=bind(sock,(struct sockaddr *)&sock_in,sinlen))<0){
    printf("Error bind socket\n");
    exit(EXIT_FAILURE);
  }

  if((status=getsockname(sock,(struct sockaddr *)&sock_in,&sinlen))==-1){
    printf("Error getsockname\n");
    exit(EXIT_FAILURE);
  }
  printf("Client Broadcast by port: %d\n",htons(sock_in.sin_port));

}

void initClienteMulticast(){
  sinlen=sizeof(struct sockaddr_in);
  memset(&sock_in,0,sinlen);
  memset(&sock_in, 0, sizeof(struct sockaddr_in));
  memset(&imreq, 0, sizeof(struct ip_mreq));

  if((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP)) < 0){
    perror("Error creating socket"), exit(EXIT_FAILURE);
  }

  sock_in.sin_family = PF_INET;
  sock_in.sin_port = htons(port);
  sock_in.sin_addr.s_addr = htonl(INADDR_ANY);
  if((status = bind(sock, (struct sockaddr *)&sock_in, sizeof(struct sockaddr_in)))<0){
    perror("Error binding socket to interface"), exit(EXIT_FAILURE);
  }

  imreq.imr_multiaddr.s_addr = inet_addr("226.0.0.1");
  imreq.imr_interface.s_addr = INADDR_ANY;

  if((status=setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP,(const void *)&imreq, sizeof(struct ip_mreq)))==-1){
    printf("Error setsockopt\n"),exit(EXIT_FAILURE);
  }
  printf("Client Multicast by port: %d\n",htons(sock_in.sin_port));
}

void *hiloCliente(void *arg){
  int id=*((int*)arg),ban=1,who,format,tam=1;
  trama *buffAux;
  while(ban){
    buffAux=reciveClient();
    who=(*(buffAux)>>4)&0x0f;
    if(who==(id+1)){
      tam=*(buffAux+5);
      tam=(tam<<8)+*(buffAux+6);
      printTrama(buffAux,tam);
      ban=0;
    }
  }
  format=(*(buffAux))&0x0f;
  (imgs+id)->name=((id+1)==1)?(file1):
    (((id+1)==2)?(file2):(((id+1)==3)?(file3):
    (((id+1)==4)?(file4):(file5))));
  (imgs+id)->format=(format==1)?(nameJPEG):
    ((format==2)?(nameJPG):((format==3)?(namePNG):(nameGIF)));
  (imgs+id)->totalSegmentos=((*(buffAux+3)<<8))+((*(buffAux+4)));
  printf("Imagen a construir: %s%s\n"
    "Numero total de tramas: %d\nPeso Aproximado de: %d bytes\n\n"
    ,(imgs+id)->name,(imgs+id)->format,(imgs+id)->totalSegmentos,
    (tam));
  exit(0);
}
