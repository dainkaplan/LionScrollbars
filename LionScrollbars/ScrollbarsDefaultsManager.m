//
//  ScrollbarsDefaultsManager.m
//  LionScrollbars
//
//  Created by Dain Kaplan on 8/15/11.
//  Copyright 2011-2012 Dain Kaplan <dk@tempura.org>. All rights reserved.
//

#import "ScrollbarsDefaultsManager.h"

NSString *const kAppleShowScrollBarsSettingKey = @"AppleShowScrollBars";
NSString *const kAppleShowScrollBarsSettingAutomatic = @"Automatic";
NSString *const kAppleShowScrollBarsSettingWhenScrolling = @"WhenScrolling";
NSString *const kAppleShowScrollBarsSettingAlways = @"Always";
NSString *const kAppleShowScrollBarsSettingDefault = nil;

@implementation ScrollbarsDefaultsManager

static ScrollbarsDefaultsManager *_sharedSingleton;

+ (void)initialize
{
    static BOOL initialized = NO;
    if(!initialized)
    {
        initialized = YES;
        _sharedSingleton = [[ScrollbarsDefaultsManager alloc] init];
    }
}

+ (ScrollbarsDefaultsManager *)sharedManager 
{
	return _sharedSingleton;
}

- (id)init
{
    self = [super init];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}

- (NSString *)settingValueForIdentifier:(NSString *)identifier
{
	return [[DefaultsManager sharedManager] settingValueForKey:kAppleShowScrollBarsSettingKey 
												withIdentifier:identifier];
}

- (void)setSettingValue:(NSString *)value forIdentifier:(NSString *)identifier
{
	[[DefaultsManager sharedManager] setSettingValue:value 
											  forKey:kAppleShowScrollBarsSettingKey 
										  Identifier:identifier];
}

@end
