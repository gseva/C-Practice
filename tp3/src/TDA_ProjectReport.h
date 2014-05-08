/**
 *
 */


#ifndef __TDA_PROJECT_REPORT_H_DEFINED__

  #define __TDA_PROJECT_REPORT_H_DEFINED__


  #include <stdio.h>
  #include <stdio.h>

  #include "TDA_AsanaClient.h"
  #include "TDA_ProjectDetail.h"
  #include "TDA_Project.h"
  #include "TDA_Task.h"
  #include "Lista.h"


  typedef struct {

    Project* project;

    TDA_ProjectDetail* projectDetail;

    TListaSimple tasks;

  } ProjectReport;

  /**
   * Creates Project Report
   *
   * PRE:
   * POST: Returns 0 if report successfully created, !0 otherwise.
   */
  int createReport(char* key, char* projectId);

  /**
   * Initializes ProjectReport instance.
   *
   * PRE: report not initialized.
   * POST: report initialized and empty.
   */
  int initializeReport(ProjectReport* report);

  /**
   * Destroys ProjectReport instance.
   *
   * PRE: report initialized.
   * POST: memory free.
   */
  int destroyReport(ProjectReport* report);

  int readProject(AsanaClient* client, char* projectId, ProjectReport* report);
  int readProjectDetail(AsanaClient* client, char* pdId, ProjectReport* report);
  int readTask(AsanaClient* client, char* taskId, ProjectReport* report);

#endif
