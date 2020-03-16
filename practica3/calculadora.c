/*Developed by:
 * Valdez Bernal Maria Fernanda
 * Valdez Esquivel Melani Betsabee
 * Gonzalez Pardo Adrian
 * 3CV6 20-02
 * Last file update: 15-03-2020 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Calculadora manual de IPs a partir de parametros */
int isIP(char*);
void changeToArr(char*,void*);

int main(int argc, char *argv[]) {
  if(argc<3){
    printf("Error Usage %s <IP> <NETMASK>\n",*argv);
    exit(EXIT_FAILURE);
  }
  char *ip=argv[1],*netmask=argv[2],ipArr[4],netmaskArr[4];
  unsigned char ipUn[4],netmaskUn[4],host[4],final[4];
  int i;
  FILE *out;
  if(isIP(ip) && isIP(netmask)){
    changeToArr(ip,(void*)&ipArr);
    //printf("Array IP: %d.%d.%d.%d\n",(256+*(ipArr))%256,(256+*(ipArr+1))%256,(256+*(ipArr+2))%256,(256+*(ipArr+3))%256);
    changeToArr(netmask,(void*)&netmaskArr);
    //printf("Array NETMASK: %d.%d.%d.%d\n",(256+*(netmaskArr))%256,(256+*(netmaskArr+1))%256,(256+*(netmaskArr+2))%256,(256+*(netmaskArr+3))%256);
    for(i=0;i<4;i++){
      *(ipUn+i)=(256+*(ipArr+i))%256;
      *(netmaskUn+i)=(256+*(netmaskArr+i))%256;
      *(host+i)=*(ipUn+i)&*(netmaskUn+i);
      *(final+i)=*(ipUn+i)| ~*(netmaskUn+i);
    }
    /*printf("Id de red: ");
    for(i=0;i<4;i++){
      printf("%d",*(host+i));
      if(i<3){
        printf(".");
      }
    }
    printf("\nRed de broadcast: ");
    for(i=0;i<4;i++){
      printf("%d",*(final+i));
      if(i<3){
        printf(".");
      }
    }
    printf("\n");*/
    *(host+3)+=1;
    out=fopen("ips.txt","w");
    if(out==NULL){
      printf("Error al abrir el flujo\n");
      exit(EXIT_FAILURE);
    }
    while(memcmp(final+0,host+0,4)){
      fprintf(out,"%d.%d.%d.%d\n",*(host),*(host+1),*(host+2),*(host+3));
      if(*(host+3)==0xff){
        *(host+3)=0;
        if(*(host+2)==0xff){
          *(host+2)=0;
          if(*(host+1)==0xff){
            *(host+1)=0;
            *host=+1;
          }else{
            *(host+1)+=1;
          }
        }else{
          *(host+2)+=1;
        }
      }else{
        *(host+3)+=1;
      }
    }
    fclose(out);
  }
  return 0;
}

int isIP(char *x){
  int i,ban=0;
  for(i=0;i<strlen(x);i++){
    if(*(x+i)=='.'){
      ban++;
    }
  }
  if(ban==3)
    return 1;
  return 0;
}

void changeToArr(char *x, void *dst){
  int i,cen=0,coun=0,c=0;
  char *dest=(char*)dst;
  for(i=0;i<strlen(x);i++){
    if(*(x+i)=='.'){
      *(dest+coun)=cen;
      cen=0;
      coun++;
      continue;
    }
    cen=(cen*10)+((*(x+i))-'0');
  }
  *(dest+coun)=cen;
}
