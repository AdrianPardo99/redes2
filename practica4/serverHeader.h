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
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include "color.h"

#define segmentos 20
#define tramaTamMax 1500
#define tamThreads 5
#define bufferJPEG " | grep -o 'JPEG' | wc -c\0"
#define bufferJPG " | grep -o 'JPG' | wc -c\0"
#define bufferPNG " | grep -o 'PNG' | wc -c\0"
#define bufferGIF " | grep -o 'GIF' | wc -c\0"
#define bufferFile "file \0"
#define tamJPEG strlen(bufferJPEG)
#define tamJPG strlen(bufferJPG)
#define tamPNG strlen(bufferPNG)
#define tamGIF strlen(bufferGIF)
#define tamFile strlen(bufferFile)

typedef struct fileImage{
  char *name;
  int type,tam,segmentosMTU,mtuMax;
}images;

images *imgs;
pthread_t *threadID;
int *id;

typedef unsigned char trama;

sem_t *a;
int sock,status,port,bandera;
unsigned sinlen;
struct sockaddr_in sock_in;

void signalServer(int);
void sleepT(int);
void changeColor(int);
void printTrama(trama*,int);
void *threadFun(void*);
void sentData(trama*,int);
void onExit();
void initServerBroadcast();
void initServerMulticast();
void initSem();
void informationAbout(int);
void tamFiles(int);
int checkImages(int);
int isImageType(char*);
