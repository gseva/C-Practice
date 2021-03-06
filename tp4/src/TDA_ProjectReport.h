/**
 *
 */


#ifndef __TDA_PROJECT_REPORT_H_DEFINED__

  #define __TDA_PROJECT_REPORT_H_DEFINED__


  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>

  #include "TDA_AsanaClient.h"
  #include "TDA_ProjectDetail.h"
  #include "TDA_Project.h"
  #include "TDA_Task.h"
  #include "TDA_CsvFile.h"
  #include "TDA_ParsearEntrada.h"
  #include "Lista.h"
  #include "Index.h"

  #define percentage(a, b) ((b) ? ((double)a / b) * 100 : 0)

  typedef struct {

    Project* project;

    TDA_ProjectDetail* projectDetail;

    TListaSimple tasks;

    T_Index assigneeIndex, dueDateIndex, tagsIndex;

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
   * PRE: Report not initialized.
   * POST: Report initialized and empty.
   */
  int initializeReport(ProjectReport* report);

  /**
   * Destroys ProjectReport instance.
   *
   * PRE: Report initialized.
   * POST: Memory free.
   */
  int destroyReport(ProjectReport* report);

  /**
   * Reads the respective ADT and saves it in the report.
   *
   * PRE: Report and client initialized.
   * POST: Report saves reference to a created structure, non 0 value if error.
   */
  int readProject(AsanaClient* client, char* projectId, ProjectReport* report);
  int readProjectDetail(AsanaClient* client, char* pdId, ProjectReport* report);
  int readTask(AsanaClient* client, char* taskId, ProjectReport* report);

  /**
   * Returns number of tasks or sprints of the project.
   *
   * PRE: Report initialized, ProjectDetail readed.
   * POST: Returns count.
   */
  int getTasksCount(ProjectReport* report);
  int getSprintsCount(ProjectReport* report);

  /**
   * Returns number of finalized tasks of the project.
   *
   * PRE: Report initialized, ProjectDetail and Tasks readed.
   * POST: Returns count.
   */
  int getFinalizedTasksCount(ProjectReport* report);
  int getOverdueTasksCount(ProjectReport* report);
  int getBugsCount(ProjectReport* report);
  int getMilestonesCount(ProjectReport* report);
  int getPendingMilestonesCount(ProjectReport* report);
  int getOverdueFinalizedTasksCount(ProjectReport* report);

  /**
   * Returns an average of overdue days.
   *
   * PRE: Report initialized, ProjectDetail and Tasks readed.
   * POST: Returns average.
   */
  int getAverageOverdue(ProjectReport* report);

  /**
   * Creates a file named "project.txt", with project information.
   *
   * PRE: Report initialized, Project, ProjectDetail and Tasks readed.
   * POST: File created, filled and closed.
   */
  int makeTextOutput(ProjectReport* report, char* csvFileName);

  /**
   * Creates, fills and exports a csv file or prints output to stdout.
   *
   * PRE: Report initialized, Project, ProjectDetail and Tasks readed.
   * POST: File created, filled and closed.
   */
  int makeOutput(TListaSimple tasks, char* tasksFile);

  int getTaskById(ProjectReport* report, char* taskId, TDA_Task *t);

  /**
   * Case insentitive string compare.
   */
  int strcicmp(char const *a, char const *b);

  int fillIndexes(ProjectReport* report);
  T_Index* getIndexByKey(ProjectReport* report, char* key);
  void getInput(ProjectReport* report);
  int executeCommand(ProjectReport* report, Command* command);

#endif
