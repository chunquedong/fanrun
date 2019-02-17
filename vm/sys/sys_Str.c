#include "vm.h"
#include "pod_sys_struct.h"
#include "pod_sys_native.h"

#include <stdlib.h>
#include <string.h>
#include "utf8.h"
#include <wchar.h>

static fr_Int hash(struct sys_Str_ *str) {
    fr_Int hashValue = 0;
    size_t i;
    for (i=0; i<str->size; ++i) {
        hashValue = (str->data[i]) + 31 * hashValue;
    }
    return hashValue;
}

size_t utf8decode(char const *str, wchar_t *des, size_t n, int *illegal) {
    if (n == 0)
        return 0;
    
    char *s = (char *)str;
    size_t i = 0;
    wchar_t uc = 0;
    int r_illegal_all = 0, r_illegal;
    
    while ((uc = getu8c(&s, &r_illegal)))
    {
        if (i < (n - 1))
        {
            des[i++] = uc;
            r_illegal_all += r_illegal;
        }
        else
        {
            break;
        }
    }
    
    des[i] = 0;
    if (illegal)
    {
        *illegal = r_illegal_all + r_illegal;
    }
    
    return i;
}

size_t utf8encode(wchar_t *us, char *des, size_t n, int *illegal)
{
    if (n == 0)
        return 0;
    
    char *s = des;
    size_t left = n;
    size_t len = 0;
    int r_illegal = 0;
    
    *s = 0;
    while (*us)
    {
        int ret = putu8c(*us, &s, &left);
        if (ret > 0)
        {
            len += ret;
        }
        else if (ret == -1)
        {
            r_illegal += 1;
        }
        else
        {
            break;
        }
        
        ++us;
    }
    
    if (illegal)
    {
        *illegal = r_illegal;
    }
    
    return len;
}

//////////////////////////////////////////////////////////

FObj * sys_Str_fromUtf8_(fr_Env env__, const char *cstr) {
    size_t len;
    struct sys_Str_* str;
    FObj *obj;
    size_t size;
    
    len = strlen(cstr);
    size = len + 1;
    
    fr_Type type = fr_findType(env__, "sys", "Str");
    
    //fr_lock(env__);
    obj = fr_allocObj_internal(env__, type, sizeof(struct sys_Str_));
    str = (struct sys_Str_*)(obj);
    
    str->data = (wchar_t*)malloc(sizeof(wchar_t)*size);
    //mbstowcs();
    //str->size = mbstowcs(cstr, str->data, len);
    str->size = utf8decode(cstr, str->data, size, NULL);
    
    str->hashCode = hash(str);
    str->utf8 = NULL;
    
    //fr_unlock(env__);
    return (FObj*)(str);
}

FObj * sys_Str_fromUnicode(fr_Env env__, const wchar_t *data, size_t size) {
    struct sys_Str_* str;
    FObj *obj;

    fr_Type type = fr_findType(env__, "sys", "Str");
    
    //fr_lock(env__);
    obj = fr_allocObj_internal(env__, type, sizeof(struct sys_Str_));
    str = (struct sys_Str_*)(obj);
    
    size_t len = sizeof(wchar_t)*(size+1);
    str->data = (wchar_t*)malloc(len);
    memcpy(str->data, data, len);
    //mbstowcs();
    //str->size = mbstowcs(cstr, str->data, len);
    str->size = size;
    
    str->hashCode = hash(str);
    str->utf8 = NULL;
    
    //fr_unlock(env__);
    return (FObj*)(str);
}

char *sys_Str_getUtf8(fr_Env env__, FObj * self__) {
    size_t size;
    size_t realSize;
    struct sys_Str_ *str = (struct sys_Str_ *)self__;
    if (str->utf8) return str->utf8;
    size = str->size * 4 + 1;
    str->utf8 = malloc(size);
    realSize = utf8encode(str->data, str->utf8, size, NULL);
    str->utf8[realSize] = 0;
    return str->utf8;
}


void sys_Str_privateMake_f(fr_Env env, fr_Obj self) {
    struct sys_Str_ *str;
    //fr_lock(env);
    str = (struct sys_Str_ *)fr_getPtr(env, self);
    
    str->data = NULL;
    str->size = 0;
    
    //fr_unlock(env);
    return;
}
fr_Obj sys_Str_fromChars_f(fr_Env env, fr_Obj chars, fr_Int offset, fr_Int len) {
    return 0;
}
fr_Bool sys_Str_equals_f(fr_Env env, fr_Obj self, fr_Obj obj) {
    fr_Type type;
    struct sys_Str_ *str;
    struct sys_Str_ *other;
    size_t i = 0;
    
    //fr_lock(env);
    str = (struct sys_Str_ *)fr_getPtr(env, self);
    
    if (obj == NULL) {
        //fr_unlock(env);
        return false;
    }
    type = fr_findType(env, "sys", "Str");
    
    if (!fr_isInstanceOf(env, obj, type)) {
        //fr_unlock(env);
        return false;
    }
    
    other = (struct sys_Str_ *)fr_getPtr(env, obj);
    if (str->size != other->size) {
        //fr_unlock(env);
        return false;
    }
    if (str->hashCode != other->hashCode) {
        //fr_unlock(env);
        return false;
    }
    
    for (i=0; i<str->size; ++i) {
        if (str->data[i] != other->data[i]) {
            //fr_unlock(env);
            return false;
        }
    }
    
    //fr_unlock(env);
    return true;
}

fr_Bool sys_Str_equalsIgnoreCase_f(fr_Env env, fr_Obj self, fr_Obj s) {
    return 0;
}
fr_Int sys_Str_compare_f(fr_Env env, fr_Obj self, fr_Obj obj) {
    fr_Type type;
    struct sys_Str_ *str;
    struct sys_Str_ *other;
    fr_Int result;
    
    //fr_lock(env);
    str = (struct sys_Str_ *)fr_getPtr(env, self);
    
    if (obj == NULL) {
        //fr_unlock(env);
        return 0;
    }
    type = fr_findType(env, "sys", "Str");
    
    if (!fr_isInstanceOf(env, obj, type)) {
        fr_throwNew(env, "sys", "CastErr", "can not compare with Str");
        //fr_unlock(env);
        return 0;
    }
    
    other = (struct sys_Str_ *)fr_getPtr(env, obj);
    result = wcscmp(str->data, other->data);
    //fr_unlock(env);
    return result;
}
fr_Int sys_Str_compareIgnoreCase_f(fr_Env env, fr_Obj self, fr_Obj s) {
    return 0;
}
fr_Int sys_Str_hash_f(fr_Env env, fr_Obj self) {
    struct sys_Str_ *str;
    fr_Int result;
    //fr_lock(env);
    str = (struct sys_Str_ *)fr_getPtr(env, self);
    result = str->hashCode;
    //fr_unlock(env);
    return result;
}
fr_Obj sys_Str_toStr_f(fr_Env env, fr_Obj self) {
    return self;
}
fr_Obj sys_Str_toLocale_f(fr_Env env, fr_Obj self) {
    return self;
}
fr_Bool sys_Str_isEmpty_f(fr_Env env, fr_Obj self) {
    struct sys_Str_ *str;
    fr_Bool result;
    //fr_lock(env);
    str = (struct sys_Str_ *)fr_getPtr(env, self);
    result = str->size == 0;
    //fr_unlock(env);
    return result;
}
fr_Int sys_Str_size_f(fr_Env env, fr_Obj self) {
    struct sys_Str_ *str;
    fr_Int result;
    //fr_lock(env);
    str = (struct sys_Str_ *)fr_getPtr(env, self);
    result = str->size;
    //fr_unlock(env);
    return result;
}
fr_Obj sys_Str_intern_f(fr_Env env, fr_Obj self) {
    //TODO
    return self;
}
fr_Bool sys_Str_startsWith_f(fr_Env env, fr_Obj self, fr_Obj s) {
    struct sys_Str_ *str;
    struct sys_Str_ *src;
    
    //fr_lock(env);
    str = (struct sys_Str_ *)fr_getPtr(env, self);
    src = (struct sys_Str_ *)fr_getPtr(env, s);
    
    wchar_t *pos = wcsstr(str->data, src->data);
    if (pos == NULL) {
        //fr_unlock(env);
        return NULL;
    }
    
    if (pos == str->data) {
        //fr_unlock(env);
        return true;
    }
    //fr_unlock(env);
    return false;
}
fr_Bool sys_Str_endsWith_f(fr_Env env, fr_Obj self, fr_Obj s) {
    return 0;
}
fr_Int sys_Str_find_f(fr_Env env, fr_Obj self, fr_Obj s, fr_Int offset) {
    struct sys_Str_ *str;
    struct sys_Str_ *src;
    
    //fr_lock(env);
    str = (struct sys_Str_ *)fr_getPtr(env, self);
    src = (struct sys_Str_ *)fr_getPtr(env, s);
    
    if (offset >= str->size) {
        //fr_unlock(env);
        return -1;
    }
    
    wchar_t *pos = wcsstr(str->data + offset, src->data);
    if (pos == NULL) {
        //fr_unlock(env);
        return -1;
    }
    
    return pos - str->data;
}
fr_Obj sys_Str_index_f(fr_Env env, fr_Obj self, fr_Obj s, fr_Int offset) {
    fr_Int i = sys_Str_find_f(env, self, s, offset);
    if (i < 0) return NULL;
    fr_Value val;
    val.i = i;
    //val.type = fr_vtInt;
    
    //fr_unlock(env);
    return fr_box(env, &val, fr_vtInt);
}
//TODO
fr_Int sys_Str_findr_f(fr_Env env, fr_Obj self, fr_Obj s, fr_Int offset) {
    return -1;
}
fr_Obj sys_Str_indexr_f(fr_Env env, fr_Obj self, fr_Obj s, fr_Int offset) {
    return 0;
}
fr_Obj sys_Str_indexIgnoreCase_f(fr_Env env, fr_Obj self, fr_Obj s, fr_Int offset) {
    return 0;
}
fr_Obj sys_Str_indexrIgnoreCase_f(fr_Env env, fr_Obj self, fr_Obj s, fr_Int offset) {
    return 0;
}
fr_Bool sys_Str_contains_f(fr_Env env, fr_Obj self, fr_Obj s) {
    struct sys_Str_ *str;
    struct sys_Str_ *src;
    
    //fr_lock(env);
    str = (struct sys_Str_ *)fr_getPtr(env, self);
    src = (struct sys_Str_ *)fr_getPtr(env, s);
    
    wchar_t *pos = wcsstr(str->data, src->data);
    
    //fr_unlock(env);
    return pos != NULL;
}
fr_Bool sys_Str_containsChar_f(fr_Env env, fr_Obj self, fr_Int ch) {
    return 0;
}
fr_Int sys_Str_get_f(fr_Env env, fr_Obj self, fr_Int index) {
    struct sys_Str_ *str;
    fr_Int result;
    //fr_lock(env);
    str = (struct sys_Str_ *)fr_getPtr(env, self);
    result = str->data[index];
    //fr_unlock(env);
    return result;
}
fr_Int sys_Str_getSafe_f(fr_Env env, fr_Obj self, fr_Int index, fr_Int def) {
    return 0;
}
fr_Obj sys_Str_getRange_f(fr_Env env, fr_Obj self, fr_Obj range) {
    return 0;
}
fr_Obj sys_Str_plus_f(fr_Env env, fr_Obj self, fr_Obj obj) {
    return 0;
}
fr_Obj sys_Str_chars_f(fr_Env env, fr_Obj self) {
    return 0;
}
void sys_Str_each_f(fr_Env env, fr_Obj self, fr_Obj c) {
    return;
}
void sys_Str_eachr_f(fr_Env env, fr_Obj self, fr_Obj c) {
    return;
}
fr_Bool sys_Str_any_f(fr_Env env, fr_Obj self, fr_Obj c) {
    return 0;
}
fr_Bool sys_Str_all_f(fr_Env env, fr_Obj self, fr_Obj c) {
    return 0;
}
fr_Obj sys_Str_spaces_f(fr_Env env, fr_Int n) {
    return 0;
}
fr_Obj sys_Str_lower_f(fr_Env env, fr_Obj self) {
    struct sys_Str_ *str;
    struct sys_Str_ *nstr;
    fr_Obj onstr;
    int i;
    
    //fr_lock(env);
    str = (struct sys_Str_ *)fr_getPtr(env, self);
    
    fr_Type type = fr_findType(env, "sys", "Str");
    onstr = fr_allocObj(env, type, sizeof(struct sys_Str_));
    nstr = (struct sys_Str_*)fr_getPtr(env, onstr);
    
    nstr->data = (wchar_t*)malloc(sizeof(wchar_t)*(str->size+1));
    nstr->size = str->size;
    nstr->hashCode = hash(nstr);
    nstr->utf8 = NULL;
    
    for (i=0; i<str->size; ++i) {
        nstr->data[i] = towlower(str->data[i]);
    }
    
    //fr_unlock(env);
    return onstr;
}
fr_Obj sys_Str_upper_f(fr_Env env, fr_Obj self) {
    struct sys_Str_ *str;
    struct sys_Str_ *nstr;
    fr_Obj onstr;
    int i;
    
    //fr_lock(env);
    str = (struct sys_Str_ *)fr_getPtr(env, self);
    
    fr_Type type = fr_findType(env, "sys", "Str");
    onstr = fr_allocObj(env, type, sizeof(struct sys_Str_));
    nstr = (struct sys_Str_*)fr_getPtr(env, onstr);
    
    nstr->data = (wchar_t*)malloc(sizeof(wchar_t)*(str->size+1));
    nstr->size = str->size;
    nstr->hashCode = hash(nstr);
    nstr->utf8 = NULL;
    
    for (i=0; i<str->size; ++i) {
        nstr->data[i] = towupper(str->data[i]);
    }
    
    //fr_unlock(env);
    return onstr;
}
fr_Obj sys_Str_capitalize_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Str_decapitalize_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Str_toDisplayName_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Str_fromDisplayName_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Str_justl_f(fr_Env env, fr_Obj self, fr_Int width) {
    return 0;
}
fr_Obj sys_Str_justr_f(fr_Env env, fr_Obj self, fr_Int width) {
    return 0;
}
fr_Obj sys_Str_padl_f(fr_Env env, fr_Obj self, fr_Int width, fr_Int char_) {
    return 0;
}
fr_Obj sys_Str_padr_f(fr_Env env, fr_Obj self, fr_Int width, fr_Int char_) {
    return 0;
}
fr_Obj sys_Str_reverse_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Str_trim_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Str_trimToNull_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Str_trimStart_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Str_trimEnd_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Str_split_f(fr_Env env, fr_Obj self, fr_Obj separator, fr_Bool trim) {
    return 0;
}
fr_Obj sys_Str_splitLines_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Str_replace_f(fr_Env env, fr_Obj self, fr_Obj from, fr_Obj to) {
    return 0;
}
fr_Int sys_Str_numNewlines_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Bool sys_Str_isAscii_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Bool sys_Str_isSpace_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Bool sys_Str_isUpper_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Bool sys_Str_isLower_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Bool sys_Str_isAlpha_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Bool sys_Str_isAlphaNum_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Int sys_Str_localeCompare_f(fr_Env env, fr_Obj self, fr_Obj s) {
    return 0;
}
fr_Obj sys_Str_localeLower_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Str_localeUpper_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Str_localeCapitalize_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Obj sys_Str_localeDecapitalize_f(fr_Env env, fr_Obj self) {
    return 0;
}
fr_Bool sys_Str_toBool_f(fr_Env env, fr_Obj self, fr_Bool checked) {
    return 0;
}
fr_Int sys_Str_toInt_f(fr_Env env, fr_Obj self, fr_Int radix, fr_Bool checked) {
    return 0;
}
fr_Float sys_Str_toFloat_f(fr_Env env, fr_Obj self, fr_Bool checked) {
    return 0;
}
fr_Obj sys_Str_toCode_f(fr_Env env, fr_Obj self, fr_Int quote, fr_Bool escapeUnicode) {
    return 0;
}
fr_Obj sys_Str_toXml_f(fr_Env env, fr_Obj self) {
    return 0;
}
//TODO
fr_Obj sys_Str_format_f(fr_Env env, fr_Obj format, fr_Obj args) {
    return NULL;
}
fr_Obj sys_Str_toUtf8_f(fr_Env env, fr_Obj self) {
    return NULL;
}
fr_Obj sys_Str_fromUtf8_f(fr_Env env, fr_Obj ba, fr_Int offset, fr_Int len) {
    return NULL;
}
void sys_Str_finalize_f(fr_Env env, fr_Obj self) {
    struct sys_Str_ *str;
    //fr_lock(env);
    str = (struct sys_Str_ *)fr_getPtr(env, self);
    
    free(str->data);
    free(str->utf8);
    str->data = NULL;
    str->utf8 = NULL;
    str->size = 0;
    str->hashCode = 0;
    
    //fr_unlock(env);
    return;
}
void sys_Str_static__init_f(fr_Env env) {
    return;
}
