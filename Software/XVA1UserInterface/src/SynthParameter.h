#include "ParameterType.h"

struct SynthParameter {
  ParameterType type = NUMERIC;
  char name[20];
  int number;
  int number2 = -1;
  int min = 0;
  int max = 255;
  char *descriptions[25];
};
