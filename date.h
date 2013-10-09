#ifndef _DATE_H_INCLUDED_
#define _DATE_H_INCLUDED_

/* changes to date.h */ /* do not rely on those, as Joe won't get your date.h!!!! */
#include <stdbool.h>
int digest_int(char* datestr_ptr, int length);
#define VALIDATE_INPUT
/* end of changes to date.h */


typedef struct date Date;

/*
 * date_create creates a Date structure from `datestr`
 * `datestr' is expected to be of the form "dd/mm/yyyy"
 * returns pointer to Date structure if successful,
 *         NULL if not (syntax error)
 */
Date* date_create(char *datestr);

/*
 * date_duplicate creates a duplicate of `d'
 * returns pointer to new Date structure if successful,
 *         NULL if not (memory allocation failure)
 */
Date* date_duplicate(Date *d);

/*
 * date_compare compares two dates, returning <0, 0, >0 if
 * date1<date2, date1==date2, date1>date2, respectively
 */
int date_compare(Date *date1, Date *date2);

/*
 * date_destroy returns any storage associated with `d' to the system
 */
void date_destroy(Date *d);

#endif /* _DATE_H_INCLUDED_ */
