//
//  HackedScrollersUserDefaults.h
//  LionScrollbars
//
//  Created by Dain Kaplan on 1/28/12.
//  Copyright 2012 Dain Kaplan. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSString* const kLsbSettingsChangedNotification;

extern NSString* const kLsbRestyleLegacyScrollers;
extern NSString* const kLsbRestyleOverlayScrollers;
extern NSString* const kLsbScrollerKnobMinAlpha;
extern NSString* const kLsbScrollerTrackMinAlpha;
extern NSString* const kLsbUseGradient;
extern NSString* const kLsbRoundedCorners;
extern NSString* const kLsbDrawBackgrounds;

typedef struct _HackedScrollerSettings {
	BOOL restyleLegacyScrollers;
	BOOL restyleOverlayScrollers;
	CGFloat scrollerKnobMinAlpha;
	CGFloat scrollerTrackMinAlpha;
	BOOL useGradient;
	BOOL roundedCorners;
	BOOL drawBackgrounds;
} HackedScrollerSettings;

HackedScrollerSettings loadHackedScrollerSettingsFromUserDefaults(void);
void saveHackedScrollerSettingsToUserDefaults(HackedScrollerSettings *_settings);
void setHackedScrollerSettingsDefaults(HackedScrollerSettings *_settings);

@protocol HackedScrollerUserDefaults
- (void)setHackedScrollerSettings:(HackedScrollerSettings)settings;
@end
