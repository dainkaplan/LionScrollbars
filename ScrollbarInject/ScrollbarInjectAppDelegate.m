//
//  ScrollbarInjectAppDelegate.m
//  ScrollbarInject
//
//  Created by Dain Kaplan on 1/20/12.
//  Copyright 2012 Dain's place. All rights reserved.
//

#import "ScrollbarInjectAppDelegate.h"
#import <FScript/FScript.h>

@implementation ScrollbarInjectAppDelegate

@synthesize window;
@synthesize scrollView;
@synthesize imageView;
@synthesize mainView;
@synthesize statusLabel;

- (void)loadHacks
{
	NSString* pathToBundle = [[NSBundle mainBundle] pathForResource:@"LionScrollbarsSIMBLBundle" ofType:@"bundle"];
    NSBundle* bundle = [NSBundle bundleWithPath:pathToBundle];
    
    Class plugin = [bundle classNamed:@"LSBPlugin"];
    NSAssert(plugin != nil, @"Couldn't load LSBPlugin");
    [plugin initialize];
}

- (void)applicationWillFinishLaunching:(NSNotification *)aNotification
{
	//[self loadHacks];
}

- (void)awakeFromNib 
{
	//[self loadHacks];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
	[[NSApp mainMenu] addItem:[[FScriptMenuItem alloc] init]];
	
	NSImage *image = [NSImage imageNamed:@"image1"];
	NSLog(@"image: %f %f", [image size].width, [image size].height);
	NSLog(@"image view is %@", imageView == nil ? @"null" : @"not null");
	// NSMakeRect(0, 0, image.size.width, image.size.height)
	imageView = [[NSImageView alloc] init];
	[imageView setImage: image];
	//[imageView setFrameOrigin:NSMakePoint(0,0)];
	[imageView setFrameSize:[image size]];
	[imageView setBoundsSize:[image size]];
	//[imageView setBoundsOrigin:NSMakePoint(0, image.size.height)];
	[imageView setImageScaling: NSScaleToFit];
	[mainView addSubview:imageView];
	[mainView setFrameSize:image.size];
	
	//[[scrollView horizontalScroller] setControlSize:NSSmallControlSize];
	//[[scrollView verticalScroller] setControlSize:NSSmallControlSize];
	//[[scrollView horizontalScroller] setControlSize:NSMiniControlSize];
	//[[scrollView verticalScroller] setControlSize:NSMiniControlSize];
	//[scrollView setNeedsDisplay:YES];
	
	// Scroll the vertical scroller to top
    //if ([scrollView hasVerticalScroller]) {
    //    scrollView.verticalScroller.floatValue = 0;
    //}
	
    // Scroll the contentView to top
    //[scrollView.contentView scrollToPoint:NSMakePoint(0, mainView.frame.size.height - scrollView.contentSize.height)];
	
	//[scrollView setNeedsDisplay:YES];
	
	if ([[NSFileManager defaultManager] fileExistsAtPath:@"/Library/ScriptingAdditions/SIMBL.osax"]) {
		[statusLabel setStringValue:@"SIMBL installation was found."];
	} else {
		[statusLabel setStringValue:@"SIMBL installation was *not* found."];
	}
	[self loadHacks];
}

@end
