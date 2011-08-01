//
//  DefaultsManager.h
//  LionScollbars
//
//  Created by Dain Kaplan on 8/1/11.
//  Copyright 2011 Dain's place. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DefaultsManager : NSObject

+ (DefaultsManager *)sharedManager;

- (NSString *)settingValueForIdentifier:(NSString *)identifier;

- (void)setSettingValue:(NSString *)value 
		  forIdentifier:(NSString *)identifier;

@end
