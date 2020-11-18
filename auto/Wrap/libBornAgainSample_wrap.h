/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.2
 *
 * This file is not intended to be easily readable and contains a number of
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG
 * interface file instead.
 * ----------------------------------------------------------------------------- */

#ifndef SWIG_libBornAgainSample_WRAP_H_
#define SWIG_libBornAgainSample_WRAP_H_

#include <map>
#include <string>


class SwigDirector_ISample : public ISample, public Swig::Director {

public:
    SwigDirector_ISample(PyObject *self);
    SwigDirector_ISample(PyObject *self, NodeMeta const &meta, std::vector< double, std::allocator< double > > const &PValues);
    virtual ~SwigDirector_ISample();
    virtual ISample *clone() const;
    virtual void transferToCPP();
    virtual ParameterPool *createParameterTree() const;
    virtual void onChange();
    virtual void accept(INodeVisitor *visitor) const;
    virtual std::string treeToString() const;
    virtual std::vector< INode const *, std::allocator< INode const * > > getChildren() const;
    virtual void setParent(INode const *newParent);
    virtual Material const *material() const;

/* Internal director utilities */
public:
    bool swig_get_inner(const char *swig_protected_method_name) const {
      std::map<std::string, bool>::const_iterator iv = swig_inner.find(swig_protected_method_name);
      return (iv != swig_inner.end() ? iv->second : false);
    }
    void swig_set_inner(const char *swig_protected_method_name, bool swig_val) const {
      swig_inner[swig_protected_method_name] = swig_val;
    }
private:
    mutable std::map<std::string, bool> swig_inner;

#if defined(SWIG_PYTHON_DIRECTOR_VTABLE)
/* VTable implementation */
    PyObject *swig_get_method(size_t method_index, const char *method_name) const {
      PyObject *method = vtable[method_index];
      if (!method) {
        swig::SwigVar_PyObject name = SWIG_Python_str_FromChar(method_name);
        method = PyObject_GetAttr(swig_get_self(), name);
        if (!method) {
          std::string msg = "Method in class ISample doesn't exist, undefined ";
          msg += method_name;
          Swig::DirectorMethodException::raise(msg.c_str());
        }
        vtable[method_index] = method;
      }
      return method;
    }
private:
    mutable swig::SwigVar_PyObject vtable[9];
#endif

};


class SwigDirector_IFormFactor : public IFormFactor, public Swig::Director {

public:
    SwigDirector_IFormFactor(PyObject *self);
    SwigDirector_IFormFactor(PyObject *self, NodeMeta const &meta, std::vector< double, std::allocator< double > > const &PValues);
    virtual ~SwigDirector_IFormFactor();
    virtual IFormFactor *clone() const;
    virtual void transferToCPP();
    virtual ParameterPool *createParameterTree() const;
    virtual void onChange();
    virtual void accept(INodeVisitor *visitor) const;
    virtual std::string treeToString() const;
    virtual std::vector< INode const *, std::allocator< INode const * > > getChildren() const;
    virtual void setParent(INode const *newParent);
    virtual Material const *material() const;
    virtual void setAmbientMaterial(Material const &arg0);
    virtual complex_t evaluate(WavevectorInfo const &wavevectors) const;
    virtual double volume() const;
    virtual double radialExtension() const;
    virtual double bottomZ(IRotation const &rotation) const;
    virtual double topZ(IRotation const &rotation) const;
    virtual bool canSliceAnalytically(IRotation const &rot) const;
    virtual bool canSliceAnalyticallySwigPublic(IRotation const &rot) const {
      return IFormFactor::canSliceAnalytically(rot);
    }
    virtual IFormFactor *sliceFormFactor(ZLimits limits, IRotation const &rot, kvector_t translation) const;
    virtual IFormFactor *sliceFormFactorSwigPublic(ZLimits limits, IRotation const &rot, kvector_t translation) const {
      return IFormFactor::sliceFormFactor(limits,rot,translation);
    }

/* Internal director utilities */
public:
    bool swig_get_inner(const char *swig_protected_method_name) const {
      std::map<std::string, bool>::const_iterator iv = swig_inner.find(swig_protected_method_name);
      return (iv != swig_inner.end() ? iv->second : false);
    }
    void swig_set_inner(const char *swig_protected_method_name, bool swig_val) const {
      swig_inner[swig_protected_method_name] = swig_val;
    }
private:
    mutable std::map<std::string, bool> swig_inner;

#if defined(SWIG_PYTHON_DIRECTOR_VTABLE)
/* VTable implementation */
    PyObject *swig_get_method(size_t method_index, const char *method_name) const {
      PyObject *method = vtable[method_index];
      if (!method) {
        swig::SwigVar_PyObject name = SWIG_Python_str_FromChar(method_name);
        method = PyObject_GetAttr(swig_get_self(), name);
        if (!method) {
          std::string msg = "Method in class IFormFactor doesn't exist, undefined ";
          msg += method_name;
          Swig::DirectorMethodException::raise(msg.c_str());
        }
        vtable[method_index] = method;
      }
      return method;
    }
private:
    mutable swig::SwigVar_PyObject vtable[17];
#endif

};


class SwigDirector_IBornFF : public IBornFF, public Swig::Director {

public:
    SwigDirector_IBornFF(PyObject *self);
    SwigDirector_IBornFF(PyObject *self, NodeMeta const &meta, std::vector< double, std::allocator< double > > const &PValues);
    virtual ~SwigDirector_IBornFF();
    virtual IBornFF *clone() const;
    virtual void transferToCPP();
    virtual ParameterPool *createParameterTree() const;
    virtual void onChange();
    virtual void accept(INodeVisitor *visitor) const;
    virtual std::string treeToString() const;
    virtual std::vector< INode const *, std::allocator< INode const * > > getChildren() const;
    virtual void setParent(INode const *newParent);
    virtual Material const *material() const;
    virtual void setAmbientMaterial(Material const &arg0);
    virtual complex_t evaluate(WavevectorInfo const &wavevectors) const;
    virtual double volume() const;
    virtual double radialExtension() const;
    virtual double bottomZ(IRotation const &rotation) const;
    virtual double topZ(IRotation const &rotation) const;
    virtual bool canSliceAnalytically(IRotation const &rot) const;
    virtual bool canSliceAnalyticallySwigPublic(IRotation const &rot) const {
      return IBornFF::canSliceAnalytically(rot);
    }
    virtual IFormFactor *sliceFormFactor(ZLimits limits, IRotation const &rot, kvector_t translation) const;
    virtual IFormFactor *sliceFormFactorSwigPublic(ZLimits limits, IRotation const &rot, kvector_t translation) const {
      return IFormFactor::sliceFormFactor(limits,rot,translation);
    }
    virtual complex_t evaluate_for_q(cvector_t q) const;

/* Internal director utilities */
public:
    bool swig_get_inner(const char *swig_protected_method_name) const {
      std::map<std::string, bool>::const_iterator iv = swig_inner.find(swig_protected_method_name);
      return (iv != swig_inner.end() ? iv->second : false);
    }
    void swig_set_inner(const char *swig_protected_method_name, bool swig_val) const {
      swig_inner[swig_protected_method_name] = swig_val;
    }
private:
    mutable std::map<std::string, bool> swig_inner;

#if defined(SWIG_PYTHON_DIRECTOR_VTABLE)
/* VTable implementation */
    PyObject *swig_get_method(size_t method_index, const char *method_name) const {
      PyObject *method = vtable[method_index];
      if (!method) {
        swig::SwigVar_PyObject name = SWIG_Python_str_FromChar(method_name);
        method = PyObject_GetAttr(swig_get_self(), name);
        if (!method) {
          std::string msg = "Method in class IBornFF doesn't exist, undefined ";
          msg += method_name;
          Swig::DirectorMethodException::raise(msg.c_str());
        }
        vtable[method_index] = method;
      }
      return method;
    }
private:
    mutable swig::SwigVar_PyObject vtable[18];
#endif

};


class SwigDirector_ISampleBuilder : public ISampleBuilder, public Swig::Director {

public:
    SwigDirector_ISampleBuilder(PyObject *self);
    virtual ~SwigDirector_ISampleBuilder();
    virtual ParameterPool *createParameterTree() const;
    virtual void onChange();
    virtual MultiLayer *buildSample() const;
    virtual MultiLayer *createSampleByIndex(size_t arg0);
    virtual size_t size();

/* Internal director utilities */
public:
    bool swig_get_inner(const char *swig_protected_method_name) const {
      std::map<std::string, bool>::const_iterator iv = swig_inner.find(swig_protected_method_name);
      return (iv != swig_inner.end() ? iv->second : false);
    }
    void swig_set_inner(const char *swig_protected_method_name, bool swig_val) const {
      swig_inner[swig_protected_method_name] = swig_val;
    }
private:
    mutable std::map<std::string, bool> swig_inner;

#if defined(SWIG_PYTHON_DIRECTOR_VTABLE)
/* VTable implementation */
    PyObject *swig_get_method(size_t method_index, const char *method_name) const {
      PyObject *method = vtable[method_index];
      if (!method) {
        swig::SwigVar_PyObject name = SWIG_Python_str_FromChar(method_name);
        method = PyObject_GetAttr(swig_get_self(), name);
        if (!method) {
          std::string msg = "Method in class ISampleBuilder doesn't exist, undefined ";
          msg += method_name;
          Swig::DirectorMethodException::raise(msg.c_str());
        }
        vtable[method_index] = method;
      }
      return method;
    }
private:
    mutable swig::SwigVar_PyObject vtable[5];
#endif

};


#endif
