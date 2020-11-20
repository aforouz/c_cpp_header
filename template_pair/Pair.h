#pragma once

template <class _Ty1, class _Ty2>
class Pair
{
private:
	_Ty1 _first;
	_Ty2 _second;

public:
	Pair() {}
	Pair(_Ty1 _first_tmp, _Ty2 _second_tmp) :_first(_first_tmp), _second(_second_tmp) {}
	Pair<_Ty1, _Ty2> operator=(Pair<_Ty1, _Ty2> _tmp)
	{
		_first = _tmp._first;
		_second = _tmp._second;
		return _tmp;
	}

	void get_pair(_Ty1 _first_tmp, _Ty2 _second_tmp)
	{
		_first = _first_tmp;
		_second = _second_tmp;
	}
	void first(_Ty1 _first_tmp) { _first = _first_tmp; }
	void second(_Ty2 _second_tmp) { _second = _second_tmp; }

	_Ty1 first() { return _first; }
	_Ty2 second() { return _second; }

	bool operator<(Pair<_Ty1, _Ty2> _tmp)
	{
		return(
			(_first < _tmp._first)
			||
			(_first == _tmp._first && _second < _tmp._second)
			);
	}
	bool operator>(Pair<_Ty1, _Ty2> _tmp)
	{
		return(
			(_first > _tmp._first)
			||
			(_first == _tmp._first && _second > _tmp._second)
			);
	}
	bool operator<=(Pair<_Ty1, _Ty2> _tmp)
	{
		return(
			(_first < _tmp._first)
			||
			(_first == _tmp._first && _second <= _tmp._second)
			);
	}
	bool operator>=(Pair<_Ty1, _Ty2> _tmp)
	{
		return(
			(_first > _tmp._first)
			||
			(_first == _tmp._first && _second >= _tmp._second)
			);
	}
	bool operator==(Pair<_Ty1, _Ty2> _tmp)
	{
		return(
			(_first == _tmp._first)
			&&
			(_second == _tmp._second)
			);
	}
};

// *******************************************
// *** Made by: Ali Forouzandeh Hafshejani ***
// *** IUT Scientific Computing Specialist ***
// *******************************************
