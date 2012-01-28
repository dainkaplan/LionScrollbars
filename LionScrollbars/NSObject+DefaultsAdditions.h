//
//  NSObject+DefaultsAdditions.h
//  LionScrollbars
//
//  Created by Dain Kaplan on 1/27/12.
//  Copyright 2012 Dain Kaplan. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSObject (DefaultsAdditions)

- (NSString *)userDefaultsValueForSetting:(NSString *)name;
- (void)setUserDefaultsValue:(NSString *)value forSetting:(NSString *)name identifer:(NSString *)identifier;
@end
