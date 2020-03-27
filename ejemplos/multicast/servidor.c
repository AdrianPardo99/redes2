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

int main(int argc, char *argv[]) {
  if(argc<2){
    printf("Error\nUsage: %s <PORT>\n",*argv),exit(EXIT_FAILURE);
  }
  /* Variables para la configuración */
  int sock, status,port=atoi(*(argv+1));
  unsigned socklen;
  char *buffer;
  struct sockaddr_in saddr;
  struct ip_mreq imreq;
  buffer=(char*)malloc(sizeof(char)*MAXBUFSIZE);

  /* Modifica los bytes que contiene la estructura a 0 */
  memset(&saddr, 0, sizeof(struct sockaddr_in));
  memset(&imreq, 0, sizeof(struct ip_mreq));

  /* Creacion del socket */
  if((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP)) < 0){
    perror("Error creating socket"), exit(EXIT_FAILURE);
  }

  /* Modificacion de la estructura para el uso de multicast */
  saddr.sin_family = PF_INET;
  saddr.sin_port = htons(port);
  saddr.sin_addr.s_addr = htonl(INADDR_ANY);
  if((status = bind(sock, (struct sockaddr *)&saddr, sizeof(struct sockaddr_in)))<0){
    perror("Error binding socket to interface"), exit(EXIT_FAILURE);
  }

  /* Creacion del grupo de multicast en una direccion ya pre-establecida */
  imreq.imr_multiaddr.s_addr = inet_addr("226.0.0.1");
  imreq.imr_interface.s_addr = INADDR_ANY; // use DEFAULT interface

  /* Union al grupo de multicast */
  if((status=setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP,(const void *)&imreq, sizeof(struct ip_mreq)))==-1){
    printf("Error setsockopt\n"),exit(EXIT_FAILURE);
  }

  socklen = sizeof(struct sockaddr_in);

  /* Recepcion de paquetes del multicast */
  if((status=recvfrom(sock, buffer, MAXBUFSIZE, 0,(struct sockaddr *)&saddr, &socklen))==-1){
    printf("Error recvfrom\n"),exit(EXIT_FAILURE);
  }
  printf("Se recibio: %s\n",buffer);
  shutdown(sock,SHUT_RDWR);
  close(sock);
  free(buffer);
  return 0;
}
