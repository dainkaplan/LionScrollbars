//
//  LionScollbarsAppDelegate.h
//  LionScollbars
//
//  Created by Dain Kaplan on 7/31/11.
//  Copyright 2011 Dain's place. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface LionScollbarsAppDelegate : NSObject <NSApplicationDelegate, NSWindowDelegate, NSComboBoxDelegate, NSTableViewDelegate, NSTableViewDataSource> {
	NSWindow *window;
	IBOutlet NSComboBox *applicationRunningComboBox;
	IBOutlet NSButton *resetAllButton;
	IBOutlet NSTableView *applicationsTableView;
	IBOutlet NSComboBox *systemDefaultComboBox;
	IBOutlet NSTextField *applicationCount;
	NSMutableArray *applications;
	NSString *tmpSettingValue;
}

@property (assign) IBOutlet NSWindow *window;
@property (retain) NSMutableArray *applications;

- (IBAction)rowClicked:(id)sender;
- (IBAction)resetAllClicked:(id)sender;
@end
