//
//  DefaultsManager.h
//  LionScrollbars
//
//  Created by Dain Kaplan on 8/1/11.
//  Copyright 2011-2012 Dain Kaplan <dk@tempura.org>. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DefaultsManager : NSObject

+ (DefaultsManager *)sharedManager;

- (NSString *)settingValueForKey:(NSString *)key withIdentifier:(NSString *)identifier;
- (void)setSettingValue:(NSString *)value forKey:(NSString *)key Identifier:(NSString *)identifier;

@end
