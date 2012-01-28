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
#import "NSObject+DefaultsAdditions.h"
#import "HackedScrollers+DefaultsAdditions.h"

@implementation LSBPlugin

- (id)init
{
    self = [super init];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}

- (void)receivedNotification:(NSNotification *)aNotification
{
	// TODO
	NSLog(@"Got notification (thread: %@)", [NSThread currentThread]);
	[HackedOverlayScroller loadUserDefaults];
	[HackedLegacyScroller loadUserDefaults];
	[self redrawScrollers:YES];
}

- (void)install
{
	static BOOL __installed = NO;
	if (__installed) return;
	__installed = YES;
	[self initializeScrollbarHacks:NO];
	
	[[NSDistributedNotificationCenter defaultCenter] addObserver:self selector:@selector(receivedNotification:) name:kLsbSettingsChangedNotification object:nil suspensionBehavior:NSNotificationSuspensionBehaviorDeliverImmediately];
	
	NSLog(@"LSBPlugin installed");
}

- (void) initializeScrollbarHacks:(BOOL)force
{
	// This probably gets called before this by the initialize class method in the category??
	BOOL hackOverlays = [HackedOverlayScroller shouldRestyleOverlayScrollers];;
	BOOL hackLegacy = [HackedLegacyScroller shouldRestyleLegacyScrollers];
	if (hackOverlays || force) {
		[NSScrollerImpHack lsb_initializeOverylayHack];
	}
	if (hackLegacy || force) {
		[NSScrollerImpHack lsb_initializeLegacyHack];
	}
	[HackedOverlayScroller loadUserDefaults];
	[HackedLegacyScroller loadUserDefaults];
}

- (void)dealloc
{
	[[NSDistributedNotificationCenter defaultCenter] removeObserver:self];
	[super dealloc];
}

- (void)redrawScrollers:(BOOL)force 
{
	BOOL hackOverlays = [HackedOverlayScroller shouldRestyleOverlayScrollers];;
	BOOL hackLegacy = [HackedLegacyScroller shouldRestyleLegacyScrollers];
	if (hackOverlays || hackLegacy || force) {
		//NSRect _frame = [[NSApp mainWindow] frame];
		//NSRect frame = NSInsetRect(_frame, 0, 1);
		//[[NSApp mainWindow] setFrame:frame display:YES animate:NO];
		//[[NSApp mainWindow] setFrame:_frame display:YES animate:NO];
		// This is slower but doesn't force the jitter.
		[[NSApp mainWindow] setViewsNeedDisplay:YES];
		[[NSApp mainWindow] display];
	}
}

#pragma mark class-level methods

+ (void)initialize 
{
	NSLog(@"LSB: initialize");
	LSBPlugin* plugin = [LSBPlugin sharedInstance];
	[plugin install];
}

+ (void) load
{
	NSLog(@"LSB: load");
	LSBPlugin* plugin = [LSBPlugin sharedInstance];
	[plugin install];
	[plugin redrawScrollers:NO];
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
