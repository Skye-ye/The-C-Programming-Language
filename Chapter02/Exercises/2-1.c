#include <float.h>
#include <limits.h>
#include <stdio.h>

int main() {
  // Integer types - Using limits.h
  printf("Using <limits.h>\n");
  printf("CHAR_MIN: %d\n", CHAR_MIN);
  printf("CHAR_MAX: %d\n", CHAR_MAX);
  printf("UCHAR_MAX: %u\n", UCHAR_MAX);
  printf("SHRT_MIN: %d\n", SHRT_MIN);
  printf("SHRT_MAX: %d\n", SHRT_MAX);
  printf("USHRT_MAX: %u\n", USHRT_MAX);
  printf("INT_MIN: %d\n", INT_MIN);
  printf("INT_MAX: %d\n", INT_MAX);
  printf("UINT_MAX: %u\n", UINT_MAX);
  printf("LONG_MIN: %ld\n", LONG_MIN);
  printf("LONG_MAX: %ld\n", LONG_MAX);
  printf("ULONG_MAX: %lu\n", ULONG_MAX);
  printf("LLONG_MIN: %lld\n", LLONG_MIN);
  printf("LLONG_MAX: %lld\n", LLONG_MAX);
  printf("ULLONG_MAX: %llu\n", ULLONG_MAX);

  // Floating point types - Using float.h
  printf("\nUsing <float.h>\n");
  printf("FLT_MIN: %e\n", FLT_MIN);
  printf("FLT_MAX: %e\n", FLT_MAX);
  printf("DBL_MIN: %e\n", DBL_MIN);
  printf("DBL_MAX: %e\n", DBL_MAX);
  printf("LDBL_MIN: %Le\n", LDBL_MIN);
  printf("LDBL_MAX: %Le\n", LDBL_MAX);

  // Integer types - Direct computation
  printf("\nComputed Directly\n");
  printf("Computed CHAR_MIN: %d\n", -(1 << (sizeof(char) * 8 - 1)));
  printf("Computed CHAR_MAX: %d\n", (1 << (sizeof(char) * 8 - 1)) - 1);
  printf("Computed UCHAR_MAX: %u\n", (unsigned char)~0);
  printf("Computed SHRT_MIN: %d\n", -(1 << (sizeof(short) * 8 - 1)));
  printf("Computed SHRT_MAX: %d\n", (1 << (sizeof(short) * 8 - 1)) - 1);
  printf("Computed USHRT_MAX: %u\n", (unsigned short)~0);
  printf("Computed INT_MIN: %d\n", -(1 << (sizeof(int) * 8 - 1)));
  printf("Computed INT_MAX: %d\n", (1 << (sizeof(int) * 8 - 1)) - 1);
  printf("Computed UINT_MAX: %u\n", (unsigned int)~0);
  printf("Computed LONG_MIN: %ld\n", -(1L << (sizeof(long) * 8 - 1)));
  printf("Computed LONG_MAX: %ld\n", (1L << (sizeof(long) * 8 - 1)) - 1);
  printf("Computed ULONG_MAX: %lu\n", (unsigned long)~0);
  printf("Computed LLONG_MIN: %lld\n", -(1LL << (sizeof(long long) * 8 - 1)));
  printf("Computed LLONG_MAX: %lld\n",
         (1LL << (sizeof(long long) * 8 - 1)) - 1);
  printf("Computed ULLONG_MAX: %llu\n", (unsigned long long)~0);

  return 0;
}
