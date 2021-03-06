//
// Copyright (C) 2011-14 Mark Wiebe, DyND Developers
// BSD 2-Clause License, see LICENSE.txt
//

#ifndef _DYND__ARRAY_FROM_PY_DYNAMIC_HPP_
#define _DYND__ARRAY_FROM_PY_DYNAMIC_HPP_

#include <Python.h>

#include <dynd/array.hpp>

namespace pydynd {

/**
 * Converts a Python object into an nd::array, dynamically
 * reallocating the result with a new type if a new value
 * requires it.
 *
 * The returned array is writable, if the caller wants an
 * immutable array, it should call flag_as_immutable() on it.
 *
 * The reason for doing this dynamically instead of using
 * two passes is to be able to appropriately deduce types from
 * iterators which may only exist for a single pass of iteration.
 *
 * As an example, consider a deduced datashape "4 * var * var * float64"
 * from [[], [[], []], [], [[], [3.5]]].
 */
dynd::nd::array array_from_py_dynamic(PyObject *obj);

} // namespace pydynd

#endif // _DYND__ARRAY_FROM_PY_DYNAMIC_HPP_

