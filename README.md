VerbalExpressions Objective C Library
===========================

- ported from [VerbalExpressions](https://github.com/jehna/VerbalExpressions)

VerbalExpressions is an Objective C library that helps to construct difficult regular expressions.

## Requirements
VerbalExpressions requires either __iOS >= 4.3__, or __Mac OS >= 10.7__. Also, it uses __ARC__. 

## Instalation
### From source
Drags `VerbalExpressions.h` and `VerbalExpressions.m` into your projects and `import "VerbalExpressions.h"`

## Examples

```objective-c
// url matches
VerbalExpressions *tester = [[[[[[[VerEX() startOfLine] then:@"http"] maybe:@"s"] then:@"://"] maybe:@"www."] anythingBut:@" "] endOfLine];

NSString *testMe = @"https://www.google.com/";
if( [tester test:testMe] ){
    NSLog(@"We have a correct URL ");
}else{
    NSLog(@"The URL is incorrect");
}

// replace string
NSString *replaceMe = @"Replace bird with a duck";
tester = [VerEX() find:@"bird"];
NSString *result = [tester replace:replaceMe by:@"duck"];
NSLog(@"result = %@",result);

// shorthand for string replace
result = [[VerEX() find:@"red"] replace:@"We have a red house" by:@"blue"];
NSLog(@"result = %@",result); 

```
