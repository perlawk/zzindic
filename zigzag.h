/*     Zig Zig */

/*     iha   : input array of high prices */
/*     ila   : input array of low prices */
/*     la    : length of arrays */
/*     ch    : minimum change to cause a zig/ */
/*     pct   : logical, % (1) or $ (0) change */
/*     rtr   : logical, retrace (1) or absolute (0) change */
/*     lex   : logical, last (1) or first (0) extreme value */
/*     zz    : Zig/Zag vector */

#ifndef _ZIGZAG_H
#define _ZIGZAG_H

#define tp(n) printf("%d\n", (n));


typedef long int integer;
typedef double doublereal;

int zigzag(
	doublereal *iha, doublereal *ila,
	integer *la,
	doublereal *ch,
	integer *pct,  integer *rtr, integer *lex,
	doublereal *zzv);

#endif
