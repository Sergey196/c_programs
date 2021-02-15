/*
-------------------------------------------------------------------------
 CxxTest: A lightweight C++ unit testing library.
 Copyright (c) 2008 Sandia Corporation.
 This software is distributed under the LGPL License v3
 For more information, see the COPYING file in the top CxxTest directory.
 Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
 the U.S. Government retains certain rights in this software.
-------------------------------------------------------------------------
*/

#ifndef __cxxtest_StdValueTraits_h__
#define __cxxtest_StdValueTraits_h__

//
// This file defines ValueTraits for std:: stuff.
// It is #included by <cxxtest/ValueTraits.h> if you
// define CXXTEST_HAVE_STD
//

#include <ValueTraits.h>
#include <StdHeaders.h>

#ifdef _CXXTEST_OLD_STD
#   define CXXTEST_STD(x) x
#else // !_CXXTEST_OLD_STD
#   define CXXTEST_STD(x) std::x
#endif // _CXXTEST_OLD_STD

#ifndef CXXTEST_USER_VALUE_TRAITS

namespace CxxTest {
//
// NOTE: This should have been
// template<class Char, class Traits, class Allocator>
// class ValueTraits< std::basic_string<Char, Traits, Allocator> > {};
// But MSVC doesn't support it (yet).
//

//
// If we have std::string, we might as well use it
//
class StdTraitsBase {
public:
    StdTraitsBase &operator<<(const CXXTEST_STD(string) &s) { _s += s; return *this; }
    const char *asString() const { return _s.c_str(); }

private:
    CXXTEST_STD(string) _s;
};

//
// std::string
//
CXXTEST_TEMPLATE_INSTANTIATION
class ValueTraits<const CXXTEST_STD(string)> : public StdTraitsBase {
    static bool mb_partial (char ch) {
        return ch & 0x80;
    }
    static bool mb_start (char ch) {
        return (ch & 0xC0) == 0xC0;
    }
    static size_t mb_length (char ch) {
        size_t numBytes = 1;
        while((ch & (1 << (7-numBytes))) && numBytes < 6)
            ++numBytes;
        return numBytes;
    }
    static bool is_mb ( const CXXTEST_STD(string) &s, unsigned i ) {
        if( !mb_start(s[i]) || i + mb_length(s[i]) > s.length() )
            return false;
        for ( unsigned len = mb_length(s[i]); len > 0; -- len, ++ i ) {
            if ( !mb_partial(s[i]) )
                return false;
        }
        return true;
    }

public:
    ValueTraits(const CXXTEST_STD(string) &s) {
        *this << "\"";
        for ( unsigned i = 0; i < s.length(); ++ i ) {
            if(is_mb(s, i)) {
                for ( unsigned len = mb_length(s[i]); len > 0; -- len, ++ i ) {
                    char c[2] = { s[i], '\0' };
                    *this << c;
                }
                -- i;
            }
            else {
                char c[sizeof("\\xXX")];
                charToString( s[i], c );
                *this << c;
            }
        }
        *this << "\"";
    }
};

CXXTEST_COPY_CONST_TRAITS(CXXTEST_STD(string));

#ifndef _CXXTEST_OLD_STD
//
// std::wstring
//
CXXTEST_TEMPLATE_INSTANTIATION
class ValueTraits<const CXXTEST_STD(basic_string<wchar_t>)> : public StdTraitsBase {
public:
    ValueTraits(const CXXTEST_STD(basic_string<wchar_t>) &s) {
        *this << "L\"";
        for (unsigned i = 0; i < s.length(); ++ i) {
            char c[sizeof("\\x12345678")];
            charToString((unsigned long)s[i], c);
            *this << c;
        }
        *this << "\"";
    }
};

CXXTEST_COPY_CONST_TRAITS(CXXTEST_STD(basic_string<wchar_t>));
#endif // _CXXTEST_OLD_STD

//
// Convert a range defined by iterators to a string
// This is useful for almost all STL containers
//
template<class Stream, class Iterator>
void dumpRange(Stream &s, Iterator first, Iterator last) {
    if (first == last) {
        s << "{}";
        return;
    }

    s << "{ ";
    while (first != last) {
        s << TS_AS_STRING(*first);
        if (++ first != last) {
            s << ", ";
        }
    }
    s << " }";
}

#ifdef _CXXTEST_PARTIAL_TEMPLATE_SPECIALIZATION
//
// std::pair
//
template<class First, class Second>
class ValueTraits< CXXTEST_STD(pair)<First, Second> > : public StdTraitsBase {
public:
    ValueTraits(const CXXTEST_STD(pair)<First, Second> &p) {
        *this << "<" << TS_AS_STRING(p.first) << ", " << TS_AS_STRING(p.second) << ">";
    }
};

//
// std::vector
//
template<class Element>
class ValueTraits< CXXTEST_STD(vector)<Element> > : public StdTraitsBase {
public:
    ValueTraits(const CXXTEST_STD(vector)<Element> &v) {
        dumpRange(*this, v.begin(), v.end());
    }
};

//
// std::list
//
template<class Element>
class ValueTraits< CXXTEST_STD(list)<Element> > : public StdTraitsBase {
public:
    ValueTraits(const CXXTEST_STD(list)<Element> &l) {
        dumpRange(*this, l.begin(), l.end());
    }
};

//
// std::set
//
template<class Element>
class ValueTraits< CXXTEST_STD(set)<Element> > : public StdTraitsBase {
public:
    ValueTraits(const CXXTEST_STD(set)<Element> &s) {
        dumpRange(*this, s.begin(), s.end());
    }
};

//
// std::map
//
template<class Key, class Value>
class ValueTraits< CXXTEST_STD(map)<Key, Value> > : public StdTraitsBase {
public:
    ValueTraits(const CXXTEST_STD(map)<Key, Value> &m) {
        dumpRange(*this, m.begin(), m.end());
    }
};

//
// std::deque
//
template<class Element>
class ValueTraits< CXXTEST_STD(deque)<Element> > : public StdTraitsBase {
public:
    ValueTraits(const CXXTEST_STD(deque)<Element> &d) {
        dumpRange(*this, d.begin(), d.end());
    }
};

//
// std::multiset
//
template<class Element>
class ValueTraits< CXXTEST_STD(multiset)<Element> > : public StdTraitsBase {
public:
    ValueTraits(const CXXTEST_STD(multiset)<Element> &ms) {
        dumpRange(*this, ms.begin(), ms.end());
    }
};

//
// std::multimap
//
template<class Key, class Value>
class ValueTraits< CXXTEST_STD(multimap)<Key, Value> > : public StdTraitsBase {
public:
    ValueTraits(const CXXTEST_STD(multimap)<Key, Value> &mm) {
        dumpRange(*this, mm.begin(), mm.end());
    }
};

//
// std::complex
//
template<class Number>
class ValueTraits< CXXTEST_STD(complex)<Number> > : public StdTraitsBase {
public:
    ValueTraits(const CXXTEST_STD(complex)<Number> &c) {
        if (!c.imag()) {
            *this << TS_AS_STRING(c.real());
        } else if (!c.real()) {
            *this << "(" << TS_AS_STRING(c.imag()) << " * i)";
        } else {
            *this << "(" << TS_AS_STRING(c.real()) << " + " << TS_AS_STRING(c.imag()) << " * i)";
        }
    }
};
#endif // _CXXTEST_PARTIAL_TEMPLATE_SPECIALIZATION
}

#endif // CXXTEST_USER_VALUE_TRAITS

#endif // __cxxtest_StdValueTraits_h__
