//
//  VerbalExpressions Objective C Library v0.1
//  VerbalExpressions.h
//
//  This is a ported version of VerbalExpressions JavaScript Library
//  https://github.com/jehna/VerbalExpressions
//
//  Copyright (c) 2013 sakiwei.
//


#import <Foundation/Foundation.h>

/**
 Shorthand for creating `VerbalExpressions` object
 */
#define VerEX() [VerbalExpressions expression]

@interface VerbalExpressions : NSObject
/**
 The NSRegularExpression object which created by VerbalExpressions commands
 */
@property (strong, nonatomic, readonly) NSRegularExpression *regex;

/**
 The NSRegularExpressionOptions which created by VerbalExpressions commands
 */
@property (nonatomic, readonly) NSRegularExpressionOptions regexOptions;

/**
 Creates and initializes an `VerbalExpressions` object.
 
 @return The newly-initialized `VerbalExpressions` object
 */
+ (instancetype)expression;

/**
 Add stuff to the expression 
 
 @param value the stuff to be added
 
 @return current `VerbalExpressions` object
 */
- (id)add:(NSString *)value;

/**
 Mark the expression to start at the beginning of the line.
 
 @return current `VerbalExpressions` object
 */
- (id)startOfLine;

/**
 Mark the expression to start at the beginning of the line.
 
 @param enable Enables or disables the line starting
 
 @return current `VerbalExpressions` object
 */
- (id)startOfLine:(BOOL)enable;

/**
 Mark the expression to end at the last character of the line.
 
 @return current `VerbalExpressions` object
 */
- (id)endOfLine;

/**
 Mark the expression to end at the last character of the line.
 
 @param enable Enables or disables the line ending.
 
 @return current `VerbalExpressions` object
 */
- (id)endOfLine:(BOOL)enable;

/**
 Add a string to the expression
 
 @param value The string to be looked for
 
 @return current `VerbalExpressions` object
 */
- (id)then:(NSString *)value;

/**
 alias for `then:`
 
 @param value The string to be looked for
 
 @return current `VerbalExpressions` object
 */
- (id)find:(NSString *)value;

/**
 Add a string to the expression that might appear once (or not).

 @param value The string to be looked for
 
 @return current `VerbalExpressions` object
 */
- (id)maybe:(NSString *)value;

/**
 Accept any string
 
 @return current `VerbalExpressions` object
 */
- (id)anything;

/**
 Anything but this chars
 
 @param value The unaccepted chars
 
 @return current `VerbalExpressions` object
 */
- (id)anythingBut:(NSString *)value;

/**
 Accept any non-empty string
 
 @return current `VerbalExpressions` object
 */
- (id)something;

/**
 Anything non-empty except for these chars
 
 @param value The unaccepted chars
 
 @return current `VerbalExpressions` object
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
 
 @return current `VerbalExpressions` object
 */
- (id)lineBreak;

/**
 Shorthand for lineBreak
 
 @return current `VerbalExpressions` object
 */
- (id)br;

/**
 Matches tabs.
 
 @return current `VerbalExpressions` object
 */
- (id)tab;

/**
 Matches any alfanumeric
 
 @return current `VerbalExpressions` object
 */
- (id)word;

/**
 Any of the listed chars
 
 @param value The chars looked for
 
 @return current `VerbalExpressions` object
 */
- (id)anyOf:(NSString *)value;

/**
 Shorthand for anyOf
 
 @param value The chars looked for
 
 @return current `VerbalExpressions` object
 */
- (id)any:(NSString *)value;

/**
 Adds a range to our expresion example:
    [[VerbalExpressions expression] range:@[a,z,0,9]]
    => a-z
 
 @param args array of paired char ranges
 
 @return current `VerbalExpressions` object
 */
- (id)range:(NSArray *)args;

/**
 Adds a modifier
 
 @return current `VerbalExpressions` object
 */
- (id)addModifier:(NSRegularExpressionOptions)regularExpressionOptions;

/**
 Removes a modifier
 
 @return current `VerbalExpressions` object
 */
- (id)removeModifier:(NSRegularExpressionOptions)regularExpressionOptions;

/**
 Matches case insensitive or sensitive based on enable value
 
 @param enable Enables or disables case sensitive. Default true
 
 @return current `VerbalExpressions` object
 */
- (id)withAnyCase:(BOOL)enable;

/**
 Adds the multiple modifier at the end of your expresion
 
 @param value Your expresion
 
 @return current `VerbalExpressions` object
 */
- (id)multiple:(NSString *)value;

/**
 Wraps the current expresion in an `or` with value
 
 @param value new expression
 
 @return current `VerbalExpressions` object
 */
- (id)_or:(NSString *)value;

/**
 Wraps the current expresion in an `or` with value
 
 @param value new expression
 
 @param escaped the value is escaped for Regex or not
 
 @return current `VerbalExpressions` object
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

