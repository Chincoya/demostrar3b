#include<stdio.h>
#include<string.h>

void MSB(int * c);
void LSB(int * c);

int main(int argc, char *argv[]){
  if(argc<3)return 1;
  if(argc>3)return 1;
  int c, r, g, b, w, h, s;
  unsigned char ch;
  char *m = "-m";
  char *l = "-l";
  
  FILE *stream = fopen(argv[2], "rb");
  FILE *exit = fopen("Salida.txt", "wb");
  FILE *modified = fopen("modif.bmp", "wb");
  if(strcmp(argv[1],m)==0){
    modified = fopen("mostSig.bmp", "wb");
  }else if(strcmp(argv[1],l)==0){
    modified = fopen("lessSig.bmp", "wb");
  }else{
    printf("Wrong option!\nThe valid options are:\n   -m For most significant bits\n   -l For less significant bits\n\nAdieu!");
    return 1;
  }
  
  if(stream == (FILE*)0||exit == (FILE*)0)return 1;
  for(int i = 0; i<54; i++){
    c = fgetc(stream);
    ch = c;
    fprintf(exit,"%d ", c);
    fprintf(modified, "%c", ch);
    if(i==18)w=c;
    if(i==22)h=c;
  }
  fprintf(exit, "\n ---------------------------- \n");
  s = w*h;
  printf("%d", s);
  for(int i = 0, k =1; i<s; i++, k++){
    if(k == w){
      //Aquí va el padding. Hasta ahora no se ha usado pues las imagenes
      //usadas tienen tamaños múltiplos de cuatro c:
      //fprintf(exit,"\n");
      //fprintf(modified, "\n");
      k=1;
    }
    b = fgetc(stream);
    g = fgetc(stream);
    r = fgetc(stream);
    fprintf(exit,"%d ",b);
    fprintf(exit,"%d ",g);
    fprintf(exit,"%d ",r);
    if(strcmp(argv[1],m)==0){
      MSB(&b);
      MSB(&g);
      MSB(&r);
    }
    if(strcmp(argv[1],l)==0){
      LSB(&b);
      LSB(&g);
      LSB(&r);
    }
    fprintf(modified,"%c",b);
    fprintf(modified,"%c",g);
    fprintf(modified,"%c",r);
    fprintf(exit, "- ");
  }
  fclose(stream);
  fclose(exit);
  fclose(modified);
}

void MSB(int * c){
  int cc = (int)*c;
  *c = 0;
  if(cc>127)*c = 255;
}

void LSB(int * c){
  int cc = (int)*c;
  *c = 0;
  if(cc%2==1)*c = 255;
}
