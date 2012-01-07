//
//  ScrollbarsDefaultsManager.h
//  LionScrollbars
//
//  Created by Dain Kaplan on 8/1/11.
//  Copyright 2011-2012 Dain Kaplan <dk@tempura.org>. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DefaultsManager.h"

extern NSString *const kAppleShowScrollBarsSettingKey;
extern NSString *const kAppleShowScrollBarsSettingAutomatic;
extern NSString *const kAppleShowScrollBarsSettingWhenScrolling;
extern NSString *const kAppleShowScrollBarsSettingAlways;
extern NSString *const kAppleShowScrollBarsSettingDefault;

@interface ScrollbarsDefaultsManager : NSObject

+ (ScrollbarsDefaultsManager *)sharedManager;

- (NSString *)settingValueForIdentifier:(NSString *)identifier;
- (void)setSettingValue:(NSString *)value forIdentifier:(NSString *)identifier;

@end
