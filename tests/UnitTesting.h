#pragma once
/*
 * This extends the defines from cppunit.
 */

#include <string>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <cppunit/SourceLine.h>

CPPUNIT_NS_BEGIN

template <class T>
void assertNotEquals(
		const T& value1,
        const T& value2,
        const SourceLine & sourceLine,
        const std::string &message )
{
	std::string s1 = assertion_traits<T>::toString(value1);
	std::string s2 = assertion_traits<T>::toString(value2);

	if (s1 == s2) {
		Asserter::fail(message + ": Value1: " + s1 + ". Value2: " + s2, sourceLine);
	}
}

CPPUNIT_NS_END

#define CPPUNIT_ASSERT_NOT_EQUALS(message, value1, value2) \
	( CPPUNIT_NS::assertNotEquals(value1, value2, CPPUNIT_SOURCELINE(), message) )


#define CPPUNIT_ASSERT_LESS_MESSAGE(message, expected, actual)          \
    ( CPPUNIT_NS::assertLess( (expected),              \
                              (actual),                \
                              CPPUNIT_SOURCELINE(),    \
                              message ) )

#define CPPUNIT_ASSERT_GREATER_MESSAGE(message, expected, actual)       \
    ( CPPUNIT_NS::assertGreater( (expected),           \
                                 (actual),             \
                                 CPPUNIT_SOURCELINE(), \
                                 message ) )


#define CPPUNIT_ASSERT_NOT_NULL(message, value) CPPUNIT_ASSERT_MESSAGE(message, value != NULL)
#define CPPUNIT_ASSERT_NOT_EQUAL(message, expected, value) CPPUNIT_ASSERT_MESSAGE(message, value != NULL)
