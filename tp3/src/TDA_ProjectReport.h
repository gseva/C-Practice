/**
 *
 */


#ifndef __TDA_PROJECT_REPORT_H_DEFINED__

  #define __TDA_PROJECT_REPORT_H_DEFINED__


  #include <stdio.h>
  #include <stdio.h>

  #include "TDA_AsanaClient.h"
  #include "TDA_Project.h"
  #include "TDA_Task.h"
  #include "Lista.h"


  typedef struct {

    TListaSimple tasks;

  } ProjectReport;


  int createReport(char* key, char* projectId);


#endif
