/* Developed by:
 * Valdez Bernal Maria Fernanda
 * Valdez Esquivel Melani Betsabee
 * Gonzalez Pardo Adrian
 * 3CV6 20-02
 * Last file update: 15-04-2020 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>
#include "color.h"

#define segmentos 20
#define tramaTamMax 1500
#define tamThreads 5
#define nameJPEG ".jpeg\0"
#define nameJPG ".jpg\0"
#define namePNG ".png\0"
#define nameGIF ".gig\0"
#define file1 "1\0"
#define file2 "2\0"
#define file3 "3\0"
#define file4 "4\0"
#define file5 "5\0"

typedef struct archivo{
  const char *name,*format;
  int *arrSegmentos,totalSegmentos;
}imagen;


typedef unsigned char trama;
imagen *imgs;
trama **buffer;
pthread_t *threadID;
int *id,sock,status,port;
unsigned sinlen;
struct sockaddr_in sock_in;
struct ip_mreq imreq;


void changeColor(int);
void printTrama(trama*,int);
trama *reciveClient();
void onExit();
int checkPosition(int,int);
void initClienteBroadcast();
void initClienteMulticast();
void *hiloCliente(void*);
