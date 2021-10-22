#ifndef COMPILER_H
#define COMPILER_H

/* REQ:COMPILER040,049,051 */
#define AUTOMATIC
#define STATIC  static
#define NULL_PTR    ((void *)0)

#define INLINE

/* REQ:COMPILER005 */
/*
#define FUNC(rettype,memclass) rettype
#define P2VAR(ptrtype, memclass, ptrclass) ptrtype *
#define P2CONST(ptrtype, memclass, ptrclass) const ptrtype *
#define CONSTP2VAR(ptrtype,memclass,ptrclass) ptrtype * const
#define CONSTP2CONST(ptrtype, memclass, ptrclass) const ptrtype * const
#define P2FUNC(rettype,ptrclass,fctname) rettype (*fctname)
#define CONST(consttype,memclass) const consttype
#define VAR(vartype,memclass) vartype
*/

#endif
