# LexicalAnalysis
线程规格说明的词法规则
1. 语言的关键字（18个）：
```
thread,  features,  flows,  properties,  end,  none,  in, out,  data,  port,  event,  parameter,  flow ,  source, sink ,  path,  constant ,  access
```
注：关键字是保留字，并且必须是小写。

2. 语言的专用符号8个：
```
=>  +=>  ； :  ::   {    }   ->
```

3. 标示符identifier和浮点数decimal的词法规则通过下列正则表达式定义：
```
identifier = identifier_letter (underline?letter_or_digit)*
identifier_letter=a|..|z|A|..|Z|
letter_or_digit = identifier_letter | digit
digit = 0|..|9
underline=_
 
decimal = sign? numeral . numeral
numeral= digit (digit)*
sign = + | -
```
4. 空白、换行符和制表符在词法分析时忽略掉。
