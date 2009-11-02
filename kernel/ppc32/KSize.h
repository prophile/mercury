#ifndef __KSIZE__
#define __KSIZE__

typedef unsigned long KWord;
typedef long KSignedWord;

const KWord KWordSize = 32;

#define KWordCTZ __builtin_ctzl
#define KWordCLZ __builtin_clzl
#define KWordFFS __builtin_ffsl
#define KWordPopcount __builtin_popcountl
#define KWordParity __builtin_parityl

extern const void* KHeapBase;

#endif
