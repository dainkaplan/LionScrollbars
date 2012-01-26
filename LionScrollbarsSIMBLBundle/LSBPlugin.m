//
//  LSBPlugin.m
//  LionScrollbarsSIMBLBundle
//
//  Created by Dain Kaplan on 1/22/12.
//  Copyright 2012 Dain's place. All rights reserved.
//

#import "LSBPlugin.h"
#import "HackedOverlayScroller.h"
#import "HackedLegacyScroller.h"
#import "NSScrollerImpHack.h"
#import "DefaultsManager.h"

NSString* kLsbRestyleOverlayScrollers = @"LsbRestyleOverlayScrollers";
NSString* kLsbRestyleLegacyScrollers = @"LsbRestyleLegacyScrollers";
NSString* kLsbScrollerKnobMinAlpha = @"LsbScrollerKnobMinAlpha";
NSString* kLsbScrollerTrackMinAlpha = @"LsbScrollerTrackMinAlpha";
NSString* kLsbUseGradient = @"LsbUseGradient";
NSString* kLsbDrawBackgrounds = @"LsbDrawBackgrounds";

@implementation LSBPlugin

- (id)init
{
    self = [super init];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}

- (void)install
{
	static BOOL __installed = NO;
	if (__installed) return;
	__installed = YES;
	[self initializeScrollbarHacks];
	NSLog(@"LSBPlugin installed");
}

- (NSString *)valueForSetting:(NSString *)name
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

- (void) initializeScrollbarHacks
{
	// This probably gets called before this by the initialize class method in the category??
	NSString *overlays = [self valueForSetting: kLsbRestyleOverlayScrollers];
	NSString *legacy = [self valueForSetting: kLsbRestyleLegacyScrollers];
	BOOL hackOverlays = NO;
	BOOL hackLegacy = NO;
	if (overlays != nil && [overlays boolValue] == YES) hackOverlays = YES;
	if (legacy != nil && [legacy boolValue] == YES) hackLegacy = YES;
	if (hackOverlays) {
		[NSScrollerImpHack lsb_initializeOverylayHack];
	}
	if (hackLegacy) {
		[NSScrollerImpHack lsb_initializeLegacyHack];
	}
	NSString *knobAlpha = [self valueForSetting: kLsbScrollerKnobMinAlpha];
	NSLog(@"knobAlpha = %@", knobAlpha);
	if (knobAlpha != nil) {
		[HackedOverlayScroller setMinKnobAlpha: [knobAlpha floatValue]];
	}
	NSString *trackAlpha = [self valueForSetting: kLsbScrollerTrackMinAlpha];
	NSLog(@"trackAlpha = %@", trackAlpha);
	if (trackAlpha != nil) {
		[HackedOverlayScroller setMinTrackAlpha: [trackAlpha floatValue]];
	}
	NSString *useGradient = [self valueForSetting: kLsbUseGradient];
	NSLog(@"useGradient = %@", useGradient);
	if (useGradient != nil) {
		[HackedLegacyScroller setUseGradient: [useGradient boolValue]];
	}
	NSString *drawBg = [self valueForSetting: kLsbDrawBackgrounds];
	NSLog(@"drawBg = %@", drawBg);
	if (drawBg != nil) {
		[HackedLegacyScroller setDrawBackground: [drawBg boolValue]];
	}

}

+ (void)initialize 
{
	NSLog(@"LSB: initialize");
	LSBPlugin* plugin = [LSBPlugin sharedInstance];
	[plugin install];
}

/**
 * A special method called by SIMBL once the application has started and all classes are initialized.
 */
+ (void) load
{
	NSLog(@"LSB: load");
	LSBPlugin* plugin = [LSBPlugin sharedInstance];
	[plugin install];
	NSRect _frame = [[NSApp mainWindow] frame];
	NSRect frame = NSInsetRect(_frame, 1, 0);
	[[NSApp mainWindow] setFrame:frame display:YES animate:NO];
	[[NSApp mainWindow] setFrame:_frame display:YES animate:NO];
}

/**
 * @return the single static instance of the plugin object
 */
+ (LSBPlugin*) sharedInstance
{
	static LSBPlugin* plugin = nil;
	
	if (plugin == nil)
		plugin = [[LSBPlugin alloc] init];
	
	return plugin;
}

@end
