//
//  ScrollbarInjectAppDelegate.h
//  ScrollbarInject
//
//  Created by Dain Kaplan on 1/20/12.
//  Copyright 2012 Dain's place. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface ScrollbarInjectAppDelegate : NSObject <NSApplicationDelegate> {
	NSWindow *window;
	NSScrollView *scrollView;
	NSImageView *imageView;
	NSView *mainView;
	NSTextField *statusLabel;
}

@property (assign) IBOutlet NSWindow *window;
@property (assign) IBOutlet NSScrollView *scrollView;
@property (assign) IBOutlet NSImageView *imageView;
@property (assign) IBOutlet NSView *mainView;
@property (assign) IBOutlet NSTextField *statusLabel;

@end
