#include "local_alloc.h"
#include <unistd.h>

static Header base;
static Header *free_p = NULL;
static const unsigned kMinAlloc = 1024;
static const unsigned kMaxBytes = 10240;

/* Applies more memory from system.
 *
 * @param size new memory's size
 * @return the new memory node's pointer
 */
static Header *MoreCore(unsigned size);

void *malloc(unsigned nbytes) {
  Header *p, *prev_p;
  unsigned nunits;

  if (nbytes > kMaxBytes) {
    return NULL;
  }

  nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

  if ((prev_p = free_p) == NULL) {
    base.s.ptr = free_p = prev_p = &base;
    base.s.size = 0;
  }

  for (p = prev_p->s.ptr; ; prev_p = p, p = p->s.ptr) {
    if (p->s.size >= nunits) {
      if (p->s.size == nunits) {
        prev_p->s.ptr = p->s.ptr;
      } else {
        p->s.size -= nunits;
        p += p->s.size;
        p->s.size = nunits;
      }

      free_p = prev_p;
      return (void *)(p + 1);
    }

    if (p == free_p) {
      if ((p = MoreCore(nunits)) == NULL) {
        return NULL;
      }
    }
  }
}

void *calloc(unsigned n, unsigned size) {
  unsigned i, nbytes;
  char *p, *q;

  nbytes = n *size;
  if ((p = q = malloc(nbytes)) != NULL) {
    for (i = 0; i < nbytes; ++i) {
      *p++ = 0;
    }
  }

  return q;
}

void free(void *ap) {
  Header *bp, *p;

  bp = (Header *)ap - 1;

  if (bp->s.size == 0) {
    return;
  }

  for (p = free_p; !(bp > p && bp < p->s.ptr); p = p->s.ptr) {
    if (p >= p->s.ptr && (bp > p || bp < p->s.ptr)) {
      break;
    }
  }

  if (bp + bp->s.size == p->s.ptr) {
    bp->s.size += p->s.ptr->s.size;
    bp->s.ptr = p->s.ptr->s.ptr;
  } else {
    bp->s.ptr = p->s.ptr;
  }

  if (p + p->s.size == bp) {
    p->s.size += bp->s.size;
    p->s.ptr = bp->s.ptr;
  } else {
    p->s.ptr = bp;
  }
  free_p = p;
}

void bfree(char *p, unsigned n) {
  Header *hp;

  if (n < sizeof(Header)) {
    return;
  }

  hp = (Header *) p;
  hp->s.size = n / sizeof(Header);
  free((void *)(hp + 1));
}

static Header *MoreCore(unsigned size) {
  char *cp;
  Header *up;

  if (size < kMinAlloc) {
    size = kMinAlloc;
  }

  cp = sbrk(size * sizeof(Header));

  if (cp == (char *) -1) {
    return NULL;
  }
  up = (Header *) cp;
  up->s.size = size;

  //inserts the new memory into the free block list
  free((void *)(up + 1));

  return free_p;
}
