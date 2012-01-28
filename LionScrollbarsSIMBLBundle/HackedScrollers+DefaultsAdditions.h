//
//  HackedLegacyScroller+DefaultsAdditions.h
//  LionScrollbars
//
//  Created by Dain Kaplan on 1/27/12.
//  Copyright 2012 Dain Kaplan. All rights reserved.
//

#import "HackedOverlayScroller.h"
#import "HackedLegacyScroller.h"

@interface HackedLegacyScroller (DefaultsAdditions)

+ (BOOL)shouldRestyleLegacyScrollers;
+ (void)loadUserDefaults;

@end

@interface HackedOverlayScroller (DefaultsAdditions)

+ (BOOL)shouldRestyleOverlayScrollers;
+ (void)loadUserDefaults;

@end