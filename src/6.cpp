/*
 * Copyright (c) 2003 Anton Ananich
 */


#include "stdafx.h"
#include "./6.h"

#pragma warning(disable:4503)

using namespace std;
using namespace brutal;

template <int x> class f {
public:
	inline void operator()() throw() {
		cout << x << " ";
	}
};

//typedef TYPELIST_5(f<1>, f<2>, f<3>, f<4>, f<5>) Functors;
typedef TYPELIST_4(f<1>, f<2>, f<3>, f<4>) Functors;
//typedef TYPELIST_2(f<1>, f<2>) Functors;

// a chain of checks
template <class List, int i> class Chain {
private:
	template <class Action, class Base> class Functor : public Base {
	private:
		Action a;
	public:
		inline void operator()() throw() {
			a();
			Base::operator()();
		}
	};
	class Stub {
	public:
		inline void operator()() throw(){}
	};
public:
	typedef Loki::GenLinearHierarchy<typename Rearrangement<List, i>::Result, Functor, Stub> Result;
};

// 
template <class T> class ChainWrapper {
private:
	T t;
public:
	inline void execute() throw() {
		t();
	}
};

// list of chains
template <class List, int i = Factorial<Loki::TL::Length<List>::value>::value> struct RearrangementList;
template <class List> struct RearrangementList<List, 0> {
	typedef Loki::NullType Result;
};
template <class List, int i> struct RearrangementList {
	typedef typename Loki::TL::Append<
		typename RearrangementList<List, i-1>::Result, 
		typename Chain<List, i-1>::Result
	>::Result Result;
};

typedef Loki::GenScatterHierarchy<RearrangementList<Functors>::Result, ChainWrapper> Instance;
Instance instance;

int _tmain(int argc, _TCHAR* argv[]) {
	// print the 20th rearrangement
	Loki::Field<20>(instance).execute();
	return 0;
}