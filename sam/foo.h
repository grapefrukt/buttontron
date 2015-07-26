#include "sam.h"
#include "reciter.h"

void bar() {
  char input[]={"/HAALAOAO MAYN NAAMAEAE IHSTT SAEBAASTTIHAAN \x9b\x9b\0"};
  //EnableDebug();
  SetInput(input);
  SAMMain();
  //WriteWav(wavfilename, GetBuffer(), GetBufferLength()/50);
}

