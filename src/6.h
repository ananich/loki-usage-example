#pragma once

#include <Typelist.h>

namespace brutal {
	template <int x> struct Factorial;
	template <> struct Factorial<0> {
		enum {value = 1};
	};
	template <int x> struct Factorial {
		enum {value = x * Factorial<x-1>::value};
	};

	template <class List, int index> struct Rearrangement;
	template <class Head, int index> 
	struct Rearrangement<Loki::Typelist<Head, Loki::NullType>, index> {
		typedef Loki::Typelist<Head, Loki::NullType> Result;
	};
	template <class List, int index> struct Rearrangement {
		typedef typename Loki::TL::TypeAt<List, 
			index / Factorial<Loki::TL::Length<List>::value-1>::value>::Result CurrentType;
		typedef typename Loki::TL::Erase<List, CurrentType>::Result SubList;
		enum { subIndex = index % Factorial<Loki::TL::Length<List>::value-1>::value};
		typedef Loki::Typelist<CurrentType, typename Rearrangement<SubList, subIndex>::Result> Result;
	};
}