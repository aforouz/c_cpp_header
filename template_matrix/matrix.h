// **************************************************^**************************************************
// ****************************** Copyright by Ali Forouzandeh Hafshejani ******************************
// ****************************** # IUT Scientific Computing Specialist # ******************************
// **************************************************^**************************************************

// **************************************************^**************************************************
// +++++++++++++++++++++++++++++++++++++++++++++++ Start +++++++++++++++++++++++++++++++++++++++++++++++

#pragma once
using namespace std;

// **************************************************^**************************************************
// ++++++++++++++++++++++++++++++++++++++++++++++ Header +++++++++++++++++++++++++++++++++++++++++++++++

#include <vector>

// **************************************************^**************************************************
// ++++++++++++++++++++++++++++++++++++++++++++++ Matrix +++++++++++++++++++++++++++++++++++++++++++++++

/// <summary>
/// An efficient 2D memory for save template data.
/// </summary>
template <class _Ty>
class matrix
{
// **************************************************^**************************************************
// ++++++++++++++++++++++++++++++++++++++++++++++ Private ++++++++++++++++++++++++++++++++++++++++++++++

private:
// **************************************************^**************************************************
// TypeDef

	typedef vector<_Ty> _Matrix_vec_alloc;
	typedef vector<_Matrix_vec_alloc> _Matrix_alloc;
	typedef _Matrix_alloc _Matrix_val;

// **************************************************^**************************************************
// Element

	size_t _rowSize; // Row size.
	size_t _columnSize; // Column size.
	_Matrix_val _matrixElements; // Matrix elements.
	
// **************************************************^**************************************************
// ++++++++++++++++++++++++++++++++++++++++++++++ Public +++++++++++++++++++++++++++++++++++++++++++++++

public:
// **************************************************^**************************************************
// Destructor

	/// <summary>
	/// Default destructor for matrix class.
	/// </summary>
	~matrix() {}

// **************************************************^**************************************************
// Constructor

	/// <summary>
	/// Default constructor for matrix class.
	/// </summary>
	matrix() :_rowSize(0), _columnSize(0) {}

	/// <summary>
	/// Copy constructor for matrix class.
	/// </summary>
	/// <param name = "_obj">
	/// Input matrix.
	/// </param>
	matrix(const matrix<_Ty>& _obj)
		:
		_rowSize(_obj._rowSize), _columnSize(_obj._columnSize), _matrixElements(_obj._matrixElements)
	{}

	/// <summary>
	/// Constructor for square matrix.
	/// "row size == column size".
	/// </summary>
	/// <param name = "_count">
	/// Size of row and column.
	/// </param>
	matrix(size_t _count)
		:
		_rowSize(_count), _columnSize(_count), _matrixElements(_count)
	{
		for (register size_t _ir(0); _ir < _rowSize; ++_ir) 
		{
			_matrixElements[_ir] = _Matrix_vec_alloc(_columnSize); 
		}
	}

	/// <summary>
	/// Constructor for matrix.
	/// </summary>
	/// <param name = "_row_count">
	/// Size of row.
	/// </param>
	/// <param name = "_column_count">
	/// Size of column.
	/// </param>
	matrix(size_t _row_count, size_t _column_count)
		:
		_rowSize(_row_count), _columnSize(_column_count), _matrixElements(_row_count)
	{
		for (register size_t _ir(0); _ir < _rowSize; ++_ir) 
		{
			_matrixElements[_ir] = _Matrix_vec_alloc(_columnSize); 
		}
	}

	/// <summary>
	/// Constructor for matrix.
	/// </summary>
	/// <param name = "_row_count">
	/// Size of row.
	/// </param>
	/// <param name = "_column_count">
	/// Size of column.
	/// </param>
	/// <param name = "_first_value">
	/// First value of all elements.
	/// </param>
	matrix(size_t _row_count, size_t _column_count, _Ty _defalut_value)
		:
		_rowSize(_row_count), _columnSize(_column_count), _matrixElements(_row_count)
	{
		for (register size_t _ir(0); _ir < _rowSize; ++_ir)
		{
			_matrixElements[_ir] = _Matrix_vec_alloc(_columnSize, _defalut_value); 
		}
	}

// **************************************************^**************************************************
// Operator

	/// <summary>
	/// Assignment.
	/// </summary>
	/// <param name = "_obj">
	/// Input matrix.
	/// </param>
/*	matrix<_Ty>& operator=(matrix<_Ty>& _obj)
	{
		_rowSize = _obj._rowSize; _columnSize = _obj._columnSize;
		_matrixElements = _obj._matrixElements; return _obj;
	}*/

	/// <summary>
	/// Direct access to elements.
	/// </summary>
	_Matrix_vec_alloc& operator[](size_t _row_index) { return _matrixElements[_row_index]; }
	
// **************************************************^**************************************************
// Memory function

	/// <summary>
	/// Refuser for matrix.
	/// </summary>
	void clear() { _rowSize = 0; _columnSize = 0; _matrixElements.clear(); }

	/// <summary>
	/// Allocator for square matrix.
	/// "row size == column size".
	/// </summary>
	/// <param name = "_count">
	/// Size of row and column.
	/// </param>
	void allocate(size_t _count)
	{
		_rowSize = _count; _columnSize = _count; 
		_matrixElements = _Matrix_alloc(_count, _Matrix_vec_alloc(_count)); 
	}
	
	/// <summary>
	/// Allocator for matrix.
	/// </summary>
	/// <param name = "_row_count">
	/// Size of row.
	/// </param>
	/// <param name = "_column_count">
	/// Size of column.
	/// </param>
	void allocate(size_t _row_count, size_t _column_count)
	{
		_rowSize = _row_count; _columnSize = _column_count; 
		_matrixElements = _Matrix_alloc(_row_count, _Matrix_vec_alloc(_column_count)); 
	}

	/// <summary>
	/// Allocator for matrix.
	/// </summary>
	/// <param name = "_row_count">
	/// Size of row.
	/// </param>
	/// <param name = "_column_count">
	/// Size of column.
	/// </param>
	/// <param name = "_first_value">
	/// Default value of all elements.
	/// </param>
	void allocate(size_t _row_count, size_t _column_count, _Ty _default_value) 
	{
		_rowSize = _row_count; _columnSize = _column_count;
		_matrixElements = _Matrix_alloc(_row_count, _Matrix_vec_alloc(_column_count, _default_value)); 
	}
	
// **************************************************^**************************************************
// Function

	/// <summary>
	/// Returns the transpose of matrix.
	/// </summary>
	matrix<_Ty> transpose()
	{
		matrix<_Ty> _obj(_columnSize, _rowSize);
		for (register size_t _ir(0); _ir < _rowSize; ++_ir)
		{
			for (register size_t _ic(0); _ic < _columnSize; ++_ic)
			{
				_obj[_ic][_ir] = _matrixElements[_ir][_ic];
			}
		}
		return _obj;
	}

	/// <summary>
	/// Returns a copy of row[index].
	/// </summary>
	/// <param name = "_row_index">
	/// Index of row.
	/// </param>
	_Matrix_vec_alloc row(size_t _row_index) { return _matrixElements[_row_index]; }
	
	/// <summary>
	/// Returns a copy of column[index].
	/// </summary>
	/// <param name = "_column_index">
	/// Index of column.
	/// </param>
	_Matrix_vec_alloc column(size_t _column_index)
	{
		_Matrix_vec_alloc _tmp(_rowSize);
		for (register size_t _ir(0); _ir < _rowSize; ++_ir)
		{
			_tmp[_ir] = _matrixElements[_ir][_column_index];
		}
		return _tmp;
	}

	/// <summary>
	/// Count of rows.
	/// </summary>
	size_t row_size() { return _rowSize; }

	/// <summary>
	/// Count of columns.
	/// </summary>
	size_t column_size() { return _columnSize; }
};

// **************************************************^**************************************************
// ++++++++++++++++++++++++++++++++++++++++++++++++ End ++++++++++++++++++++++++++++++++++++++++++++++++
