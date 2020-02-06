all: stat
	gcc main.c stat.a -o out # Note that all static libraries should be present after the sources
stat: stat_a.o stat_b.o
	ar scr stat.a stat_a.o stat_b.o 
stat_a.o:stat_a.c
	gcc -c stat_a.c -o stat_a.o
stat_b.o:stat_b.c
	gcc -c stat_b.c -o stat_b.o
clean:
	rm *.o out *.a
