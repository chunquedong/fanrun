#include "vm.h"

CF_BEGIN

struct sys_Obj_{
    struct fr_ObjHeader super;
};

struct sys_Bool_{
    struct sys_Obj_ super;
    fr_Bool value;
};

struct sys_Num_{
    struct sys_Obj_ super;
};

struct sys_Float_{
    struct sys_Num_ super;
    fr_Float value;
};

struct sys_Int_{
    struct sys_Num_ super;
    fr_Int value;
};

struct sys_Str_{
    struct sys_Obj_ super;
    
    wchar_t *data;
    size_t size;
    
    size_t hashCode;
    char *utf8;
};

struct sys_Err_{
    struct sys_Obj_ super;
    FObj * msg;
    FObj * cause;
    FObj * traceToStr;
};

struct sys_StrBuf_{
    struct sys_Obj_ super;
    
    wchar_t *data;
    size_t size;
    size_t capacity;
};

struct sys_This_{
    struct sys_Obj_ super;
};

struct sys_Void_{
    struct sys_Obj_ super;
};

struct sys_ByteArray_{
    struct sys_Obj_ super;
    char *data;
    size_t size;
};

struct sys_IntArray_{
    struct sys_Obj_ super;
    fr_Int *data;
    size_t size;
};

struct sys_ObjArray_{
    struct sys_Obj_ super;
    FObj **data;
    size_t size;
};

struct sys_Func_{
    struct sys_Obj_ super;
};

struct sys_Type_;
struct sys_Slot_{
    struct sys_Obj_ super;
    fr_Obj parent;
    
    fr_Obj name;
    fr_Obj qname;
    
    fr_Obj facets;
    fr_Obj doc;
};

struct sys_Field_{
    struct sys_Slot_ super;
    void *ffield;
    
    fr_Obj type;
};

struct sys_Param_{
    struct sys_Obj_ super;
};

struct sys_Method_{
    struct sys_Slot_ super;
    void *fmethod;
    
    fr_Obj returns;
    fr_Obj params;
    fr_Obj func;
};
fr_Obj sys_Method_fromFMethod(fr_Env env, void *fmethod);

struct sys_Pod_{
    struct sys_Obj_ super;
    void *fpod;
    
    fr_Obj name;
    fr_Obj version;
    fr_Obj depends;
    fr_Obj uri;
    fr_Obj meta;
    fr_Obj doc;
    fr_Obj log;
};

struct sys_Type_{
    struct sys_Obj_ super;
    struct FType* ftype;
    
    fr_Obj name;
    fr_Obj qname;
    fr_Obj signature;
    
    fr_Obj pod;
    fr_Obj base;
    fr_Obj mixins;
    fr_Obj inheritance;
    
    fr_Obj fields;
    fr_Obj methods;
    fr_Obj slots;
    fr_Obj facets;
    fr_Obj doc;
};

CF_END
