#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  //add ".counts\0" to the file name (+8)
  char * outputName = malloc((strlen(inputName) + 8) * sizeof(*outputName));
  strcpy(outputName, inputName);
  strcat(outputName, ".counts");
  return outputName;
}
