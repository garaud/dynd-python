//
// Copyright (C) 2011-12, Dynamic NDArray Developers
// BSD 2-Clause License, see LICENSE.txt
//

#include <Python.h>

#include <algorithm>

#include <dynd/memblock/external_memory_block.hpp>

#include "elwise_gfunc_functions.hpp"
#include "ndobject_functions.hpp"
#include "utility_functions.hpp"
#include "ctypes_interop.hpp"

using namespace std;
using namespace dynd;
using namespace pydynd;

static void create_elwise_gfunc_kernel_from_ctypes(dynd::codegen_cache& cgcache, PyCFuncPtrObject *cfunc, dynd::gfunc::elwise_kernel& out_kernel)
{
#if 0 // TODO reenable
    dtype& returntype = out_kernel.m_returntype;
    vector<dtype> &paramtypes = out_kernel.m_paramtypes;
    get_ctypes_signature(cfunc, returntype, paramtypes);

    if (returntype.get_type_id() == void_type_id) {
        // TODO: May want support for this later, e.g. for print or other output functions
        throw std::runtime_error("Cannot construct a gfunc kernel from a ctypes function which returns void");
    }

    memory_block_ptr ctypes_memblock = make_external_memory_block(cfunc, &py_decref_function);
    Py_INCREF(cfunc);

    if (paramtypes.size() == 1) {
        cgcache.codegen_unary_function_adapter(returntype, paramtypes[0], get_ctypes_calling_convention(cfunc),
                            *(void **)cfunc->b_ptr, ctypes_memblock.get(), out_kernel.m_unary_kernel);
    } else if (paramtypes.size() == 2) {
        cgcache.codegen_binary_function_adapter(returntype, paramtypes[0], paramtypes[1], get_ctypes_calling_convention(cfunc),
                            *(void **)cfunc->b_ptr, ctypes_memblock.get(), out_kernel.m_binary_kernel);
    } else {
        std::stringstream ss;
        ss << "gfunc kernels with " << paramtypes.size() << "parameters are not yet supported";
        throw std::runtime_error(ss.str());
    }
#endif // TODO reenable
}

void pydynd::elwise_gfunc_add_kernel(dynd::gfunc::elwise& gf, dynd::codegen_cache& cgcache, PyObject *kernel)
{
#if 0 // TODO reenable
    if (PyObject_IsSubclass((PyObject *)Py_TYPE(kernel), ctypes.PyCFuncPtrType_Type)) {
        gfunc::elwise_kernel egk;

        create_elwise_gfunc_kernel_from_ctypes(cgcache, (PyCFuncPtrObject *)kernel, egk);
        gf.add_kernel(egk);

        return;
    }

    throw std::runtime_error("Object could not be used as a gfunc kernel");
#endif // TODO reenable
}

PyObject *pydynd::elwise_gfunc_call(dynd::gfunc::elwise& gf, PyObject *args, PyObject *kwargs)
{
#if 0 // TODO reenable
    Py_ssize_t nargs = PySequence_Size(args);

    // Convert the args into ndobjects, and get the value dtypes
    vector<ndobject> ndobject_args(nargs);
    vector<dtype> argtypes(nargs);
    for (Py_ssize_t i = 0; i < nargs; ++i) {
        pyobject_ownref arg_obj(PySequence_GetItem(args, i));
        ndobject_init_from_pyobject(ndobject_args[i], arg_obj);
        argtypes[i] = ndobject_args[i].get_dtype().value_dtype();
    }

    const gfunc::elwise_kernel *egk;
    egk = gf.find_matching_kernel(argtypes);

    if (egk == NULL) {
        std::stringstream ss;
        ss << gf.get_name() << ": could not find a gfunc kernel matching input argument types (";
        for (Py_ssize_t i = 0; i < nargs; ++i) {
            ss << argtypes[i];
            if (i != nargs - 1) {
                ss << ", ";
            }
        }
        ss << ")";
        throw std::runtime_error(ss.str());
    }

    PyErr_SetString(PyExc_TypeError, "pydynd::elwise_gfunc_call isn't implemented presently");
    return NULL;
    /*
    if (nargs == 1) {
        ndobject result(make_elwise_unary_kernel_node_copy_kernel(
                    egk->m_returntype, ndobject_args[0].get_node(), egk->m_unary_kernel));
        pyobject_ownref result_obj(WNDObject_Type->tp_alloc(WNDObject_Type, 0));
        ((WNDObject *)result_obj.get())->v.swap(result);
        return result_obj.release();
    } else if (nargs == 2) {
        ndobject result(make_elwise_binary_kernel_node_copy_kernel(
                    egk->m_returntype, ndobject_args[0].get_node(), ndobject_args[1].get_node(), egk->m_binary_kernel));
        pyobject_ownref result_obj(WNDObject_Type->tp_alloc(WNDObject_Type, 0));
        ((WNDObject *)result_obj.get())->v.swap(result);
        return result_obj.release();
    } else {
        PyErr_SetString(PyExc_TypeError, "Elementwise gfuncs only support 1 or 2 arguments presently");
        return NULL;
    }
    */
#endif // TODO reenable
        PyErr_SetString(PyExc_TypeError, "Elementwise gfuncs disabled presently");
        return NULL;
}
