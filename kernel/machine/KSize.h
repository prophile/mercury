#ifndef __KSIZE__
#define __KSIZE__

typedef unsigned long KWord;
typedef long KSignedWord;

#ifdef __LP64__
const KWord KWordSize = 64;
#else
const KWord KWordSize = 32;
#endif

#define KWordCTZ __builtin_ctzl
#define KWordCLZ __builtin_clzl
#define KWordFFS __builtin_ffsl
#define KWordPopcount __builtin_popcountl
#define KWordParity __builtin_parityl

#endif
