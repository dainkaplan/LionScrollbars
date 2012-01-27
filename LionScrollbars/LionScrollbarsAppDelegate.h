//
//  LionScrollbarsAppDelegate.h
//  LionScrollbars
//
//  Created by Dain Kaplan on 7/31/11.
//  Copyright 2011-2012 Dain Kaplan <dk@tempura.org>. All rights reserved.
//

#import <Cocoa/Cocoa.h>

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
}

@property (assign) IBOutlet NSWindow *window;
@property (retain) NSMutableArray *applications;
@property (retain) NSMutableArray *filteredApplications;
@property (assign) IBOutlet NSSearchField *searchField;

- (IBAction)performFilter:(id)sender;
- (IBAction)popUpButtonValueChanged:(id)sender;
- (IBAction)resetAllClicked:(id)sender;
@end
