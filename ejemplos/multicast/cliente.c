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

#define MAXBUFSIZE 65536

/* Flags for Shutdown the config interface
 * -> SHUT_RDWR: Apaga la recepcion y transmision de datos <==> 2
 * -> SHUT_RD: Apaga la recepcion de datos <==> 0
 * -> SHUT_WR: Apaga la transmision de datos <==> 1
 */

int main(int argc, char *argv[]){
  if(argc<2){
    printf("Error\nUsage: %s <PORT-MULTICAST_SERVER>\n",*argv),exit(EXIT_FAILURE);
  }
  /* Variables para la configuracion */
  int sock, status, socklen,port=atoi(*(argv+1));
  char buffer[MAXBUFSIZE];
  struct sockaddr_in saddr;
  struct in_addr iaddr;
  unsigned char ttl = 3;
  unsigned char one = 1;

  /* Modifica los bytes que contiene la estructura a 0 */
  memset(&saddr, 0, sizeof(struct sockaddr_in));
  memset(&iaddr, 0, sizeof(struct in_addr));

  /* Creacion del socket */
  if((sock=socket(PF_INET, SOCK_DGRAM, 0))<0){
    perror("Error creating socket"), exit(0);
  }
  /* Modificacion de la configuracion del cliente */
  saddr.sin_family = PF_INET;
  saddr.sin_port = htons(0); // Use the first free port
  saddr.sin_addr.s_addr = htonl(INADDR_ANY); // bind socket to any interface

  /* Punto terminal de conexion */
  if((status = bind(sock, (struct sockaddr *)&saddr, sizeof(struct sockaddr_in)))<0){
    perror("Error binding socket to interface"), exit(0);
  }


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

  /* Modificacion del destino de multicast */
  saddr.sin_family = PF_INET;
  saddr.sin_addr.s_addr = inet_addr("226.0.0.1");
  saddr.sin_port = htons(port);


  strcpy(buffer, "Hello world in multicast\n");

  socklen=sizeof(struct sockaddr_in);

  if((status=sendto(sock, buffer, strlen(buffer), 0,(struct sockaddr *)&saddr, socklen))==-1){
    printf("Error sendto\n"),exit(EXIT_FAILURE);
  }
  printf("Se envio %s\n",buffer);
  shutdown(sock, SHUT_RDWR);
  close(sock);
  return 0;
}
