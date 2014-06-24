
#include "Index.h"

typedef struct _item {
  void *key, *value;
  size_t key_size, value_size;
} Item;

int copy_item(void* destino, const void* origen) {
  Item* to = (Item*) destino; Item* from = (Item*) origen;
  to->key = malloc(from->key_size);
  to->value = malloc(from->value_size);
  if (to->key && to->value) {
    to->key_size = from->key_size;
    to->value_size = from->value_size;
    memcpy(to->key, from->key, from->key_size);
    memcpy(to->value, from->value, from->value_size);
    return 0;
  }
  free(to->key);
  free(to->value);
  return -1;
}

void destroy_item(void* item) {
  Item* aux = (Item*) item;
  free(aux->key);
  free(aux->value);
  free(aux);
}

int idx_create(T_Index* i, size_t key_size, size_t value_size, F_Cmp keycmp,
               F_Clone key_clone, F_Clone value_clone, F_Destroy key_destroy,
               F_Destroy value_destroy) {
  AB_Crear(&(i->data), sizeof(Item), copy_item, destroy_item);
  i->key_size = key_size; i->value_size = value_size;

  i->keycmp = keycmp;
  i->key_clone = key_clone;
  i->value_clone = value_clone;
  i->key_destroy = key_destroy;
  i->value_destroy = value_destroy;
  return 0;
}

int idx_destroy(T_Index* i) {
  AB_Vaciar(&(i->data));
  return 0;
}

int idx_put(T_Index* i, const void* key, const void* value) {
  Item item, *aux = malloc(sizeof(Item)); int mov;
  item.key = malloc(i->key_size);
  item.value = malloc(i->value_size);
  item.key_size = i->key_size;
  item.value_size = i->value_size;
  i->key_clone(item.key, key);
  i->value_clone(item.value, value);

  if (AB_MoverCte(&(i->data), RAIZ)) {
    do {
      AB_ElemCte(i->data, aux);
      if (i->keycmp(aux->key, key) > 0) {  // aux.key > key
        mov = IZQ;
      } else {
        mov = DER;
      }
    } while (AB_MoverCte(&(i->data), mov));
    AB_Insertar(&(i->data), mov, &item);
  } else {
    AB_Insertar(&(i->data), RAIZ, &item);
  }
  return 0;
}

int idx_get(T_Index* i, const void* key, TListaSimple* values) {
  Item aux; int mov, cmp;
  if (AB_Vacio(i->data)) {
    return -1;
  } else {
    AB_MoverCte(&(i->data), RAIZ);
    do {
      AB_ElemCte(i->data, &aux);
      cmp = i->keycmp(aux.key, key);
      if (cmp > 0) {  // aux.key > key
        mov = IZQ;
      } else {
        if (!cmp) {
          if (L_Vacia(*values)) {
            L_Insertar_Cte(values, L_Primero, aux.value);
          } else {
            L_Insertar_Cte(values, L_Siguiente, aux.value);
          }
        }
        mov = DER;
      }
    } while (AB_MoverCte(&(i->data), mov));
  }
  return 0;
}


int _llamada_recursiva(TAB a, int mov, F_Operate operate, void* shared_data, int break_value) {

  Item aux;

  if (AB_MoverCte(&a, mov)) {
    if (_llamada_recursiva(a, IZQ, operate, shared_data, break_value))
      return 1;
    AB_ElemCte(a, &aux);
    if (operate(aux.value, shared_data) == break_value) {
      return 1;
    }
    if (_llamada_recursiva(a, DER, operate, shared_data, break_value))
      return 1;
  }
  return 0;
}

int idx_go_through(T_Index* i, F_Operate operate, void* shared_data, int break_value) {

  if (AB_Vacio(i->data)) return -1;

  AB_MoverCte(&(i->data), RAIZ);
  return _llamada_recursiva(i->data, RAIZ, operate, shared_data, break_value);
}
