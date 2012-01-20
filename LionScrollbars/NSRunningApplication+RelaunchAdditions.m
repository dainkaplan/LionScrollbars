//
//  NSRunningApplication+RelaunchAdditions.m
//  LionScrollbars
//
//  Created by Dain Kaplan on 1/20/12.
//  Copyright 2012 Dain Kaplan <DK@tempura.org>
//
// Reference: http://stackoverflow.com/questions/1469534/terminating-another-app-running-cocoa

#import "NSRunningApplication+RelaunchAdditions.h"

@interface NSRunningApplication ()
+ (void)bringCurrentToFront;
@end

@implementation NSRunningApplication (RelaunchAdditions)

+ (void)bringCurrentToFront {
	[NSApp activateIgnoringOtherApps:YES];
}

+ (void) launchAppInBackgroundWithBundleIdentifier:(NSString *)identifier {
	NSWorkspace *ws = [NSWorkspace sharedWorkspace];
	NSLog(@"Launching app: %@", identifier);
	NSWorkspaceLaunchOptions options = NSWorkspaceLaunchNewInstance | NSWorkspaceLaunchDefault;
	// XXX: The NSWorkspaceLaunchWithoutActivation option SHOULD do exactly what we want, but testing seemed to result in the restarted app going rogue on us (backgrounding) after launch; to work around this, we instead bring outselves to the front after we launch the other app normally; this seems to work alright.
	[ws launchAppWithBundleIdentifier: identifier
							  options: options
	   additionalEventParamDescriptor: [NSAppleEventDescriptor nullDescriptor]
					 launchIdentifier: NULL];
	[NSRunningApplication performSelector:@selector(bringCurrentToFront) withObject:nil afterDelay:1.0];

}

+ (void) terminateAndLaunchRunningApp:(NSRunningApplication *)app {
	BOOL terminated = [app terminate];
	if (terminated) {
		[NSRunningApplication launchAppInBackgroundWithBundleIdentifier: [app bundleIdentifier]];
	}
}

+ (void) relaunchAppsWithBundleIdentifier:(NSString *)identifier 
				   usingConfirmationBlock: (ConfirmRelaunchBlock)confirmRelaunch {
	NSArray *runningApps = [NSRunningApplication runningApplicationsWithBundleIdentifier: identifier];
	if ([runningApps count] > 0) {
		if (confirmRelaunch != NULL && confirmRelaunch([runningApps objectAtIndex:0]) == NO) 
			return;
		for (NSRunningApplication* app in runningApps) {
			[NSRunningApplication terminateAndLaunchRunningApp: app];
		}
	}
}

@end
