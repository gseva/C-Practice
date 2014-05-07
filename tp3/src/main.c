/*
 *
 */


#include "TDA_ProjectReport.h"
#include "TDA_CsvFile.h"


int main(int argc, char* argv[]) {
  char* asanaKey = malloc(30);
  strcpy(asanaKey, "3fmVdZTk.dUwa5vc1oMyKSYOao7fOApx");
  createReport(asanaKey, "some project id");
  free(asanaKey);
  return 0;
}
