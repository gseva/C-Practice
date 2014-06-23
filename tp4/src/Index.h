
#ifndef __T_INDEX_H_DEFINED__

  #define __T_INDEX_H_DEFINED__

  #include <stdio.h>
  #include <stdlib.h>
  #include "AB.h"
  #include "Lista.h"

  typedef int (*F_Cmp) (const void*, const void*);
  typedef int (*F_Clone) (void* destination, const void* source);
  typedef int (*F_Destroy) (void*);
  typedef int (*F_Operate) (void* value, void* shared_data);

  typedef struct _index {
    TAB data;

    size_t key_size, value_size;

    F_Cmp keycmp;
    F_Clone key_clone, value_clone;
    F_Destroy key_destroy, value_destroy;

  } T_Index;

  int idx_create(T_Index* i, size_t key_size, size_t value_size, F_Cmp keycmp,
                 F_Clone key_clone, F_Clone value_clone, F_Destroy key_destroy, F_Destroy value_destroy);
  int idx_destroy(T_Index* i);
  int idx_put(T_Index* i, const void* key, const void* value);
  int idx_get(T_Index* i, const void* key, TListaSimple* values);
  int idx_go_through(T_Index* i, F_Operate operate, void* shared_data, int break_value);

#endif
