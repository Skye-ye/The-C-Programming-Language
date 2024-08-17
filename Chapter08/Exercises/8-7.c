#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define NALLOC 1024
#define MIN_ALLOC_SIZE 16
#define MAX_ALLOC_SIZE ((size_t) - 1 - sizeof(Header))

typedef long Align;

union header {
  struct {
    union header *ptr;
    unsigned size;
  } s;
  Align x;
};

typedef union header Header;

static Header base;
static Header *freep = NULL;

static Header *morecore(unsigned nu);
void *malloc(unsigned nbytes);
void free(void *ap);
void *calloc(unsigned n, unsigned size);

void *malloc(unsigned nbytes) {
  Header *p, *prevp;
  unsigned nunits;

  if (nbytes == 0) {
    errno = EINVAL;
    return NULL;
  }

  if (nbytes > MAX_ALLOC_SIZE) {
    errno = ENOMEM;
    return NULL;
  }

  nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

  if (nunits < MIN_ALLOC_SIZE / sizeof(Header)) {
    nunits = MIN_ALLOC_SIZE / sizeof(Header);
  }

  if ((prevp = freep) == NULL) {
    base.s.ptr = freep = prevp = &base;
    base.s.size = 0;
  }

  for (p = prevp->s.ptr;; prevp = p, p = p->s.ptr) {
    if (p->s.size >= nunits) {
      if (p->s.size == nunits) {
        prevp->s.ptr = p->s.ptr;
      } else {
        p->s.size -= nunits;
        p += p->s.size;
        p->s.size = nunits;
      }
      freep = prevp;
      return (void *)(p + 1);
    }
    if (p == freep) {
      if ((p = morecore(nunits)) == NULL) {
        return NULL;
      }
    }
  }
}

static Header *morecore(unsigned nu) {
  char *cp;
  Header *up;

  if (nu < NALLOC) {
    nu = NALLOC;
  }

  cp = sbrk(nu * sizeof(Header));
  if (cp == (char *)-1) {
    return NULL;
  }

  up = (Header *)cp;
  up->s.size = nu;
  free((void *)(up + 1));
  return freep;
}

void free(void *ap) {
  Header *bp, *p;

  if (ap == NULL) return;

  bp = (Header *)ap - 1;

  if (bp->s.size == 0 || bp->s.size > MAX_ALLOC_SIZE) {
    fprintf(stderr, "free: invalid size\n");
    errno = EINVAL;
    return;
  }

  if ((unsigned)bp % sizeof(Align) != 0) {
    fprintf(stderr, "free: misaligned pointer\n");
    errno = EINVAL;
    return;
  }

  for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) {
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

  freep = p;
}

void *calloc(unsigned n, unsigned size) {
  void *ptr;
  unsigned total_size;

  if (n && size > SIZE_MAX / n) {
    return NULL;
  }

  total_size = n * size;

  ptr = malloc(total_size);

  if (ptr != NULL) {
    memset(ptr, 0, total_size);
  }

  return ptr;
}