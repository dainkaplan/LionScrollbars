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
//#import "HackedScrollers+DefaultsAdditions.h"
#import "HackedScrollersUserDefaults.h"
#import "NSObject+DefaultsAdditions.h"
#import "OnOffSwitchControlCell.h"

const NSInteger const kSettingSystemDefault = -1;
const NSInteger const kSettingAutomatic = 0;
const NSInteger const kSettingWhenScrolling = 1;
const NSInteger const kSettingAlways = 2;

NSString * const kAppRestartDialogOkayButton = @"APP_RESTART_DIALOG/OKAY_BUTTON";
NSString * const kAppRestartDialogMessageTemplate = @"APP_RESTART_DIALOG/MESSAGE_TEMPLATE";
NSString * const kAppRestartDialogRestartButton = @"APP_RESTART_DIALOG/RESTART_BUTTON";
NSString * const kAppRestartDialogInformationText = @"APP_RESTART_DIALOG/INFORMATION_TEXT";

NSString * const kEnablePluginDialogOkayButton = @"ENABLE_PLUGIN_DIALOG/OKAY_BUTTON";
NSString * const kEnablePluginDialogCancelButton = @"ENABLE_PLUGIN_DIALOG/CANCEL_BUTTON";
NSString * const kEnablePluginDialogMessageTemplate = @"ENABLE_PLUGIN_DIALOG/MESSAGE_TEMPLATE";
NSString * const kEnablePluginDialogInformationText = @"ENABLE_PLUGIN_DIALOG/INFORMATION_TEXT";

NSString * const kDisablePluginDialogOkayButton = @"DISABLE_PLUGIN_DIALOG/OKAY_BUTTON";
NSString * const kDisablePluginDialogCancelButton = @"DISABLE_PLUGIN_DIALOG/CANCEL_BUTTON";
NSString * const kDisablePluginDialogMessageTemplate = @"DISABLE_PLUGIN_DIALOG/MESSAGE_TEMPLATE";
NSString * const kDisablePluginDialogInformationText = @"DISABLE_PLUGIN_DIALOG/INFORMATION_TEXT";

NSString * const kResetAllSettingsDialogResetAllButton = @"RESET_ALL_SETTINGS_DIALOG/RESET_ALL_BUTTON";
NSString * const kResetAllSettingsDialogCancelButton = @"RESET_ALL_SETTINGS_DIALOG/CANCEL_BUTTON";
NSString * const kResetAllSettingsDialogMessageText = @"RESET_ALL_SETTINGS_DIALOG/MESSAGE_TEXT";

BOOL simblInstalled(void);
BOOL pluginInstalled(void);
void modifyPlugin(BOOL install);

BOOL simblInstalled()
{
	return [[NSFileManager defaultManager] fileExistsAtPath:@"/Library/ScriptingAdditions/SIMBL.osax"];
}

BOOL pluginInstalled()
{
	return 
	[[NSFileManager defaultManager] fileExistsAtPath:@"/Library/Application Support/SIMBL/Plugins/LionScrollbarsSIMBLBundle.bundle"];
	//|| [[NSFileManager defaultManager] fileExistsAtPath:[@"~/Library/Application Support/SIMBL/Plugins/LionScrollbarsSIMBLBundle.bundle" stringByExpandingTildeInPath]];
}

void modifyPlugin(BOOL install) {
	NSError *error = NULL;
	NSString *path = [[NSBundle mainBundle] pathForResource:@"LionScrollbarsSIMBLBundle" ofType:@"bundle"];
	NSString *libraryPath = [@"/Library/Application Support/SIMBL/Plugins/" stringByExpandingTildeInPath];
	NSString *libraryBundle = [@"/Library/Application Support/SIMBL/Plugins/LionScrollbarsSIMBLBundle.bundle" stringByExpandingTildeInPath];
	if (install) {
		NSLog(@"Copying: %@\nTo: %@", path, libraryPath);
		if (![[NSFileManager defaultManager] fileExistsAtPath:libraryPath]) {
			[[NSFileManager defaultManager] createDirectoryAtPath:libraryPath withIntermediateDirectories:YES attributes:NULL error:&error];
		}
		[[NSFileManager defaultManager] copyItemAtPath:path toPath:libraryBundle error: &error];
	} else {
		NSLog(@"Removing: %@", libraryBundle);
		[[NSFileManager defaultManager] removeItemAtPath:libraryBundle error:&error];
	}
	if (error != NULL) {
		NSLog(@"%@", [error localizedDescription]);
	}
}

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
- (BOOL)confirmPluginEnable;
- (BOOL)confirmPluginDisable;
- (void)updatePluginStatus;
- (void)loadPluginSettings;
- (void)pluginSettingsChanged;
- (BOOL)checkForSimbl;
- (void)checkForSimblRecurring;
@end

@implementation LionScrollbarsAppDelegate

@synthesize settingRoundedCorners;
@synthesize settingDrawBackground;
@synthesize settingUseGradient;
@synthesize settingTrackAlpha;
@synthesize settingKnobAlpha;
@synthesize settingLegacyScrollersToggle;
@synthesize settingOverlayScrollersToggle;
@synthesize pluginSettingsView;
@synthesize legacyScrollersPreview;
@synthesize overylayScrollersPreview;
@synthesize tabView;
@synthesize pluginStatusToggle;
@synthesize pluginStatusLabel;
@synthesize simblNotFoundView;
@synthesize simblFoundView;
@synthesize window;
@synthesize applications;
@synthesize filteredApplications;
@synthesize searchField;

- (void)updatePluginStatus 
{
	if (pluginInstalled()) {
		[self.pluginStatusLabel setStringValue:@"Installed"];
		[self.pluginStatusToggle setState:NSOnState];
	} else {
		[self.pluginStatusLabel setStringValue:@"Not Installed"];
		[self.pluginStatusToggle setIntValue:NSOffState];
	}
}

- (void)loadHacks
{
	NSString* pathToBundle = [[NSBundle mainBundle] pathForResource:@"LionScrollbarsSIMBLBundle" ofType:@"bundle"];
    NSBundle* bundle = [NSBundle bundleWithPath:pathToBundle];
    
    Class plugin = [bundle classNamed:@"LSBPlugin"];
    NSAssert(plugin != nil, @"Couldn't load LSBPlugin");
    [plugin initialize];
	[[plugin sharedInstance] initializeScrollbarHacks:YES];
	
}

- (void)pluginSettingsChanged
{
	// XXX: The scroller plugin listens for this event, so broadcasting it forces a reload of settings.
	[[NSDistributedNotificationCenter defaultCenter] postNotificationName:kLsbSettingsChangedNotification object:nil userInfo:nil deliverImmediately:YES];
}

- (void)loadPluginSettings
{
	// XXX: SIMBL might have injected the plugin into this app, but it might not have. We therefore check to see if the class has been loaded, and if not, load the bundle ourselves.
	if (NSClassFromString(@"HackedLegacyScroller") == nil) {
		[self loadHacks];
	}

	HackedScrollerSettings settings = loadHackedScrollerSettingsFromUserDefaults();	
	[self.settingKnobAlpha setFloatValue: settings.scrollerKnobMinAlpha];
	[self.settingTrackAlpha setFloatValue: settings.scrollerTrackMinAlpha];
	[self.settingRoundedCorners setState: settings.roundedCorners ? NSOnState : NSOffState];
	[self.settingUseGradient setState: settings.useGradient ? NSOnState : NSOffState];
	[self.settingDrawBackground setState: settings.drawBackgrounds ? NSOnState : NSOffState];
	[self.settingLegacyScrollersToggle setState: settings.restyleLegacyScrollers ? NSOnState : NSOffState];
	[self.settingOverlayScrollersToggle setState: settings.restyleOverlayScrollers ? NSOnState : NSOffState];
}

- (void)applicationWillFinishLaunching:(NSNotification *)notification
{
	//NSInteger appearanceTabIndex = [self.tabView indexOfTabViewItemWithIdentifier:@"appearanceTab"];
	//[self.tabView removeTabViewItem: [self.tabView tabViewItemAtIndex:appearanceTabIndex]];
	
	if (![self checkForSimbl]) {
		[self checkForSimblRecurring];
	}
	OnOffSwitchControlCell *switchCell = self.pluginStatusToggle.cell;
	switchCell.onOffSwitchControlColors = OnOffSwitchControlCustomColors;
	[switchCell setOnOffSwitchCustomOnColor:[NSColor colorWithCalibratedRed:0.0 green:0.3 blue:1.0 alpha:0.6f]
								   offColor:[NSColor colorWithCalibratedRed:0.7 green:0.0 blue:0.0 alpha:0.6f]];
}

- (BOOL)checkForSimbl {
	if (simblInstalled()) {
		[self.simblFoundView setHidden:NO];
		[self.simblNotFoundView setHidden:YES];
		[self.pluginSettingsView setHidden:NO];
		[self updatePluginStatus];
		self.legacyScrollersPreview.scrollerStyle = NSScrollerStyleLegacy;
		[self loadPluginSettings];
		return YES;
	} else {
		[self.simblFoundView setHidden:YES];
		[self.simblNotFoundView setHidden:NO];
		[self.pluginSettingsView setHidden:YES];
		return NO;
	}
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
	[alert addButtonWithTitle: NSLocalizedString(kAppRestartDialogRestartButton, @"Restart now")];
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
	} else {
		[[ScrollbarsDefaultsManager sharedManager] setSettingValue:val forIdentifier:nil];
		// TODO: Should flag in the UI someplace app restarts are necessary.
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

#pragma mark Setup simbl

- (void)checkForSimblRecurring
{
	// Check every 2 seconds until it's installed.
	if (![self checkForSimbl]) {
		[self performSelector:@selector(checkForSimblRecurring) withObject:nil afterDelay:2.0];
	}
}

- (IBAction)installSimbl:(id)sender
{
	NSString* pathToPackage = [[NSBundle mainBundle] pathForResource:@"SIMBL-0.9.9" ofType:@"pkg"];
	[[NSWorkspace sharedWorkspace] openFile:pathToPackage];
}

- (IBAction)readmoreAboutSimbl:(id)sender
{
	NSURL *url = [NSURL URLWithString:@"http://www.macupdate.com/app/mac/18351/simbl"];
	[[NSWorkspace sharedWorkspace] openURL:url];
}

- (IBAction)viewSimblLicense:(id)sender
{
	NSURL *url = [NSURL URLWithString:@"http://www.gnu.org/licenses/old-licenses/gpl-2.0-standalone.html"];
	[[NSWorkspace sharedWorkspace] openURL:url];
}

- (IBAction)showHelp:(id)sender {
	NSURL *url = [NSURL URLWithString:@"http://bitbucket.org/dainkaplan/lionscrollbars/wiki/"];
	[[NSWorkspace sharedWorkspace] openURL:url];
}


#pragma mark Plugin config methods

- (IBAction)saveOverlaySettings:(id)sender
{
	HackedScrollerSettings settings = loadHackedScrollerSettingsFromUserDefaults();
	settings.restyleOverlayScrollers = [self.settingOverlayScrollersToggle state] == NSOnState ? YES : NO;
	settings.scrollerKnobMinAlpha = [self.settingKnobAlpha floatValue];
	settings.scrollerTrackMinAlpha = [self.settingTrackAlpha floatValue];
	saveHackedScrollerSettingsToUserDefaults(&settings);
	// Reload them for the previews.
	[self pluginSettingsChanged];
	[self.overylayScrollersPreview flashScrollers];
}

- (IBAction)saveLegacySettings:(id)sender
{
	HackedScrollerSettings settings = loadHackedScrollerSettingsFromUserDefaults();
	settings.restyleLegacyScrollers = [self.settingLegacyScrollersToggle state] == NSOnState ? YES : NO;
	settings.roundedCorners = [self.settingRoundedCorners state] == NSOnState ? YES : NO;
	settings.useGradient = [self.settingUseGradient state] == NSOnState ? YES : NO;
	settings.drawBackgrounds = [self.settingDrawBackground state] == NSOnState ? YES : NO;
	saveHackedScrollerSettingsToUserDefaults(&settings);
	
	// Reload them for the previews.
	[self pluginSettingsChanged];
}

- (IBAction)changePluginStatus:(id)sender
{
	bool enabled = [self.pluginStatusToggle state] == NSOnState;
	if (pluginInstalled() == enabled) return;
	if (enabled) {
		BOOL doit = [self confirmPluginEnable];
		if (doit) {
			modifyPlugin(YES);
		} else {
			[self.pluginStatusToggle setState: NSOffState];
		}
	} else {
		BOOL doit = [self confirmPluginDisable];
		if (doit) {
			modifyPlugin(NO);
		} else {
			[self.pluginStatusToggle setState: NSOnState];
		}
	}
	[self updatePluginStatus];
}

- (BOOL)confirmPluginDisable {
	NSAlert *alert = [[NSAlert alloc] init];
	[alert addButtonWithTitle: NSLocalizedString(kDisablePluginDialogOkayButton, @"Disable")];
	[alert addButtonWithTitle: NSLocalizedString(kDisablePluginDialogCancelButton, @"Cancel")];
	[alert setMessageText:NSLocalizedString(kDisablePluginDialogMessageTemplate, @"Disable plugin?")];
	[alert setInformativeText:NSLocalizedString(kDisablePluginDialogInformationText, @"This will disable the SIMBL-based scroller plugin; the plugin will continue to function in running applications until they are restarted.")];
	[alert setAlertStyle:NSWarningAlertStyle];
	BOOL shouldUninstall = [alert runModal] == NSAlertFirstButtonReturn;
	[alert release];
	return shouldUninstall;
}

- (BOOL)confirmPluginEnable {
	NSAlert *alert = [[NSAlert alloc] init];
	[alert addButtonWithTitle: NSLocalizedString(kEnablePluginDialogOkayButton, @"Install")];
	[alert addButtonWithTitle: NSLocalizedString(kEnablePluginDialogCancelButton, @"Cancel")];
	[alert setMessageText:NSLocalizedString(kEnablePluginDialogMessageTemplate, @"Install plugin?")];
	[alert setInformativeText:NSLocalizedString(kEnablePluginDialogInformationText, @"This will enable the SIMBL-based scroller plugin; running apps will need to be restarted.")];
	[alert setAlertStyle:NSWarningAlertStyle];
	BOOL shouldInstall = [alert runModal] == NSAlertFirstButtonReturn;
	[alert release];
	return shouldInstall;
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
