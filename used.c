#include <stdio.h>
#define MAXLINE 1000

main()
{
	void uSED(void); /* micro stream editor */

	uSED();
	return 0;
}


extern int reg; /* reg используется ниже в getch() */
#define ungetch(c) reg = c /* возврат символа в поток ввода*/

void uSED(void)
{
	int getch(void);

	int nlch = 0; /* newline character */
	int c, nc; /* i. e. next char */
	
	while (isspace(c = getch()) && c != EOF) /*пропускаем первые "белые" символы*/
		;
	ungetch(c);
	
	while ((c = getch()) != EOF) {
		if (!isspace(c)) {
			/* проверка на случай "<>" */
			if (c == '<') { 
				if ((nc = getch()) == '>') {
					putchar('\n'), putchar('\n');
					continue;
				}
				else {
					putchar(c);
					ungetch(nc);
					continue;
				}
			}
			/* обычная обработка непустых символов */
			putchar(c);
			continue;
		}
		/* обработка "белых" символов */
		while (isspace(c = getch()) && c != EOF) {
			if (c == '\n') 
				nlch++;
		}
		ungetch(c);
		if (nlch > 1 || c == EOF) {
			putchar('\n'), putchar ('\n');
			nlch = 0;
		}
		else 
			putchar(' ');
	}
	/* не забываем про последний символ :)*/
//<	putchar(EOF);
}

#define EMPTY -2 /* т.е. ПУСТ. Состояние регистра reg. */ 
int reg = EMPTY; /* регистр, который эмулирует возврат символа в поток ввода */

int getch(void)
{
	if (reg != EMPTY) {
		int x = reg;
		reg = EMPTY;

		return x;
	}
	return getchar();
}
