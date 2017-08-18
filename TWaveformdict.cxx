// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TWaveformdict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "TWaveform.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_TWaveform(void *p = 0);
   static void *newArray_TWaveform(Long_t size, void *p);
   static void delete_TWaveform(void *p);
   static void deleteArray_TWaveform(void *p);
   static void destruct_TWaveform(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TWaveform*)
   {
      ::TWaveform *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TWaveform >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TWaveform", ::TWaveform::Class_Version(), "TWaveform.h", 65,
                  typeid(::TWaveform), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TWaveform::Dictionary, isa_proxy, 4,
                  sizeof(::TWaveform) );
      instance.SetNew(&new_TWaveform);
      instance.SetNewArray(&newArray_TWaveform);
      instance.SetDelete(&delete_TWaveform);
      instance.SetDeleteArray(&deleteArray_TWaveform);
      instance.SetDestructor(&destruct_TWaveform);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TWaveform*)
   {
      return GenerateInitInstanceLocal((::TWaveform*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TWaveform*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TWaveform::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TWaveform::Class_Name()
{
   return "TWaveform";
}

//______________________________________________________________________________
const char *TWaveform::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TWaveform*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TWaveform::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TWaveform*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TWaveform::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TWaveform*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TWaveform::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TWaveform*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TWaveform::Streamer(TBuffer &R__b)
{
   // Stream an object of class TWaveform.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TWaveform::Class(),this);
   } else {
      R__b.WriteClassBuffer(TWaveform::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TWaveform(void *p) {
      return  p ? new(p) ::TWaveform : new ::TWaveform;
   }
   static void *newArray_TWaveform(Long_t nElements, void *p) {
      return p ? new(p) ::TWaveform[nElements] : new ::TWaveform[nElements];
   }
   // Wrapper around operator delete
   static void delete_TWaveform(void *p) {
      delete ((::TWaveform*)p);
   }
   static void deleteArray_TWaveform(void *p) {
      delete [] ((::TWaveform*)p);
   }
   static void destruct_TWaveform(void *p) {
      typedef ::TWaveform current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TWaveform

namespace {
  void TriggerDictionaryInitialization_TWaveformdict_Impl() {
    static const char* headers[] = {
"TWaveform.h",
0
    };
    static const char* includePaths[] = {
"/usr/local/Cellar/root6/6.08.02/include/root",
"/Users/carlososoriov/Documents/University/Stuart_Internship/TWaveform Package/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TWaveformdict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$TWaveform.h")))  TWaveform;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TWaveformdict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "TWaveform.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"TWaveform", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TWaveformdict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TWaveformdict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TWaveformdict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TWaveformdict() {
  TriggerDictionaryInitialization_TWaveformdict_Impl();
}
