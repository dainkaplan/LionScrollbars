//
//  PopUpButtonCellView.h
//  LionScollbars
//
//  Created by Dain Kaplan on 7/31/11.
//  Copyright 2011-2012 Dain Kaplan <dk@tempura.org>. All rights reserved.
//

#import <AppKit/AppKit.h>

@interface PopUpButtonCellView : NSTableCellView {
	IBOutlet NSPopUpButton *popUpButton;
}

@property (assign) NSPopUpButton *popUpButton;

@end
