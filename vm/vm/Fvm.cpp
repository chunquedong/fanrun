//
//  FVM.cpp
//  vm
//
//  Created by yangjiandong on 15/9/27.
//  Copyright (c) 2015, yangjiandong. All rights reserved.
//

#include "Fvm.h"
#include "Env.h"
#include <assert.h>

#ifdef FR_LLVM
    #include "SimpleLLVMJIT.hpp"
#endif

Fvm::Fvm(PodManager *podManager)
    : podManager(podManager), executeEngine(nullptr)
{
    gc.gcSupport = this;
    LinkedList_make(&globalRefList);
#ifdef FR_LLVM
    executeEngine = new SimpleLLVMJIT();
#endif
}

Fvm::~Fvm() {
    LinkedList_release(&globalRefList);
    delete executeEngine;
}

void Fvm::start() {

}
void Fvm::stop() {
}

Env *Fvm::getEnv() {
    std::thread::id tid = std::this_thread::get_id();
    auto found = threads.find(tid);
    Env *env;
    if (found != threads.end()) {
        env = found->second;
    } else {
        env = new Env(this);
        threads[tid] = env;
    }
    return env;
}
void Fvm::releaseEnv(Env *env) {
    std::thread::id tid = std::this_thread::get_id();
    threads.erase(tid);
    delete env;
}

void Fvm::registerMethod(const char *name, fr_NativeFunc func) {
    podManager->registerMethod(name, func);
}

void Fvm::onStartGc() {
    
}

void Fvm::printObj(GcObj *obj) {
    printf("%p", obj);
}

int Fvm::allocSize(void *type) {
    return ((FType *)(type))->c_allocSize;
}

void Fvm::visitChildren(Gc *gc, FObj* obj) {
    Env *env = nullptr;
    
    FType *ftype = fr_getFType(env, obj);
    FType *objArray = podManager->findType(env, "sys", "Array");
    if (ftype == objArray) {
        fr_Array *array = (fr_Array *)obj;
        if (array->valueType == fr_vtObj) {
            for (size_t i=0; i<array->size; ++i) {
                FObj * obj = array->data[i];
                //list->push_back((FObj*)obj);
                gc->onVisit((FObj*)obj);
            }
        }
        return;
    }
    
    for (int i=0; i<ftype->fields.size(); ++i) {
        FField &f = ftype->fields[i];
        if ((f.flags & FFlags::Storage) == 0) {
            continue;
        }
        if (f.flags & FFlags::Static) {
            //pass;
        } else {
            fr_Value *val = podManager->getInstanceFieldValue(obj, &f);
            fr_ValueType vtype = podManager->getValueType(env, ftype->c_pod, f.type);
            if (vtype == fr_vtObj) {
                //list->push_back((FObj*)val->o);
                gc->onVisit((FObj*)val->o);
            }
        }
    }
}
void Fvm::walkRoot(Gc *gc) {
    //global ref
    LinkedListElem *it = LinkedList_first(&globalRefList);
    LinkedListElem *end = LinkedList_end(&globalRefList);
    while (it != end) {
        gc->onVisit(reinterpret_cast<FObj*>(it->data));
        it = it->next;
    }
    
    //static field
    for (auto it = staticFieldRef.begin(); it != staticFieldRef.end(); ++it) {
        gc->onVisit(*reinterpret_cast<FObj **>(*it));
    }
    
    //local
    for (auto it = threads.begin(); it != threads.end(); ++it) {
        Env *env = it->second;
        env->walkLocalRoot(gc);
    }
}
void Fvm::finalizeObj(FObj* obj) {
    Env *env = getEnv();
    
    fr_TagValue val;
    val.type = fr_vtObj;
    val.any.o = obj;
    env->push(&val);
    
    FMethod *m = env->findMethod("sys", "Obj", "finalize");
    env->callVirtual(m, -1);
    //env->callVirtualMethod("finalize", 0);
}
void Fvm::puaseWorld(bool bloking) {
    for (auto it = threads.begin(); it != threads.end(); ++it) {
        Env *env = it->second;
        env->needStop = true;
    }
    
    if (bloking) {
      std::thread::id tid = std::this_thread::get_id();
      for (auto it = threads.begin(); it != threads.end(); ++it) {
        if (it->first ==  tid) continue;
        Env *env = it->second;
        while (!env->isStoped) {
            System_sleep(5);
        }
      }
    }
}
void Fvm::resumeWorld() {
    for (auto it = threads.begin(); it != threads.end(); ++it) {
        Env *env = it->second;
        env->needStop = false;
    }
}

fr_Obj Fvm::newGlobalRef(FObj * obj) {
    lock.lock();
    LinkedListElem *elem = LinkedList_newElem(&globalRefList, 0);
    elem->data = obj;
    LinkedList_add(&globalRefList, elem);
    fr_Obj objRef = (fr_Obj)(&elem->data);
    lock.unlock();
    return objRef;
}

void Fvm::deleteGlobalRef(fr_Obj objRef) {
    lock.lock();
    LinkedListElem *elem =  reinterpret_cast<LinkedListElem *>((char*)(objRef) - offsetof(LinkedListElem, data));
    elem->data = NULL;
    LinkedList_remove(&globalRefList, elem);
    lock.unlock();
}

void Fvm::addStaticRef(fr_Obj obj) {
    staticFieldRef.push_back(obj);
}
