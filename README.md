# is
一个用于校验数据类型的c++库
* 不依赖第三方库
* 包含gtest测试

## 使用方法
```c++
//第一种
Is("123").number()
==> true

//第二种
Is is;
is.number("123")
==> true
```

## 检验数字
```c++
//是否是数字
is.number("3")
==> true

is.number("03")
==> true

is.number("+1")
==> true

is.number("-1")
==> true

is.number("0.1")
==> true

//是否是小数
is.decimal("0.1")
==> true

//是否是整数
is.integer("3")
==> true

//是否是奇数
is.od("3")
==> true

//是否是偶数
is.even("4")
==> true

//是否是正数
is.positive("3")
==> true

//是否是整数
is.negative("-3")
==> true
```

## 检验区间范围
```c++
//是否在min于max范围内，是(min, max)，并不是[min, max]
is.within(0, 2, "1")
==> true

//是否位于max之下
is.under(2, "1")
==> true

//是否位于min之上
is.above(0, "1")
==> true

//是否在指定集合内
is.in_set("0123456789", "69")
==> true

//是否在指定集合内
string strs = {"string", "curve"};
is.in_set(strs, "string")
==> true
```

## 检验bool
```c++
is.boolean("true")
==> true

is.boolean("True")
==> true
```

## 检验日期时间
```c++
//日期
is.date("2015-03-12")
==> true

//时间
is.time("13:19")
==> true

is.time("13:19:00")
==> true

is.time("0:0:0")
==> true

//日期时间
is.datetime("2015-03-12 13:20:20")
==> true
```

