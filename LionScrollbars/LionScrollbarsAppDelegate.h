//
//  LionScrollbarsAppDelegate.h
//  LionScrollbars
//
//  Created by Dain Kaplan on 7/31/11.
//  Copyright 2011-2012 Dain Kaplan <dk@tempura.org>. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "OnOffSwitchControl.h"

@interface LionScrollbarsAppDelegate : NSObject <NSApplicationDelegate, NSWindowDelegate, NSTableViewDelegate, NSTableViewDataSource> {
	NSWindow *window;
	IBOutlet NSComboBox *applicationRunningComboBox;
	IBOutlet NSButton *resetAllButton;
	IBOutlet NSTableView *applicationsTableView;
	IBOutlet NSPopUpButton *systemDefaultPopUpButton;
	IBOutlet NSTextField *applicationCount;
	NSMutableArray *applications;
	NSSearchField *searchField;
	NSString *tmpSettingValue;
	NSTabView *tabView;
	OnOffSwitchControl *pluginStatusToggle;
	NSTextField *pluginStatusLabel;
	NSTabView *simblNotFoundView;
	NSTabView *simblFoundView;
	NSScrollView *overylayScrollersPreview;
	NSScrollView *legacyScrollersPreview;
	NSView *pluginSettingsView;
	OnOffSwitchControl *settingOverlayScrollersToggle;
	OnOffSwitchControl *settingLegacyScrollersToggle;
	NSSlider *settingKnobAlpha;
	NSSlider *settingTrackAlpha;
	OnOffSwitchControl *settingUseGradient;
	OnOffSwitchControl *settingDrawBackground;
	OnOffSwitchControl *settingRoundedCorners;
}
@property (assign) IBOutlet OnOffSwitchControl *settingRoundedCorners;
@property (assign) IBOutlet OnOffSwitchControl *settingDrawBackground;
@property (assign) IBOutlet OnOffSwitchControl *settingUseGradient;
@property (assign) IBOutlet NSSlider *settingTrackAlpha;
@property (assign) IBOutlet NSSlider *settingKnobAlpha;
@property (assign) IBOutlet OnOffSwitchControl *settingLegacyScrollersToggle;
@property (assign) IBOutlet OnOffSwitchControl *settingOverlayScrollersToggle;
@property (assign) IBOutlet NSView *pluginSettingsView;
@property (assign) IBOutlet NSScrollView *legacyScrollersPreview;
@property (assign) IBOutlet NSScrollView *overylayScrollersPreview;
@property (assign) IBOutlet NSTabView *tabView;
@property (assign) IBOutlet OnOffSwitchControl *pluginStatusToggle;
@property (assign) IBOutlet NSTextField *pluginStatusLabel;
@property (assign) IBOutlet NSTabView *simblNotFoundView;
@property (assign) IBOutlet NSTabView *simblFoundView;

@property (assign) IBOutlet NSWindow *window;
@property (retain) NSMutableArray *applications;
@property (retain) NSMutableArray *filteredApplications;
@property (assign) IBOutlet NSSearchField *searchField;

- (IBAction)saveLegacySettings:(id)sender;
- (IBAction)saveOverlaySettings:(id)sender;
- (IBAction)performFilter:(id)sender;
- (IBAction)changePluginStatus:(id)sender;
- (IBAction)popUpButtonValueChanged:(id)sender;
- (IBAction)resetAllClicked:(id)sender;
- (IBAction)installSimbl:(id)sender;
- (IBAction)readmoreAboutSimbl:(id)sender;
- (IBAction)viewSimblLicense:(id)sender;

@end
