//
//  HackedLegacyScroller+DefaultsAdditions.m
//  LionScrollbars
//
//  Created by Dain Kaplan on 1/27/12.
//  Copyright 2012 Dain Kaplan. All rights reserved.
//

#import "HackedLegacyScroller.h"
#import "HackedScrollers+DefaultsAdditions.h"
#import "NSObject+DefaultsAdditions.h"
#import "HackedScrollersUserDefaults.h"

@implementation HackedLegacyScroller (DefaultsAdditions)

+ (BOOL)shouldRestyleLegacyScrollers
{
	NSString *legacy = [self userDefaultsValueForSetting: kLsbRestyleLegacyScrollers];
	return (legacy != nil && [legacy boolValue] == YES);
}

+ (void)loadUserDefaults
{
	HackedScrollerSettings settings = loadHackedScrollerSettingsFromUserDefaults();
	[self setUseGradient: settings.useGradient];
	[self setDrawBackground: settings.drawBackgrounds];
	[self setRoundedCorners: settings.roundedCorners];
}

@end

@implementation HackedOverlayScroller (DefaultsAdditions)

+ (BOOL)shouldRestyleOverlayScrollers
{
	NSString *overlays = [self userDefaultsValueForSetting: kLsbRestyleOverlayScrollers];	
	return (overlays != nil && [overlays boolValue] == YES);
}

+ (void)loadUserDefaults
{
	HackedScrollerSettings settings = loadHackedScrollerSettingsFromUserDefaults();
	[HackedOverlayScroller setMinKnobAlpha: settings.scrollerKnobMinAlpha];
	[HackedOverlayScroller setMinTrackAlpha: settings.scrollerTrackMinAlpha];
}

@end
