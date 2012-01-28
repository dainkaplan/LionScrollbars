//
//  HackedScrollersUserDefaults.m
//  LionScrollbars
//
//  Created by Dain Kaplan on 1/28/12.
//  Copyright 2012 Dain Kaplan. All rights reserved.
//

#import "HackedScrollersUserDefaults.h"
#import "NSObject+DefaultsAdditions.h"

NSString* const kLsbSettingsChangedNotification = @"LsbSettingsChangedNotification";

NSString* const kLsbRestyleLegacyScrollers = @"LsbRestyleLegacyScrollers";
NSString* const kLsbRestyleOverlayScrollers = @"LsbRestyleOverlayScrollers";
NSString* const kLsbScrollerKnobMinAlpha = @"LsbScrollerKnobMinAlpha";
NSString* const kLsbScrollerTrackMinAlpha = @"LsbScrollerTrackMinAlpha";
NSString* const kLsbUseGradient = @"LsbUseGradient";
NSString* const kLsbDrawBackgrounds = @"LsbDrawBackgrounds";
NSString* const kLsbRoundedCorners = @"LsbRoundedCorners";


void setHackedScrollerSettingsDefaults(HackedScrollerSettings *_settings)
{
	_settings->restyleLegacyScrollers = NO;
	_settings->restyleOverlayScrollers = NO;
	
	// Legacy settings
	_settings->useGradient = YES;
	_settings->drawBackgrounds = YES;
	_settings->roundedCorners = YES;
	
	// Overlay settings
	_settings->scrollerKnobMinAlpha = 0.7;
	_settings->scrollerTrackMinAlpha = 0.0;
}

void saveHackedScrollerSettingsToUserDefaults(HackedScrollerSettings *_settings)
{
	[NSObject setUserDefaultsValue:_settings->restyleLegacyScrollers ? @"true" : @"false" forSetting:kLsbRestyleLegacyScrollers identifer:nil];
	[NSObject setUserDefaultsValue:_settings->restyleOverlayScrollers ? @"true" : @"false" forSetting:kLsbRestyleOverlayScrollers identifer:nil];
	
	// Overlay settings
	[NSObject setUserDefaultsValue:[[NSNumber numberWithFloat: _settings->scrollerKnobMinAlpha] stringValue] forSetting:kLsbScrollerKnobMinAlpha identifer:nil];
	[NSObject setUserDefaultsValue:[[NSNumber numberWithFloat: _settings->scrollerTrackMinAlpha] stringValue] forSetting:kLsbScrollerTrackMinAlpha identifer:nil];
	
	// Legacy settings
	[NSObject setUserDefaultsValue:_settings->roundedCorners ? @"true" : @"false" forSetting:kLsbRoundedCorners identifer:nil];
	[NSObject setUserDefaultsValue:_settings->useGradient ? @"true" : @"false" forSetting:kLsbUseGradient identifer:nil];
	[NSObject setUserDefaultsValue:_settings->drawBackgrounds ? @"true" : @"false" forSetting:kLsbDrawBackgrounds identifer:nil];
}

HackedScrollerSettings loadHackedScrollerSettingsFromUserDefaults() {
	HackedScrollerSettings _settings;
	setHackedScrollerSettingsDefaults(&_settings);
	NSString *restyleLegacy = [NSObject userDefaultsValueForSetting: kLsbRestyleLegacyScrollers];
	NSLog(@"restyleLegacy = %@", restyleLegacy);
	if (restyleLegacy != nil) {
		_settings.restyleLegacyScrollers = [restyleLegacy boolValue];
	}
	NSString *restyleOverlay = [NSObject userDefaultsValueForSetting: kLsbRestyleOverlayScrollers];
	NSLog(@"restyleLegacy = %@", restyleOverlay);
	if (restyleOverlay != nil) {
		_settings.restyleOverlayScrollers = [restyleOverlay boolValue];
	}
	NSString *useGradient = [NSObject userDefaultsValueForSetting: kLsbUseGradient];
	NSLog(@"useGradient = %@", useGradient);
	if (useGradient != nil) {
		_settings.useGradient = [useGradient boolValue];
	}
	NSString *drawBg = [NSObject userDefaultsValueForSetting: kLsbDrawBackgrounds];
	NSLog(@"drawBg = %@", drawBg);
	if (drawBg != nil) {
		_settings.drawBackgrounds = [drawBg boolValue];
	}
	NSString *rounded = [NSObject userDefaultsValueForSetting: kLsbRoundedCorners];
	NSLog(@"rounded = %@", drawBg);
	if (drawBg != nil) {
		_settings.roundedCorners = [rounded boolValue];
	}
	NSString *knobAlpha = [NSObject userDefaultsValueForSetting: kLsbScrollerKnobMinAlpha];
	NSLog(@"knobAlpha = %@", knobAlpha);
	if (knobAlpha != nil) {
		_settings.scrollerKnobMinAlpha = [knobAlpha floatValue];
	}
	NSString *trackAlpha = [NSObject userDefaultsValueForSetting: kLsbScrollerTrackMinAlpha];
	NSLog(@"trackAlpha = %@", trackAlpha);
	if (trackAlpha != nil) {
		_settings.scrollerTrackMinAlpha = [trackAlpha floatValue];
	}
	return _settings;
}
