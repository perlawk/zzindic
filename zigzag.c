/*
  TTR: Technical Trading Rules

  Copyright (C) 2007-2013  Joshua M. Ulrich

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#define min(a,b) ((a) <= (b) ? (a) : (b))
#define max(a,b) ((a) >= (b) ? (a) : (b))

typedef long int integer;
typedef double doublereal;

/* Subroutine */ 
int zigzag(iha, ila, la, ch, pct, rtr, lex, zz)
	doublereal *iha, *ila;
	integer *la;
	doublereal *ch;
	integer *pct, *rtr, *lex;
	doublereal *zz;
{
	integer i1;
	doublereal d1, d2;

	/* Local variables */
	static doublereal emin, emax, lmin, lmax;
	static integer i;
	static doublereal refval, infval;
	static integer refpos, infpos, sig;

	/* Initialize values */

	/* Parameter adjustments */
	--zz;
	--ila;
	--iha;

	/* Function Body */
	refval = (iha[1] + ila[1]) / 2;
	infval = (iha[2] + ila[2]) / 2;
	refpos = 1;
	infpos = 2;
	sig = 0;

	/* Begin Loop */
	i1 = *la;
	for (i = 2; i <= i1; ++i) {
		if (*pct == 1) {
			/* If % change given (absolute move) */
			emin = infval * (1 - *ch);
			emax = infval * (*ch + 1);
		} else {
			/* If $ change given (only absolute moves make sense) */
			emin = infval - *ch;
			emax = infval + *ch;
		}

		/* Find local maximum and minimum */

		/* Computing MAX */
		d1 = infval, d2 = iha[i];
		lmax = max(d1,d2);
		/* Computing MIN */
		d1 = infval, d2 = ila[i];
		lmin = min(d1,d2);

		/* Find first trend */

		if (sig == 0) {
			if (*rtr == 1) {
				/* Retrace prior move */
				if (infval >= refval) {
					sig = 1;
				} else {
					sig = -1;
				}
			} else {
				/* Absolute move */
				if (lmin <= emin) {
					/* Confirmed Downtrend */
					sig = -1;
				}
				if (lmax >= emax) {
					/* Confirmed Uptrend */
					sig = 1;
				}
			}
		}

		/* Downtrend */

		if (sig == -1) {

			/* New Minimum */

			if (ila[i] == lmin) {
				/* Last Extreme */
				if (*lex == 1) {
					infval = ila[i];
					infpos = i;
				} else {
					/* First Extreme */
					if (ila[i] != ila[i - 1]) {
						infval = ila[i];
						infpos = i;
					}
				}
			}

			/* Retrace prior move */

			if (*rtr == 1) {
				emax = infval + (refval - infval) * *ch;
			}

			/* Trend Reversal */

			if (iha[i] >= emax) {
				zz[refpos] = refval;
				refval = infval;
				refpos = infpos;
				infval = iha[i];
				infpos = i;
				sig = 1;
				goto L10;
			}
		}

		/* Uptrend */

		if (sig == 1) {

			/* New Maximum */

			if (iha[i] == lmax) {
				/* Last Extreme */
				if (*lex == 1) {
					infval = iha[i];
					infpos = i;
				} else {
					/* First Extreme */
					if (iha[i] != iha[i - 1]) {
						infval = iha[i];
						infpos = i;
					}
				}
			}

			/* Retrace prior move */

			if (*rtr == 1) {
				emin = infval - (infval - refval) * *ch;
			}

			/* Trend Reversal */

			if (ila[i] <= emin) {
				zz[refpos] = refval;
				refval = infval;
				refpos = infpos;
				infval = ila[i];
				infpos = i;
				sig = -1;
				goto L10;
			}
		}
L10:
		;
	}

	/* Set final values */

	zz[refpos] = refval;
	zz[infpos] = infval;
} /* zigzag */

