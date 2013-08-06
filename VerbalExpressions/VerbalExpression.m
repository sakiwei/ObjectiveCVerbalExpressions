//
//  VerbalExpressions Objective C Library v0.1
//  VerbalExpressions.m
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

#import "VerbalExpression.h"

@implementation VerbalExpression{
    @private
    NSString *_prefixes;
    NSString *_source;
    NSString *_suffixes;
    NSRegularExpression *_regex;
}

#pragma mark - initialize

/**
 Creates and initializes an `VerbalExpression` object.
 
 @return The newly-initialized `VerbalExpression` object
 */
+ (instancetype)expression{
    return [[self alloc] init];
}

/**
 Initializes an `VerbalExpression` object.
 */
- (id)init {
    if ((self=[super init])) {
        _prefixes = @"";
        _source = @"";
        _suffixes = @"";
        _regex = nil;
    }
    return self;
}

#pragma mark - private

/**
 Sanitation function for adding anything safely to the expression
 @param value the to be added
 @return string escaped value
 */
- (NSString *)_sanitize:(NSString *)value {
    if(!value) {
        return value;
    }
    else {
        return [NSRegularExpression escapedPatternForString:value];
    }
}

- (NSString *)description{
    return self.getRegex;
}

/**
 Create `NSRegularExpression` only if needed
 
 @return `NSRegularExpression` object
 */
- (NSRegularExpression *)regex{
    if (!_regex || (_regex && ![_regex.pattern isEqualToString:self.getRegex])) {
        // create new regex object
        NSError *outError;
        _regex = [[NSRegularExpression alloc] initWithPattern:self.getRegex options:_regexOptions error:&outError];
        if (outError) {
            NSLog(@"outError = %@",outError);
        }
    }
    return _regex;
}

#pragma mark - public
- (id)add:(NSString *)value {
    _source = (value)?[_source stringByAppendingString:value]:_source;
    return self;
}

- (id)startOfLine{
    return [self startOfLine:YES];
}

- (id)startOfLine:(BOOL)enable {
    _prefixes = enable? @"^" : @"";
    return self;
}

- (id)endOfLine{
    return [self endOfLine:YES];
}

- (id)endOfLine:(BOOL)enable {
    _suffixes = enable? @"$" : @"";
    return self;
}

- (id)then:(NSString *)value {
    return [self add:[NSString stringWithFormat:@"(?:%@)", [self _sanitize:value]]];
}

- (id)find:(NSString *)value {
    return [self then:value];
}

- (id)maybe:(NSString *)value {
    return [self add:[NSString stringWithFormat:@"(?:%@)?", [self _sanitize:value]]];
}

- (id)anything {
    return [self add:@"(?:.*)"];
}

- (id)anythingBut:(NSString *)value {
    return [self add:[NSString stringWithFormat:@"(?:[^%@]*)", [self _sanitize:value]]];
}

- (id)something {
    return [self add:@"(?:.+)"];
}

- (id)somethingBut:(NSString *)value {
    return [self add:[NSString stringWithFormat:@"(?:[^%@]+)", [self _sanitize:value]]];
}

- (NSString *)replace:(NSString *)source by:(NSString *)value {
	return [self.regex stringByReplacingMatchesInString:source options:0 range:NSMakeRange(0, [source length]) withTemplate:value];
}

- (id)lineBreak {
    return [self add:@"(?:(?:\\n)|(?:\\r\\n))"];
}

- (id)br {
    return [self lineBreak];
}

- (id)tab {
    return [self add:@"\\t"];
}

- (id)word {
    return [self add:@"\\w+"];
}

- (id)anyOf:(NSString *)value {
    return [self add:[NSString stringWithFormat:@"[%@]",[self _sanitize:value]]];
}

- (id)any:(NSString *)value {
    return [self anyOf:value];
}

- (id)range:(NSArray *)args {
    NSString *value = @"[";
    
    for(int _from = 0; _from < args.count; _from += 2) {
        int _to = _from+1;
        if(args.count <= _to) break;
        
        NSString *from = [self _sanitize:args[_from]];
        NSString *to = [self _sanitize:args[_to]];
        
        value = [NSString stringWithFormat:@"%@%@-%@", value, from, to];
    }
    
    value = [value stringByAppendingString:@"]"];
    
    return [self add:value];
}

- (id)addModifier:(NSRegularExpressionOptions)regularExpressionOptions {
    _regexOptions |= regularExpressionOptions;
    return self;
}

- (id)removeModifier:(NSRegularExpressionOptions)regularExpressionOptions {
    _regexOptions &= ~regularExpressionOptions;
    return self;
}

- (id)withAnyCase:(BOOL)enable {
    if (enable) {
       return [self addModifier:NSRegularExpressionCaseInsensitive];
    }
    else {
       return [self removeModifier:NSRegularExpressionCaseInsensitive];
    }
}

- (id)multiple:(NSString *)value {
    NSString *safeValue = [self _sanitize:value];
    NSString *lastStr = [safeValue substringFromIndex:safeValue.length-1];
    if (![lastStr isEqualToString:@"+"] && ![lastStr isEqualToString:@"*"]) {
        safeValue = [safeValue stringByAppendingString:@"+"];
    }
    return [self add:safeValue];
}

- (id)_or:(NSString *)value {
    return [self _or:value escaped:YES];
}

- (id)_or:(NSString *)value escaped:(BOOL)escaped {
    _prefixes = [_prefixes stringByAppendingString:@"(?:"];
    _suffixes = [@")" stringByAppendingString:_suffixes];
    [self add:@")|(?:"];
    
    if (value) {
        if (escaped) {
            [self add:value];
        }else{
            [self find:value];
        }
    }
    return self;
}

- (id)beginCapture{
    _suffixes = [_suffixes stringByAppendingFormat:@")"];
    return [self add:@"("];
}

- (id)endCapture{
    _suffixes = [_suffixes substringWithRange:NSMakeRange(0, _suffixes.length-1)];
    return [self add:@")"];
}

- (BOOL)test:(NSString *)toTest {
    NSArray *result = [self.regex matchesInString:toTest options:0 range:NSMakeRange(0, toTest.length)];
    return (result.count);
}

- (BOOL)isMatch:(NSString *)toTest {
    return [self test:toTest];
}


- (NSString *)getRegex{
    return [NSString stringWithFormat:@"%@%@%@",_prefixes,_source,_suffixes];
}

@end
