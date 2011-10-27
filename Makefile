	CFLAGS=-g
$< :
	gcc -o $< $<.c -g -lm
clean :
	find . -path './*' ! -path './.git*' -prune \
			-type f ! -name shmake -executable -print | xargs rm -f
