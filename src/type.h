#ifndef MCSTRING_TYPE_H
#define MCSTRING_TYPE_H

#include <mcstring/mcstring.h>

struct mcstring {
  size_t size;
  unsigned int refcount;
  const mcchar *data;
};


#endif /* MCSTRING_TYPE_H */
