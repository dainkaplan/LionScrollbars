//
//  LionScrollbarsAppDelegate.m
//  LionScrollbars
//
//  Created by Dain Kaplan on 7/31/11.
//  Copyright 2011-2012 Dain Kaplan <dk@tempura.org>. All rights reserved.
//

#import "LionScrollbarsAppDelegate.h"
#import "PopUpButtonCellView.h"
#import "ScrollbarsDefaultsManager.h"
#import "NSRunningApplication+RelaunchAdditions.h"

const NSInteger kSettingSystemDefault = -1;
const NSInteger kSettingAutomatic = 0;
const NSInteger kSettingWhenScrolling = 1;
const NSInteger kSettingAlways = 2;

const NSString *kAppRestartDialogOkayButton = @"APP_RESTART_DIALOG/OKAY_BUTTON";
const NSString *kAppRestartDialogMessageTemplate = @"APP_RESTART_DIALOG/MESSAGE_TEMPLATE";
const NSString *kAppRestartDialogRestartButton = @"APP_RESTART_DIALOG/RESTART_BUTTON";
const NSString *kAppRestartDialogInformationText = @"APP_RESTART_DIALOG/INFORMATION_TEXT";

const NSString *kResetAllSettingsDialogResetAllButton = @"RESET_ALL_SETTINGS_DIALOG/RESET_ALL_BUTTON";
const NSString *kResetAllSettingsDialogCancelButton = @"RESET_ALL_SETTINGS_DIALOG/CANCEL_BUTTON";
const NSString *kResetAllSettingsDialogMessageText = @"RESET_ALL_SETTINGS_DIALOG/MESSAGE_TEXT";

#define VALIDATE_SYSTEM_SETTING(x) x = (x < kSettingAutomatic ? kSettingAutomatic : x)

@interface AppInfo : NSObject {
	NSImage *icon;
	NSString *name;
	NSString *identifier;
	NSString *showScrollbarsSetting;
}

@property (retain, readwrite) NSImage *icon;
@property (retain, readwrite) NSString *name;
@property (retain, readwrite) NSString *identifier;
@property (retain, readwrite) NSString *showScrollbarsSetting;

@end

@implementation AppInfo

@synthesize icon;
@synthesize name;
@synthesize identifier;
@synthesize showScrollbarsSetting;

@end

@interface LionScrollbarsAppDelegate()
- (AppInfo *)appInfoForPackageFoundAtPath:(NSString *)fullPath;
- (NSInteger)tagFromSetting:(NSString *)setting;
- (NSString *)settingFromTag:(NSInteger)tag;
@end

@implementation LionScrollbarsAppDelegate

@synthesize tabView;
@synthesize window;
@synthesize applications;
@synthesize filteredApplications;
@synthesize searchField;

- (void)applicationWillFinishLaunching:(NSNotification *)notification
{
	NSInteger appearanceTabIndex = [self.tabView indexOfTabViewItemWithIdentifier:@"appearanceTab"];
	[self.tabView removeTabViewItem: [self.tabView tabViewItemAtIndex:appearanceTabIndex]];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
	 self.applications = [NSMutableArray arrayWithCapacity:20];
	self.filteredApplications = [NSMutableArray arrayWithCapacity:20];
	NSInteger defaultSettingTag = [self tagFromSetting:[[ScrollbarsDefaultsManager sharedManager] settingValueForIdentifier:nil]];
	VALIDATE_SYSTEM_SETTING(defaultSettingTag);
	[systemDefaultPopUpButton selectItemWithTag:defaultSettingTag];
	
	NSError *theError = nil;
	NSArray *contents = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:@"/Applications" error: &theError];
	NSMutableArray *allAppPaths = [NSMutableArray arrayWithCapacity:20];
	
	for (NSString *item in contents) {
		NSString *fullPath = [NSString stringWithFormat:@"/Applications/%@", item];
		BOOL isApp = [[NSWorkspace sharedWorkspace] isFilePackageAtPath:fullPath];
		BOOL isDir = NO;
		[[NSFileManager defaultManager] fileExistsAtPath:fullPath isDirectory:&isDir];
		//NSLog(@"Got item: %@", fullPath);
		if (isApp) {
			[allAppPaths addObject:fullPath];
		} else if (isDir) {
			// Only recurse ONE level-deep.
			NSArray *tmp = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:fullPath error: &theError];
			for (NSString *item2 in tmp) {
				NSString *fullPath2 = [NSString stringWithFormat:@"/%@/%@", fullPath, item2];
				BOOL isApp2 = [[NSWorkspace sharedWorkspace] isFilePackageAtPath:fullPath2];
				if (isApp2) {
					[allAppPaths addObject:fullPath2];
				}
			}
		}
	}	
	for (NSString *path in allAppPaths) {
		AppInfo *info = [self appInfoForPackageFoundAtPath:path];
		if (info != nil) {
			[self.applications addObject:info];
		}
	}
	
	[self.applications sortUsingComparator:^(AppInfo *obj1, AppInfo *obj2) {
		NSString *str1 = obj1.name;
		NSString *str2 = obj2.name;
		return [str1 compare:str2 options:NSCaseInsensitiveSearch];
	}];

	
	NSInteger cnt = [self.applications count];
	applicationCount.stringValue = [NSString stringWithFormat: @"%ld", cnt];
	[self performFilter:self];
}

- (void)windowWillClose:(NSNotification *)notification
{
	[NSApp terminate:[notification object]];
}

- (IBAction)resetAllClicked:(id)sender {
	
	NSAlert *alert = [[NSAlert alloc] init];
	[alert addButtonWithTitle: NSLocalizedString(kResetAllSettingsDialogResetAllButton, @"Reset All")];
	[alert addButtonWithTitle:NSLocalizedString(kResetAllSettingsDialogCancelButton, @"Cancel")];
	[alert setMessageText:[NSString stringWithFormat:NSLocalizedString(kResetAllSettingsDialogMessageText, @"Really reset all applications?")]];
	[alert setAlertStyle:NSWarningAlertStyle];
	NSInteger res = [alert runModal];
	if (res == NSAlertFirstButtonReturn) {
		for (AppInfo *info in self.applications) {
			[[ScrollbarsDefaultsManager sharedManager] setSettingValue:nil forIdentifier:info.identifier];
			info.showScrollbarsSetting = nil;
		}
	} else if (res == NSAlertSecondButtonReturn) {
	}
	[alert release];
	[applicationsTableView reloadData];
}

- (AppInfo *)appInfoForPackageFoundAtPath:(NSString *)fullPath 
{
	AppInfo *info = nil;
	NSBundle *appBundle = [NSBundle bundleWithPath:fullPath];
	NSString *displayName = [[appBundle infoDictionary] valueForKey:(NSString *)kCFBundleNameKey];
	//NSString *iconFileName = [[appBundle infoDictionary] valueForKey:@"CFBundleIconFile"];
	NSImage *icon = [[NSWorkspace sharedWorkspace] iconForFile:fullPath];
	NSString *identifier = [appBundle bundleIdentifier];
	if (identifier != nil && displayName != nil) {
		info = [[AppInfo alloc] init];
		info.name = displayName;
		info.identifier = identifier;
		info.showScrollbarsSetting = [[ScrollbarsDefaultsManager sharedManager] settingValueForIdentifier:identifier];
		info.icon = icon;
		NSLog(@"AppInfo: %@ (%@) = %@", info.name, info.identifier, info.showScrollbarsSetting);
	}
	return [info autorelease];
}

#pragma mark NSComboBoxDelegate methods

- (BOOL)confirmAppRelaunch:(NSRunningApplication *)info {
	NSAlert *alert = [[NSAlert alloc] init];
	[alert addButtonWithTitle: NSLocalizedString(kAppRestartDialogOkayButton, @"OK")];
	[alert setIcon: info.icon];
	[alert addButtonWithTitle: NSLocalizedString(kAppRestartDialogRestartButton, [@"Restart now")];
	[alert setMessageText:[NSString stringWithFormat: NSLocalizedString(kAppRestartDialogMessageTemplate, @"%@ is running."), info.localizedName]];
	[alert setInformativeText:NSLocalizedString(kAppRestartDialogInformationText, @"The application needs to be restarted for changes to take effect. Be sure to save your data.")];
	[alert setAlertStyle:NSWarningAlertStyle];
	BOOL shouldRelaunch = [alert runModal] == NSAlertSecondButtonReturn;
	[alert release];
	return shouldRelaunch;
}

//- (void)comboBoxSelectionDidChange:(NSNotification *)notification
- (IBAction)popUpButtonValueChanged:(id)sender
{
	NSPopUpButton *popup = sender; //[notification object];
	NSInteger tag = [popup selectedTag];
	NSInteger row = [applicationsTableView rowForView:popup];
	NSString *val = [self settingFromTag:tag];
	NSLog(@"Row is: %ld", row);
	if (popup == systemDefaultPopUpButton) {
		[[ScrollbarsDefaultsManager sharedManager] setSettingValue:val forIdentifier:nil];
		// TODO: Should flag in the UI someplace app restarts are necessary.
	} else {
		if (row > -1) {
			AppInfo *info = [filteredApplications objectAtIndex:row];
			NSLog(@"App Info (new): %@ (%@) = %@", info.name, info.identifier, val);
			[[ScrollbarsDefaultsManager sharedManager] setSettingValue:val forIdentifier:info.identifier];
			// TODO: Optionally confirm with user to restart app.
			ConfirmRelaunchBlock block = ^BOOL(NSRunningApplication *app) {
				NSLog(@"Going to show prompt for: %@ (%@)", app.localizedName, app.bundleIdentifier);
				return [self confirmAppRelaunch: app];
			};
			[NSRunningApplication relaunchAppsWithBundleIdentifier:info.identifier usingConfirmationBlock: block];
		}
	}
}

#pragma mark settings control methods

- (NSInteger)tagFromSetting:(NSString *)setting
{
	NSInteger ret = kSettingSystemDefault; // kAppleShowScrollBarsSettingDefault
	if ([kAppleShowScrollBarsSettingAutomatic isEqualToString:setting]) {
		ret = kSettingAutomatic;
	} else if ([kAppleShowScrollBarsSettingWhenScrolling isEqualToString:setting]) {
		ret = kSettingWhenScrolling;
	} else if ([kAppleShowScrollBarsSettingAlways isEqualToString:setting]) {
		ret = kSettingAlways;
	}
	return ret;
}

- (NSString *)settingFromTag:(NSInteger)tag
{
	NSString *ret = nil;
	switch (tag) {
		case kSettingAutomatic:
			ret = kAppleShowScrollBarsSettingAutomatic;
			break;
		case kSettingWhenScrolling:
			ret = kAppleShowScrollBarsSettingWhenScrolling;
			break;
		case kSettingAlways:
			ret = kAppleShowScrollBarsSettingAlways;
			break;
		default: // kSettingSystemDefault
			ret = kAppleShowScrollBarsSettingDefault;
	}
	return ret;
}

#pragma mark NSTableViewDelegate methods

// We don't have a purpose in ever selecting table rows.
- (BOOL)selectionShouldChangeInTableView:(NSTableView *)aTableView
{
	return NO;
}

- (NSView *)tableView:(NSTableView *)tableView
   viewForTableColumn:(NSTableColumn *)tableColumn
                  row:(NSInteger)row {
	
	NSTableCellView *result = nil; 
	if ([self.filteredApplications count] > row) {
		AppInfo *info = [self.filteredApplications objectAtIndex: row];
		NSString *identifier = [tableColumn identifier];
		if ([identifier isEqualToString:@"ApplicationNameIcon"]) {
			NSTableCellView *cellView = [tableView makeViewWithIdentifier:identifier owner:self];
			cellView.textField.stringValue = info.name;
			cellView.imageView.objectValue = info.icon;
			result = cellView;
		} else if([identifier isEqualToString:@"ShowScrollbars"]) {
			PopUpButtonCellView *cellView = [tableView makeViewWithIdentifier:identifier owner:self];
			NSString *setting = info.showScrollbarsSetting;
			[[cellView popUpButton] selectItemWithTag:[self tagFromSetting: setting]];
			result = cellView;
		}
	}
	return result;
}

#pragma mark Search methods
												 
- (IBAction)performFilter:(id)sender {
	NSString *search = [searchField stringValue];
	NSLog(@"Filter text: %@", search);
	[self.filteredApplications removeAllObjects];
	if ([search length] < 1) {
		[self.filteredApplications addObjectsFromArray:self.applications];
	} else if ([self.applications count] > 0) {
		for (AppInfo *app in self.applications) {
			NSRange range = [app.name rangeOfString:search options:NSCaseInsensitiveSearch];
			if (range.location != NSNotFound) {
				[self.filteredApplications addObject:app];
			}
		}
	}
	[applicationsTableView reloadData];
}
												 
#pragma mark NSTableViewDatasource methods

- (NSInteger)numberOfRowsInTableView:(NSTableView *)aTableView
{
	return [self.filteredApplications count];
}

@end
