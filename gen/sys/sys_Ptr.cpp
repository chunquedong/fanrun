

#include "sys.h"


sys_Ptr sys_Ptr_nil = 0;

fr_Err sys_Ptr_make_val(fr_Env __env, sys_Ptr_val __self){ return 0; }
fr_Err sys_Ptr_stackAlloc(fr_Env __env, sys_Ptr *__ret, sys_Int size){ return 0; }
fr_Err sys_Ptr_load_val(fr_Env __env, sys_Obj_null *__ret, sys_Ptr_val __self){ return 0; }
fr_Err sys_Ptr_store_val(fr_Env __env, sys_Ptr_val __self, sys_Obj_null v){ return 0; }
fr_Err sys_Ptr_plus_val(fr_Env __env, sys_Ptr *__ret, sys_Ptr_val __self, sys_Int b){ return 0; }
fr_Err sys_Ptr_set_val(fr_Env __env, sys_Ptr_val __self, sys_Int index, sys_Obj_null item){ return 0; }
fr_Err sys_Ptr_get_val(fr_Env __env, sys_Obj_null *__ret, sys_Ptr_val __self, sys_Int index){ return 0; }
