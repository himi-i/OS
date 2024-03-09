#include "types.h"
#include "stat.h"
#include "user.h"
int lines;
char buf[512];
void xv6_strncpy(char *dest, const char *src, int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
        if (src[i] == '\0')
            break;
    }
}
void htac(int fd)
{
  int n;
  int count = 0;
  int line_len = 0;
  char **arr;
arr = (char**)malloc(sizeof(char*)*100);
       while((n = read(fd, &buf[line_len], 1) > 0)){
               if(buf[line_len] == '\n'){
                       arr[count] = (char *)malloc(sizeof(char)*(line_len));
                       xv6_strncpy(arr[count], buf, line_len);
                       count++;
                       line_len = 0;
               }
               else{
                       line_len++;
               }
       }
  if (n < 0)
  {
    printf(1, "cat: read error\n");
    exit();
  }
  count = count-1; 
  for(int i = lines; i > 0; i--){
    printf(1, "%s\n", arr[count]);
    count--;
      }
 for(int i = 0; i < count; i++){
         free(arr[i]);
        }
 free(arr);
 }
int main(int argc, char *argv[])
{
  int fd, i;
  if (argc <= 2)
  {
    htac(0);
    exit();
  }
  lines = atoi(argv[1]);
  for (i = 2; i < argc; i++)
  {
    if ((fd = open(argv[i], 0)) < 0)
    {
      printf(1, "cat: cannot open %s\n", argv[i]);
      exit();
    }
    htac(fd);
    close(fd);
  }
  exit();
}

