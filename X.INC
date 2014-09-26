/*
_____________________________________________________________
Object connector
Philip R Brenan,  Transcendental Automation,  1992,  800-FOR-PHIL
_____________________________________________________________
*/

/*
**      Last revision - Serge Kovalyov, February 1993.
**      Tree extract routine prototype & macros added.
*/

#ifndef X_INC
#define X_INC
#define x_vector_show 32
/*
_____________________________________________________________
Object connectors
_____________________________________________________________
*/
typedef  struct XL
 {struct Xl *f, *l;
  void      *d;
 } XL;

typedef  struct Xl
 {struct Xl *n, *p;
  struct XL *u;
  void      *d;
 } Xl;

typedef  struct XT
 {struct Xt *td;
  void      *d;
 } XT;

typedef  struct Xt
 {struct Xt *tl, *tr, *tu;
  struct XT *u;
  void      *d;
  char      *k;
  int        color:1;
 } Xt;

typedef  struct XV
 {long   count;
  long   k;
  void  *d[x_vector_show];
 } XV;
/*
_____________________________________________________________
Object connection procedure declarations
_____________________________________________________________
*/
long  x_list_count      (XL *p);
long  x_tree_count      (XT *p);

Xt   *x_tree_do_first   (XT *p, void **r);
Xt   *x_tree_do_last    (XT *p, void **r);
Xt   *x_tree_do_next    (Xt *q, void **r);
Xt   *x_tree_do_prev    (Xt *q, void **r);

void *x_tree_get        (XT *p, char *k);
void *x_tree_get_n      (XT *p, char *k, int n);
void *x_tree_get_cmp    (XT *p, void *k, int (*cmp)());
void *x_tree_get_int    (XT *p, char *k);

Xt   *x_tree_ext_balance(Xt *q);

/* Prototype for x_tree_print added */

void  x_tree_print      (Xt *p, int d);

void *x_vector_get      (XV *p, char *k);
void *x_vector_get_int  (XV *p, char *k);

int   x_tree_put        (XT *p, Xt *q);
int   x_tree_put_n      (XT *p, Xt *q,   int n);
int   x_tree_put_cmp    (XT *p, Xt *q,   int (*cmp)());
int   x_tree_put_int    (XT *p, Xt *q);
void  x_tree_put_balance(XT *p, Xt *q);
void  x_rotate_left     (XT *p, Xt *q);
void  x_rotate_right    (XT *p, Xt *q);

int   x_cmp_tree_int    (XT *a, XT *b);

void *x_list_copy       (XL *p, void *a, long size);
void *x_tree_copy       (XT *p, void *a, long size);
XV   *x_list_vector     (XL *p, XV *V,   long d);
XV   *x_tree_vector     (XT *p, XV *V,   long d, long k);

void  x_vector_relocate (XV **V, long r);

/* There, prototypes for x_*_do_all_* */

Xt   *x_tree_do_all_first(XT *q, void **r, long O);
Xt   *x_tree_do_all_last(XT *q, void **r, long O);
Xt   *x_tree_do_all_next(Xt *q, void **r, long O, long o);
Xt   *x_tree_do_all_prev(Xt *q, void **r, long O, long o);
Xl   *x_list_do_all_first(XL *q, void **r, long O);
Xl   *x_list_do_all_last(XL *q, void **r, long O);
Xl   *x_list_do_all_next(Xl *q, void **r, long O, long o);
Xl   *x_list_do_all_prev(Xl *q, void **r, long O, long o);

void x_test_list_put    (void);
void x_test_tree_put    (void);
/*
_____________________________________________________________
Object connection macros
_____________________________________________________________
*/
#define x_list_do(a,b,c)   if (a && (b = ((XL *)a)->f)) for(c = (void *)b->d; b; b = b->n, b ? (c = (void *)b->d) : 0)
#define x_list_od(a,b,c)   if (a && (b = ((XL *)a)->l)) for(c = (void *)b->d; b; b = b->p, b ? (c = (void *)b->d) : 0)
#define x_list_from(a,b,c) if (a && (b = a))            for(c = (void *)b->d; b; b = b->n, b ? (c = (void *)b->d) : 0)
#define x_list_current(a, b) (a = memcpy(&b, a, sizeof(Xl)))

#define x_tree_do(a,b,c)   if (a && ((XT *)a)->td)      for(b = x_tree_do_first((XT *)a, (void *)&c); b; b = x_tree_do_next(b, (void *)&c))
#define x_tree_od(a,b,c)   if (a && ((XT *)a)->td)      for(b = x_tree_do_last ((XT *)a, (void *)&c); b; b = x_tree_do_prev(b, (void *)&c))
#define x_tree_from(a,b,c)                              for(b = a;                                  ; b; b = x_tree_do_next(b, (void *)&c))
#define x_tree_current(a, b) (a = memcpy(&b, a, sizeof(Xt)))

#define x_list_put_first(_p, _q)    (x_list_zap(_q), (_q)->u = (_p),    ((_p)->f ? ((_p)->f->p = (_q), (_q)->n = (_p)->f, (_p)->f = (_q))                 : ((_p)->f = (_p)->l = (_q))),                          (_p))
#define x_list_put_last(_p, _q)     (x_list_zap(_q), (_q)->u = (_p),    ((_p)->f ? ((_p)->l->n = (_q), (_q)->p = (_p)->l, (_p)->l = (_q))                 : ((_p)->f = (_p)->l = (_q))),                          (_p))
#define x_list_put_next(_p, _q)     (x_list_zap(_q), (_q)->u = (_p)->u, ((_p)->n ? ((_p)->n->p = (_q), (_q)->n = (_p)->n, (_q)->p = (_p), (_p)->n = (_q)) : ((_p)->n = (_q), (_q)->p = (_p), (_p)->u->l = (_q))), (_q))
#define x_list_put_prev(_p, _q)     (x_list_zap(_q), (_q)->u = (_p)->u, ((_p)->p ? ((_p)->p->n = (_q), (_q)->p = (_p)->p, (_q)->n = (_p), (_p)->p = (_q)) : ((_p)->p = (_q), (_q)->n = (_p), (_p)->u->f = (_q))), (_q))
#define x_list_ext(_q)              (((_q)->p ? ((_q)->p->n = (_q)->n) : ((_q)->u->f = (_q)->n)), ((_q)->n ? ((_q)->n->p = (_q)->p) : ((_q)->u->l = (_q)->p)),                                                    (_q))
#define x_zap_list(_p)              ((_p)->f  = (_p)->l  = 0,                                (_p))
#define x_list_zap(_p)              ((_p)->n  = (_p)->p  = 0, (_p)->u  = 0,                  (_p))
#define x_zap_tree(_p)              ((_p)->td = 0,                                           (_p))
#define x_tree_zap(_p)              ((_p)->tl = (_p)->tr = 0, (_p)->tu = 0, (_p)->color = 0, (_p))

#define X_DPTR_TO_PTR

#if (defined X_DPTR_TO_PTR)
#define x_tree_do_all(a, O, o, b, c) if (a && a->O && ((XT *)a->O)->td) for(b = x_tree_do_all_first((XT *)a->O, (void *)&c, x_offset(c, O)); b; b = x_tree_do_all_next(b, (void *)&c, x_offset(c, O), x_offset(c, o)))
#define x_tree_up(a, o, b, c) if (a) for(b = a->o, c = a; b; b = (b->u) ? *(Xt **)((char *)(b->u->d) + x_offset(a, o)) : 0, b ? (c = b->d) : 0)
#endif

#ifdef X_DPTR_TO_PTR
#define x_tree_od_all(a, O, o, b, c) if (a && a->O && ((XT *)a->O)->td) for(b = x_tree_do_all_last ((XT *)a->O, (void *)&c, x_offset(c, O)); b; b = x_tree_do_all_prev(b, (void *)&c, x_offset(c, O), x_offset(c, o)))
#define x_list_do_all(a, O, o, b, c) if (a && a->O && ((XL *)a->O)->f)  for(b = x_list_do_all_first((XL *)a->O, (void *)&c, x_offset(c, O)); b; b = x_list_do_all_next(b, (void *)&c, x_offset(c, O), x_offset(c, o)))
#define x_list_od_all(a, O, o, b, c) if (a && a->O && ((XL *)a->O)->l)  for(b = x_list_do_all_last ((XL *)a->O, (void *)&c, x_offset(c, O)); b; b = x_list_do_all_prev(b, (void *)&c, x_offset(c, O), x_offset(c, o)))
#else
#define x_tree_up(a, o, b, c)        if (a) for(b = a->o, c = a; b; b = (b->u) ? (Xt *)((char *)(b->u->d) + x_offset(a, o)) : 0, b ? (c = b->d) : 0)
#define x_tree_do_all(a, O, o, b, c) if (a && a->O.td) for(b = x_tree_do_all_first(&a->O, (void *)&c, x_offset(c, O)); b; b = x_tree_do_all_next(b, (void *)&c, x_offset(c, O), x_offset(c, o)))
#define x_tree_od_all(a, O, o, b, c) if (a && a->O.td) for(b = x_tree_do_all_last (&a->O, (void *)&c, x_offset(c, O)); b; b = x_tree_do_all_prev(b, (void *)&c, x_offset(c, O), x_offset(c, o)))
#define x_list_do_all(a, O, o, b, c) if (a && a->O.f)  for(b = x_list_do_all_first(&a->O, (void *)&c, x_offset(c, O)); b; b = x_list_do_all_next(b, (void *)&c, x_offset(c, O), x_offset(c, o)))
#define x_list_od_all(a, O, o, b, c) if (a && a->O.l)  for(b = x_list_do_all_last (&a->O, (void *)&c, x_offset(c, O)); b; b = x_list_do_all_prev(b, (void *)&c, x_offset(c, O), x_offset(c, o)))
#endif

#define x_vector_do(a,b,c) if (a) for(b = 0,            c = a->d[b]; b <  a->count; ++b, c = a->d[b])
#define x_vector_od(a,b,c) if (a) for(b = a->count - 1, c = a->d[b]; b >= 0;        --b, c = a->d[b])

/* In case you prefer x_tree_ext */

#define x_tree_ext     x_tree_ext_balance

/*
_____________________________________________________________
Object empty macros
_____________________________________________________________
*/
#define x_list_empty(X)   ((X) == 0 || (X)->f     == 0)
#define x_tree_empty(X)   ((X) == 0 || (X)->td    == 0)
#define x_vector_empty(X) ((X) == 0 || (X)->count == 0)
/*
_____________________________________________________________
Object size macros
_____________________________________________________________
*/
#define x_list_vector_size(X) ((X)->f  ? sizeof(XV) + (x_list_count(X) - x_vector_show) * sizeof(void *) : 0)
#define x_tree_vector_size(X) ((X)->td ? sizeof(XV) + (x_tree_count(X) - x_vector_show) * sizeof(void *) : 0)
#define x_vector_size(N)      (sizeof(XV) + (N - x_vector_show) * sizeof(void *))
/*
_____________________________________________________________
Object allocation macros
_____________________________________________________________
*/
#define x_LIST_alloc(m, s, D)       (s->D = m_alloc(m, sizeof(XL)), s->D->d = s,                                                   s)
#define x_list_alloc(m, s, D, A, L) (s->D = m_alloc(m, sizeof(Xl)), s->D->d = s,                        x_list_put_##A##(L, s->D), s)
#define x_list_ALLOC(m, s, D, A, L) (s    = m_alloc(m, sizeof(Xl)), s   ->d = D,                        x_list_put_##A##(L, s),    s)
#define x_TREE_alloc(m, s, D)       (s->D = m_alloc(m, sizeof(XT)), s->D->d = s,                                                   s)
#define x_tree_alloc(m, s, D, K, T) (s->D = m_alloc(m, sizeof(Xt)), s->D->d = s, s->D->k = s->K,        x_tree_put      (T, s->D), s)
#define x_tree_ALLOC(m, s, D, K, T) (s    = m_alloc(m, sizeof(Xt)), s   ->d = D, s   ->k = (char *)(K), x_tree_put      (T, s),    s)
#define x_tree_int(m,   s, D, K, T) (s->D = m_alloc(m, sizeof(Xt)), s->D->d = s, s->D->k = (char *)(K), x_tree_put_int  (T, s->D), s)
/*
_____________________________________________________________
Object offsets
_____________________________________________________________
*/
#define x_offset(X, Y) ((char *)&X->Y - (char *)X)

#endif