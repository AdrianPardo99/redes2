#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define MAXBUF 65536

/* Flags for Shutdown the config interface
 * -> SHUT_RDWR: Apaga la recepcion y transmision de datos <==> 2
 * -> SHUT_RD: Apaga la recepcion de datos <==> 0
 * -> SHUT_WR: Apaga la transmision de datos <==> 1
 */

int main(int argc, char *argv[]) {
  /* Para el puerto que ocupe el servidor */
  if(argc<2){
    printf("Error\nUsage %s <PORT>",*argv);
    exit(EXIT_FAILURE);
  }
  /* Variables de la configuracion */
  int sock, status, sinlen,yes=1,port=atoi(*(argv+1));
  char *buffer;
  struct sockaddr_in sock_in;
  buffer=(char*)malloc(sizeof(char)*MAXBUF);

  sinlen = sizeof(struct sockaddr_in);
  memset(&sock_in, 0, sinlen);

  /* Creacion del socket de Broadcast */
  if((sock=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP))==-1){
    printf("Error open socket\n");
    exit(EXIT_FAILURE);
  }

  sock_in.sin_addr.s_addr=htonl(INADDR_ANY);
  sock_in.sin_port=htons(0);
  sock_in.sin_family=PF_INET;

  /* Creacion del punto final de conexion */
  if((status=bind(sock,(struct sockaddr *)&sock_in,sinlen))<0){
    printf("Error bind socket\n");
    exit(EXIT_FAILURE);
  }
  printf("Bind socket status: %d\n",status);

  /* Modificación de la configuracion de socket para el Broadcast */
  if((status=setsockopt(sock,SOL_SOCKET,SO_BROADCAST,&yes,sizeof(int)))==-1){
    printf("Error setsockopt\n");
    exit(EXIT_FAILURE);
  }
  /* Modificación del puerto al cual va llegar el mensaje del cliente */
  sock_in.sin_addr.s_addr=htonl(-1); /* send message to 255.255.255.255 */
  sock_in.sin_port = htons(port); /* port number */
  sock_in.sin_family = PF_INET;

  sprintf(buffer, "Ciao");
  /* Envio de datos al servidor (puede o no recibir el servidor) */
  if((status = sendto(sock,buffer,strlen(buffer),0,(struct sockaddr *)&sock_in,sinlen))==-1){
    printf("Error sendto\n");
    exit(EXIT_FAILURE);
  }
  printf("sendto Status = %d\nBuffer sendto: %s\n", status,buffer);
  shutdown(sock,SHUT_RDWR);
  close(sock);
  free(buffer);
  return 0;
}
