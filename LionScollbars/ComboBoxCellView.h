//
//  ComboBoxCellView.h
//  LionScollbars
//
//  Created by Dain Kaplan on 7/31/11.
//  Copyright 2011 Dain's place. All rights reserved.
//

#import <AppKit/AppKit.h>

@interface ComboBoxCellView : NSTableCellView {
	IBOutlet NSComboBox *comboBox;
}

@property (assign) NSComboBox *comboBox;

@end
