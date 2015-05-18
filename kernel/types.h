#ifndef TYPES_H
#define TYPES_H

typedef unsigned char   u8;
typedef unsigned short  u16;
typedef unsigned int    u32;

#define udelay(v)				\
do {						\
	int i = v, j;				\
	while (i--)				\
		for (j = 0; j < 100; j++)	\
			;			\
} while (0)


#endif /* TYPES_H */
