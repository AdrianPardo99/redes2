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
  /*  */
  int sock, status;
  unsigned sinlen;
  char *buffer;
  struct sockaddr_in sock_in;

  buffer=(char*)malloc(sizeof(char)*MAXBUF);

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
  printf("Bind socket status: %d\n",status);

  if((status=getsockname(sock,(struct sockaddr *)&sock_in,&sinlen))==-1){
    printf("Error getsockname\n");
    exit(EXIT_FAILURE);
  }
  printf("Sock port usage: %d\n",htons(sock_in.sin_port));
  memset(buffer,0,MAXBUF);

  if((status=recvfrom(sock,buffer,MAXBUF,0,(struct sockaddr *)&sock_in,&sinlen))==-1){
    printf("Error recvfrom\n");
    exit(EXIT_FAILURE);
  }
  printf("Status recvfrom: %d\nMessage: %s\n",status,buffer);

  free(buffer);
  shutdown(sock,SHUT_RDWR);
  close(sock);
  return 0;
}
