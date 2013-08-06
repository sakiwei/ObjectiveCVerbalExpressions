//
//  VerbalExpressions Objective C Library v0.1
//  VerbalExpressions.h
//
//  This is a ported version of VerbalExpressions JavaScript Library
//  https://github.com/jehna/VerbalExpressions
//
//  Copyright (c) 2013 Wai Cheung.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#import <Foundation/Foundation.h>

/**
 Shorthand for creating `VerbalExpression` object
 */
#define VerEX() [VerbalExpression expression]

@interface VerbalExpression : NSObject
/**
 The NSRegularExpression object which created by VerbalExpression commands
 */
@property (strong, nonatomic, readonly) NSRegularExpression *regex;

/**
 The NSRegularExpressionOptions which created by VerbalExpression commands
 */
@property (nonatomic, readonly) NSRegularExpressionOptions regexOptions;

/**
 Creates and initializes an `VerbalExpression` object.
 
 @return The newly-initialized `VerbalExpression` object
 */
+ (instancetype)expression;

/**
 Add stuff to the expression 
 
 @param value the stuff to be added
 
 @return current `VerbalExpression` object
 */
- (id)add:(NSString *)value;

/**
 Mark the expression to start at the beginning of the line.
 
 @return current `VerbalExpression` object
 */
- (id)startOfLine;

/**
 Mark the expression to start at the beginning of the line.
 
 @param enable Enables or disables the line starting
 
 @return current `VerbalExpression` object
 */
- (id)startOfLine:(BOOL)enable;

/**
 Mark the expression to end at the last character of the line.
 
 @return current `VerbalExpression` object
 */
- (id)endOfLine;

/**
 Mark the expression to end at the last character of the line.
 
 @param enable Enables or disables the line ending.
 
 @return current `VerbalExpression` object
 */
- (id)endOfLine:(BOOL)enable;

/**
 Add a string to the expression
 
 @param value The string to be looked for
 
 @return current `VerbalExpression` object
 */
- (id)then:(NSString *)value;

/**
 alias for `then:`
 
 @param value The string to be looked for
 
 @return current `VerbalExpression` object
 */
- (id)find:(NSString *)value;

/**
 Add a string to the expression that might appear once (or not).

 @param value The string to be looked for
 
 @return current `VerbalExpression` object
 */
- (id)maybe:(NSString *)value;

/**
 Accept any string
 
 @return current `VerbalExpression` object
 */
- (id)anything;

/**
 Anything but this chars
 
 @param value The unaccepted chars
 
 @return current `VerbalExpression` object
 */
- (id)anythingBut:(NSString *)value;

/**
 Accept any non-empty string
 
 @return current `VerbalExpression` object
 */
- (id)something;

/**
 Anything non-empty except for these chars
 
 @param value The unaccepted chars
 
 @return current `VerbalExpression` object
 */
- (id)somethingBut:(NSString *)value;

/**
 Shorthand for replace string
 
 @param source the string that will be affected(subject)
 
 @param value  the replacement
 
 @return string of the replacement result
 */
- (NSString *)replace:(NSString *)source by:(NSString *)value;

/**
 Matches line break
 
 @return current `VerbalExpression` object
 */
- (id)lineBreak;

/**
 Shorthand for lineBreak
 
 @return current `VerbalExpression` object
 */
- (id)br;

/**
 Matches tabs.
 
 @return current `VerbalExpression` object
 */
- (id)tab;

/**
 Matches any alfanumeric
 
 @return current `VerbalExpression` object
 */
- (id)word;

/**
 Any of the listed chars
 
 @param value The chars looked for
 
 @return current `VerbalExpression` object
 */
- (id)anyOf:(NSString *)value;

/**
 Shorthand for anyOf
 
 @param value The chars looked for
 
 @return current `VerbalExpression` object
 */
- (id)any:(NSString *)value;

/**
 Adds a range to our expresion example:
    [[VerbalExpression expression] range:@[a,z,0,9]]
    => a-z
 
 @param args array of paired char ranges
 
 @return current `VerbalExpression` object
 */
- (id)range:(NSArray *)args;

/**
 Adds a modifier
 
 @return current `VerbalExpression` object
 */
- (id)addModifier:(NSRegularExpressionOptions)regularExpressionOptions;

/**
 Removes a modifier
 
 @return current `VerbalExpression` object
 */
- (id)removeModifier:(NSRegularExpressionOptions)regularExpressionOptions;

/**
 Matches case insensitive or sensitive based on enable value
 
 @param enable Enables or disables case sensitive. Default true
 
 @return current `VerbalExpression` object
 */
- (id)withAnyCase:(BOOL)enable;

/**
 Adds the multiple modifier at the end of your expresion
 
 @param value Your expresion
 
 @return current `VerbalExpression` object
 */
- (id)multiple:(NSString *)value;

/**
 Wraps the current expresion in an `or` with value
 
 @param value new expression
 
 @return current `VerbalExpression` object
 */
- (id)_or:(NSString *)value;

/**
 Wraps the current expresion in an `or` with value
 
 @param value new expression
 
 @param escaped the value is escaped for Regex or not
 
 @return current `VerbalExpression` object
 */
- (id)_or:(NSString *)value escaped:(BOOL)escaped;

- (id)beginCapture;

- (id)endCapture;

/**
 tests the match of a string to the current regex
 
 @param value The string to be tested
 
 @return boolean true if it's a match
 */
- (BOOL)test:(NSString *)toTest;

/**
 alias for `test:`
 
 @param value The string to be tested
 
 @return boolean true if it's a match
 */
- (BOOL)isMatch:(NSString *)toTest;

/**
 Creates the final regex.
 
 @return string The final regex
 */
- (NSString *)getRegex;

@end

