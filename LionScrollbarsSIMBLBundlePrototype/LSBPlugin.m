//
//  LSBPlugin.m
//  LionScrollbarsSIMBLBundle
//
//  Created by Dain Kaplan on 1/22/12.
//  Copyright 2012 Dain's place. All rights reserved.
//

#import "LSBPlugin.h"
#import "HackedScroller.h"
#import "NSScroller+HackedHooks.h"
#import "DefaultsManager.h"

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
	[NSScroller lsb_initialize];
	NSString *knobAlpha = [self valueForSetting: @"scrollerKnobMinAlpha"];
	NSLog(@"knobAlpha = %@", knobAlpha);
	if (knobAlpha != nil) {
		[HackedOverlayScroller setMinKnobAlpha: [knobAlpha floatValue]];
	}
	NSString *trackAlpha = [self valueForSetting: @"scrollerTrackMinAlpha"];
	NSLog(@"trackAlpha = %@", trackAlpha);
	if (trackAlpha != nil) {
		[HackedOverlayScroller setMinTrackAlpha: [trackAlpha floatValue]];
	}
}

+ (void)initialize 
{
	NSLog(@"initialize");
	LSBPlugin* plugin = [LSBPlugin sharedInstance];
	[plugin install];
}

/**
 * A special method called by SIMBL once the application has started and all classes are initialized.
 */
+ (void) load
{
	NSLog(@"load");
	LSBPlugin* plugin = [LSBPlugin sharedInstance];
	[plugin install];
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
