//
//  NSObject+DefaultsAdditions.m
//  LionScrollbars
//
//  Created by Dain Kaplan on 1/27/12.
//  Copyright 2012 Dain Kaplan. All rights reserved.
//

#import "DefaultsManager.h"
#import "NSObject+DefaultsAdditions.h"

@implementation NSObject (DefaultsAdditions)

- (NSString *)userDefaultsValueForSetting:(NSString *)name identifier:(NSString *)identifier
{
	DefaultsManager *dm = [DefaultsManager sharedManager];
	NSString *setting = nil;
	if (setting == nil) {
		setting = [dm settingValueForKey:name withIdentifier:identifier];
	}
	return setting;
}

- (NSString *)userDefaultsValueForSetting:(NSString *)name
{
	DefaultsManager *dm = [DefaultsManager sharedManager];
	NSString *setting = nil;
	if (setting == nil) {
		NSString *identifier = [[NSBundle mainBundle] bundleIdentifier];
		setting = [dm settingValueForKey:name withIdentifier:identifier];
	}
	if (setting == nil) {
		setting = [dm settingValueForKey:name withIdentifier:nil];
	}
	return setting;
}

- (void)setUserDefaultsValue:(NSString *)value forSetting:(NSString *)name identifer:(NSString *)identifier
{
	DefaultsManager *dm = [DefaultsManager sharedManager];
	[dm setSettingValue:value forKey:name Identifier:identifier];
	[dm settingValueForKey:name withIdentifier:nil];
}

@end
