/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.1
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


using System;
using System.Runtime.InteropServices;

public class Importer : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal Importer(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(Importer obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~Importer() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          AssimpPINVOKE.delete_Importer(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public Importer() : this(AssimpPINVOKE.new_Importer__SWIG_0(), true) {
  }

  public Importer(Importer other) : this(AssimpPINVOKE.new_Importer__SWIG_1(Importer.getCPtr(other)), true) {
    if (AssimpPINVOKE.SWIGPendingException.Pending) throw AssimpPINVOKE.SWIGPendingException.Retrieve();
  }

  public int GetPropertyInteger(string szName, int iErrorReturn) {
    int ret = AssimpPINVOKE.Importer_GetPropertyInteger__SWIG_0(swigCPtr, szName, iErrorReturn);
    return ret;
  }

  public int GetPropertyInteger(string szName) {
    int ret = AssimpPINVOKE.Importer_GetPropertyInteger__SWIG_1(swigCPtr, szName);
    return ret;
  }

  public bool GetPropertyBool(string szName, bool bErrorReturn) {
    bool ret = AssimpPINVOKE.Importer_GetPropertyBool__SWIG_0(swigCPtr, szName, bErrorReturn);
    return ret;
  }

  public bool GetPropertyBool(string szName) {
    bool ret = AssimpPINVOKE.Importer_GetPropertyBool__SWIG_1(swigCPtr, szName);
    return ret;
  }

  public float GetPropertyFloat(string szName, float fErrorReturn) {
    float ret = AssimpPINVOKE.Importer_GetPropertyFloat__SWIG_0(swigCPtr, szName, fErrorReturn);
    return ret;
  }

  public float GetPropertyFloat(string szName) {
    float ret = AssimpPINVOKE.Importer_GetPropertyFloat__SWIG_1(swigCPtr, szName);
    return ret;
  }

  public string GetPropertyString(string szName, string sErrorReturn) {
    string ret = AssimpPINVOKE.Importer_GetPropertyString__SWIG_0(swigCPtr, szName, sErrorReturn);
    if (AssimpPINVOKE.SWIGPendingException.Pending) throw AssimpPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public string GetPropertyString(string szName) {
    string ret = AssimpPINVOKE.Importer_GetPropertyString__SWIG_1(swigCPtr, szName);
    return ret;
  }

  public bool IsDefaultIOHandler() {
    bool ret = AssimpPINVOKE.Importer_IsDefaultIOHandler(swigCPtr);
    return ret;
  }

  public void SetProgressHandler(ProgressHandler pHandler) {
    AssimpPINVOKE.Importer_SetProgressHandler(swigCPtr, ProgressHandler.getCPtr(pHandler));
  }

  public ProgressHandler GetProgressHandler() {
    IntPtr cPtr = AssimpPINVOKE.Importer_GetProgressHandler(swigCPtr);
    ProgressHandler ret = (cPtr == IntPtr.Zero) ? null : new ProgressHandler(cPtr, false);
    return ret;
  }

  public bool IsDefaultProgressHandler() {
    bool ret = AssimpPINVOKE.Importer_IsDefaultProgressHandler(swigCPtr);
    return ret;
  }

  public bool ValidateFlags(aiPostProcessSteps pFlags) {
    bool ret = AssimpPINVOKE.Importer_ValidateFlags(swigCPtr, (uint)pFlags);
    return ret;
  }

  public aiScene ReadFile(string pFile, aiPostProcessSteps pFlags) {
    IntPtr cPtr = AssimpPINVOKE.Importer_ReadFile__SWIG_0(swigCPtr, pFile, (uint)pFlags);
    aiScene ret = (cPtr == IntPtr.Zero) ? null : new aiScene(cPtr, false);
    return ret;
  }

  public void FreeScene() {
    AssimpPINVOKE.Importer_FreeScene(swigCPtr);
  }

  public string GetErrorString() {
    string ret = AssimpPINVOKE.Importer_GetErrorString(swigCPtr);
    return ret;
  }

  public bool IsExtensionSupported(string szExtension) {
    bool ret = AssimpPINVOKE.Importer_IsExtensionSupported__SWIG_0(swigCPtr, szExtension);
    return ret;
  }

  public void GetExtensionList(aiString szOut) {
    AssimpPINVOKE.Importer_GetExtensionList__SWIG_0(swigCPtr, aiString.getCPtr(szOut));
    if (AssimpPINVOKE.SWIGPendingException.Pending) throw AssimpPINVOKE.SWIGPendingException.Retrieve();
  }

  public void GetExtensionList(SWIGTYPE_p_std__string szOut) {
    AssimpPINVOKE.Importer_GetExtensionList__SWIG_1(swigCPtr, SWIGTYPE_p_std__string.getCPtr(szOut));
    if (AssimpPINVOKE.SWIGPendingException.Pending) throw AssimpPINVOKE.SWIGPendingException.Retrieve();
  }

  public aiScene GetScene() {
    IntPtr cPtr = AssimpPINVOKE.Importer_GetScene(swigCPtr);
    aiScene ret = (cPtr == IntPtr.Zero) ? null : new aiScene(cPtr, false);
    return ret;
  }

  public aiScene GetOrphanedScene() {
    IntPtr cPtr = AssimpPINVOKE.Importer_GetOrphanedScene(swigCPtr);
    aiScene ret = (cPtr == IntPtr.Zero) ? null : new aiScene(cPtr, false);
    return ret;
  }

  public void GetMemoryRequirements(aiMemoryInfo arg0) {
    AssimpPINVOKE.Importer_GetMemoryRequirements(swigCPtr, aiMemoryInfo.getCPtr(arg0));
    if (AssimpPINVOKE.SWIGPendingException.Pending) throw AssimpPINVOKE.SWIGPendingException.Retrieve();
  }

  public void SetExtraVerbose(bool bDo) {
    AssimpPINVOKE.Importer_SetExtraVerbose(swigCPtr, bDo);
  }

  public string GetExtensionList() {
    string ret = AssimpPINVOKE.Importer_GetExtensionList__SWIG_2(swigCPtr);
    return ret;
  }

}
