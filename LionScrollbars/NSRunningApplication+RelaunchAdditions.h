//
//  NSRunningApplication+RelaunchAdditions.h
//  LionScrollbars
//
//  Created by Dain Kaplan on 1/20/12.
//  Copyright 2012 Dain Kaplan <DK@tempura.org>
//

#import <AppKit/AppKit.h>

// Adds a category to NSRunningApplication for convenient operations, like relaunching apps.

typedef BOOL (^ConfirmRelaunchBlock)(NSRunningApplication *);

@interface NSRunningApplication (RelaunchAdditions)

// This could (should) probably be a private category method instead.
+ (void) launchAppInBackgroundWithBundleIdentifier:(NSString *)identifier;

// Terminates and relaunches the running application.
+ (void) terminateAndLaunchRunningApp:(NSRunningApplication *)app;

// Pass null for the ConfirmRelaunchBlock if confirmation is not necessary. 
+ (void) relaunchAppsWithBundleIdentifier:(NSString *)identifier 
				   usingConfirmationBlock: (ConfirmRelaunchBlock)confirmRelaunch;
@end
