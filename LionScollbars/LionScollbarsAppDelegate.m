//
//  LionScollbarsAppDelegate.m
//  LionScollbars
//
//  Created by Dain Kaplan on 7/31/11.
//  Copyright 2011-2012 Dain Kaplan <dk@tempura.org>. All rights reserved.
//

#import "LionScollbarsAppDelegate.h"
#import "PopUpButtonCellView.h"
#import "ScrollbarsDefaultsManager.h"

const NSInteger kSettingSystemDefault = -1;
const NSInteger kSettingAutomatic = 0;
const NSInteger kSettingWhenScrolling = 1;
const NSInteger kSettingAlways = 2;

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

@interface LionScollbarsAppDelegate()
- (AppInfo *)appInfoForPackageFoundAtPath:(NSString *)fullPath;
- (NSInteger)tagFromSetting:(NSString *)setting;
- (NSString *)settingFromTag:(NSInteger)tag;
@end

@implementation LionScollbarsAppDelegate

@synthesize window;
@synthesize applications;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
	self.applications = [NSMutableArray arrayWithCapacity:20];
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
	[applicationsTableView reloadData];
}

- (void)windowWillClose:(NSNotification *)notification
{
	[NSApp terminate:[notification object]];
}

- (IBAction)resetAllClicked:(id)sender {
	
	NSAlert *alert = [[NSAlert alloc] init];
	[alert addButtonWithTitle:@"Reset All"];
	[alert addButtonWithTitle:@"Cancel"];
	[alert setMessageText:[NSString stringWithFormat:@"Really reset all applications?"]];
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
	} else {
		if (row > -1) {
			AppInfo *info = [applications objectAtIndex:row];
			NSLog(@"App Info (new): %@ (%@) = %@", info.name, info.identifier, val);
			[[ScrollbarsDefaultsManager sharedManager] setSettingValue:val forIdentifier:info.identifier];
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
	if ([self.applications count] > row) {
		AppInfo *info = [self.applications objectAtIndex: row];
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

#pragma mark NSTableViewDatasource methods

- (NSInteger)numberOfRowsInTableView:(NSTableView *)aTableView
{
	return [self.applications count];
}

@end
