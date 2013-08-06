//
//  AppDelegate.m
//  VerbalExpressions
//
//  Created by sakiwei on 6/8/13.
//  Copyright (c) 2013 sakiwei. All rights reserved.
//

#import "AppDelegate.h"
#import "VerbalExpressions.h"

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
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
    
    return YES;
}

@end
