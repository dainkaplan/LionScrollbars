//
//  LionScollbarsAppDelegate.m
//  LionScollbars
//
//  Created by Dain Kaplan on 7/31/11.
//  Copyright 2011 Dain's place. All rights reserved.
//

#import "LionScollbarsAppDelegate.h"
#import "ComboBoxCellView.h"
#import "DefaultsManager.h"

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
- (NSString *)displayStringFromSetting:(NSString *)setting;
- (NSString *)settingFromDisplayString:(NSString *)display;
@end

@implementation LionScollbarsAppDelegate

@synthesize window;
@synthesize applications;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
	self.applications = [NSMutableArray arrayWithCapacity:20];
	NSString *defaultSettingDisplay = [self displayStringFromSetting:[[DefaultsManager sharedManager] settingValueForIdentifier:nil]];
	[systemDefaultComboBox selectItemWithObjectValue:defaultSettingDisplay];
	
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
	NSLog(@"Number of Applications: %ld", cnt);
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
	//	[alert setInformativeText:@"This ope"];
	[alert setAlertStyle:NSWarningAlertStyle];
	NSInteger res = [alert runModal];
	if (res == NSAlertFirstButtonReturn) {
		for (AppInfo *info in self.applications) {
			[[DefaultsManager sharedManager] setSettingValue:nil forIdentifier:info.identifier];
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
		info.showScrollbarsSetting = [[DefaultsManager sharedManager] settingValueForIdentifier:identifier];
		info.icon = icon;
		NSLog(@"%@ (%@) = %@", info.name, info.identifier, info.showScrollbarsSetting);
	}
	return [info autorelease];
}

#pragma mark NSComboBoxDelegate methods


- (void)comboBoxSelectionDidChange:(NSNotification *)notification
{
	NSComboBox *comboBox = [notification object];
	NSString *val = [comboBox objectValueOfSelectedItem];
	val = [self settingFromDisplayString:val];
	if ([notification object] == systemDefaultComboBox) {
		[[DefaultsManager sharedManager] setSettingValue:val forIdentifier:nil];
	} else {
		tmpSettingValue = [val retain];
	}
}

- (IBAction)rowClicked:(id)sender {
	NSInteger row = [applicationsTableView rowForView:sender];
	if (row > -1) {
		AppInfo *info = [applications objectAtIndex:row];
		NSLog(@"App Info: %@ (%@) = %@", info.name, info.identifier, tmpSettingValue);
		[[DefaultsManager sharedManager] setSettingValue:tmpSettingValue forIdentifier:info.identifier];
		[tmpSettingValue release];
	}
}

#pragma mark settings control methods

- (NSString *)displayStringFromSetting:(NSString *)setting
{
	NSString *ret = @"System Default";
	if ([@"Automatic" isEqualToString:setting]) {
		ret = @"Automatically";
	} else	if ([@"Always" isEqualToString:setting]) {
		ret = @"Always";
	} else if ([@"WhenScrolling" isEqualToString:setting]) {
		ret = @"When scrolling";
	}
	return ret;
}

- (NSString *)settingFromDisplayString:(NSString *)display 
{
	NSString *ret = nil;
	if ([@"Automatically" isEqualToString:display]) {
		ret = @"Automatic";
	} else	if ([@"Always" isEqualToString:display]) {
		ret = @"Always";
	} else if ([@"When scrolling" isEqualToString:display]) {
		ret = @"WhenScrolling";
	}
	return ret;	
}

#pragma mark NSTableViewDelegate methods

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
			ComboBoxCellView *cellView = [tableView makeViewWithIdentifier:identifier owner:self];
			NSString *setting = info.showScrollbarsSetting;
			[[cellView comboBox] selectItemWithObjectValue:[self displayStringFromSetting: setting]];
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

- (id)tableView:(NSTableView *)aTableView objectValueForTableColumn:(NSTableColumn *)aTableColumn row:(NSInteger)rowIndex
{
	return [self.applications objectAtIndex:rowIndex];
}

@end
