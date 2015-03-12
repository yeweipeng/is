#include "gtest/gtest.h"
#include "is.h"

Is is;
string zero = "0",
	   integer = "123",
	   p_signInt = "+1",
	   n_signInt = "-1",
	   error_float = "1.2.3",
	   error_num = "1a3";
string float_int[] = {"1.2", "1.", "0.23"};

TEST(Number, NormalCase)
{
	ASSERT_TRUE(is.number(integer));
	ASSERT_TRUE(is.number(zero));
	ASSERT_TRUE(is.number("08"));
}

TEST(Number, SignCase)
{
	ASSERT_TRUE(is.number(p_signInt));
	ASSERT_TRUE(is.number(n_signInt));
}

TEST(Number, FloatCase)
{
	for(int i = 0; i != sizeof(float_int)/sizeof(float_int[0]); ++i) {
		ASSERT_TRUE(is.number(float_int[i]));
	}
	ASSERT_FALSE(is.number(error_float));
}

TEST(Number, ErrorCase)
{
	ASSERT_FALSE(is.number(error_num));
}

TEST(Decimal, NormalCase)
{
	for(int i = 0; i != sizeof(float_int)/sizeof(float_int[0]); ++i) {
		ASSERT_TRUE(is.decimal(float_int[i]));
	}
}

TEST(Decimal, ErrorCase)
{
	ASSERT_FALSE(is.decimal(error_float));
	ASSERT_FALSE(is.decimal(integer));
}

TEST(Integer, NormalCase)
{
	ASSERT_TRUE(is.integer(integer));
}

TEST(Integer, ErrorCase)
{
	for(int i = 0; i != sizeof(float_int)/sizeof(float_int[0]); ++i) {
		ASSERT_FALSE(is.integer(float_int[i]));
	}
	ASSERT_FALSE(is.integer(error_float));
}

TEST(Integer, PositiveCase)
{
	ASSERT_TRUE(is.positive(p_signInt));
	ASSERT_FALSE(is.positive(n_signInt));
	ASSERT_FALSE(is.positive(zero));
	ASSERT_TRUE(is.positive("0.23"));
}

TEST(Integer, NegativeCase)
{
	ASSERT_FALSE(is.negative(p_signInt));
	ASSERT_TRUE(is.negative(n_signInt));
	ASSERT_FALSE(is.negative(zero));
}

TEST(Integer, OddCase)
{
	ASSERT_TRUE(is.odd("123"));
	ASSERT_FALSE(is.odd("122"));
	for(int i = 0; i != sizeof(float_int)/sizeof(float_int[0]); ++i) {
		ASSERT_FALSE(is.odd(float_int[i]));
	}
}

TEST(Integer, EvenCase)
{
	ASSERT_FALSE(is.even("123"));
	ASSERT_TRUE(is.even("122"));
	for(int i = 0; i != sizeof(float_int)/sizeof(float_int[0]); ++i) {
		ASSERT_FALSE(is.even(float_int[i]));
	}
}

TEST(Range, InCase)
{
	ASSERT_TRUE(is.within(100, 200, integer));
	ASSERT_FALSE(is.within(130, 200, integer));
	ASSERT_TRUE(is.in_set("0123456789", "065"));
	ASSERT_FALSE(is.in_set("0123456789", "+65"));
}

TEST(Range, UnderCase)
{
	ASSERT_TRUE(is.under(130, integer));
	ASSERT_FALSE(is.under(100, integer));
}

TEST(Range, AboveCase)
{
	ASSERT_TRUE(is.above(100, integer));
	ASSERT_FALSE(is.above(130, integer));
}

TEST(Bool, NormalCase)
{
	ASSERT_TRUE(is.boolean("true"));
	ASSERT_TRUE(is.boolean("True"));
	ASSERT_TRUE(is.boolean("false"));
	ASSERT_TRUE(is.boolean("FALSE"));
	ASSERT_FALSE(is.boolean("ABC"));
}
TEST(Date, NormalCase)
{
	ASSERT_TRUE(is.date("2015-03-11"));
	ASSERT_FALSE(is.date("2015-03-32"));
	ASSERT_FALSE(is.date("2014-02-29"));
	ASSERT_TRUE(is.date("2014-02-28"));
}

TEST(Time, NormalCase)
{
	ASSERT_TRUE(is.time("10:17:00"));
	ASSERT_TRUE(is.time("10:17:0"));
	ASSERT_FALSE(is.time("10:+7:0"));
	ASSERT_TRUE(is.time("23:17:00"));
	ASSERT_FALSE(is.time("25:17:00"));
	ASSERT_FALSE(is.time("10:17:000"));
	ASSERT_TRUE(is.time("10:17"));
	ASSERT_FALSE(is.time("1017"));
	ASSERT_FALSE(is.time("1"));
	ASSERT_FALSE(is.time("1:"));
}

TEST(DateTime, NormalCase)
{
	ASSERT_TRUE(is.datetime("2015-03-11 10:17:00"));
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
