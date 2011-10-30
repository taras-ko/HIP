#include <stdio.h>

#ifndef _CPLUSPLUS
  typedef int bool;
#define true 1
#define false 0
#endif

int getch(void); /* чтение символов с преобразованием */
void uSED(void); /* micro stream editor */

main()
{
	uSED();
	return 0;
}

void uSED(void)
{
	
	int nlch = 0; /* newline character */
	int c;
	bool lastspace=false;
	while (isspace(c = getch()) && c != EOF) /*пропускаем первые "белые" символы*/
		;
	ungetc(c,stdin);
	
	while ((c = getch()) != EOF) {
          switch(c) {
            case '\n':
              nlch++;
            case ' ':
              lastspace=true;
              break;
            case EOF:
              putchar('\n');
              break;
            default:
              if(lastspace)
                putchar(nlch>1?'\n':' ');
              putchar(c);
              lastspace=false;
              nlch=0;
              break;
          }
        }
	/* не забываем про последний символ :)*/
//<	putchar(EOF); здесь будет напечатано '\0xff'. Для закрытия потока используют fclose(file)
}

int getch(void)
{
  int c,nc;
  if((c=getchar())=='<')
    if((nc=getchar())=='>') {
      ungetc('\n',stdin);
      return '\n';
    }
    else ungetc(nc,stdin);
  if(isspace(c) && c!='\n') c=' ';
  return c;
}
