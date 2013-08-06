ObjectiveCVerbalExpressions
===========================

VerbalExpressions Objective C Library

- ported from [VerbalExpressions](https://github.com/jehna/VerbalExpressions)

VerbalExpressions is a Objective C library that helps to construct difficult regular expressions.

## Examples

```objective-c
// some tests
// url matches
VerbalExpression *tester = [[[[[[[[VerEX() startOfLine] then:@"http"] maybe:@"s"] then:@"://"] maybe:@"www."] anythingBut:@" "] range:@[@"a",@"e"]] endOfLine];

NSString *testMe = @"https://www.google.com/abee";
if( [tester test:testMe] ){
    NSLog(@"We have a correct URL ");
}else{
    NSLog(@"The URL is incorrect");
}

// replace string
NSString *replaceMe = @"Replace bird with a duck";
VerbalExpression *tester2 = [VerEX() find:@"bird"];
NSString *result = [tester2 replace:replaceMe by:@"duck"];
NSLog(@"result = %@",result);

// shorthand for string replace
result = [[VerEX() find:@"red"] replace:@"We have a red house" by:@"blue"];
NSLog(@"result = %@",result); 

```

## Other Implementations
You can see an up to date list of all ports in our [organization](https://github.com/VerbalExpressions).  

- [Ruby](https://github.com/ryan-endacott/verbal_expressions)
- [C#](https://github.com/VerbalExpressions/CSharpVerbalExpressions)
- [Python](https://github.com/VerbalExpressions/PythonVerbalExpressions)
- [Java](https://github.com/VerbalExpressions/JavaVerbalExpressions)
- [Groovy](https://github.com/VerbalExpressions/GroovyVerbalExpressions)
- [PHP](https://github.com/VerbalExpressions/PHPVerbalExpressions)
- [Haskell](https://github.com/VerbalExpressions/HaskellVerbalExpressions)
- [C++](https://github.com/VerbalExpressions/CppVerbalExpressions)