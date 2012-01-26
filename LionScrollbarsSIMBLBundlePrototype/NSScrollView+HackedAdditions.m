//
//  NSScrollView+HackedAdditions.m
//  ScrollbarInject
//
//  Created by Dain Kaplan on 1/20/12.
//  Copyright 2012 Dain's place. All rights reserved.
//

#import "NSScrollView+HackedAdditions.h"
#import "HackedScroller.h"
#import "LSBCustomScroller.h"
#import "Hacking.h"

@interface NSScroller (Private) 
- (void) setOverlayScrollerKnobAlpha:(CGFloat)alpha;
- (void) setOverlayScrollerTrackAlpha:(CGFloat)alpha;
@end

@interface NSScrollView (Renamed) 
- (void) orig_tile;
- (Class) orig__verticalScrollerClass;
- (Class) orig__horizontalScrollerClass;
@end

@implementation NSScrollView (HackedAdditions)

+ (void) lsb_initialize
{
	static BOOL __inited = NO;
	if (__inited) {
		return;
	}
	__inited = YES;
	NSLog(@"NSScrollView (HackedAdditions): lsb_initialize: Swizzling methods...");
	Hacking_ShouldLogStatus(YES);
	
	// tile
	Hacking_CopyMethod([self class], @selector(tile), @selector(orig_tile), YES);
	Hacking_CopyMethod([self class], @selector(lsb_tile), @selector(tile), NO);
}

+ (void) lsb_setMinKnobAlpha:(CGFloat)alpha
{
	[HackedScroller setMinKnobAlpha: alpha];
}
+ (void) lsb_setMinTrackAlpha:(CGFloat)alpha
{
	[HackedScroller setMinTrackAlpha: alpha];	
}

+ (void) initialize
{
	NSLog(@"NSScrollView (HackedAdditions): initialize");
	[NSScrollView lsb_initialize];
}

+ (Class) lsb_scrollerClass
{
	return [HackedScroller class];
}

+ (void) lsb_takeoverScrollers:(NSScrollView *)view
{
	// Dynamically change the instances class so that the hacked class gets the messages.
	Class cls = [NSScrollView lsb_scrollerClass];
	if ([view hasVerticalScroller]) {
		NSScroller *vert = [view verticalScroller];
		if (![vert isMemberOfClass: cls]) {
			NSLog(@"v-scrollbar: %@", [vert className]);
			object_setClass(vert, cls);
			[vert setOverlayScrollerKnobAlpha:-1];
			[vert setOverlayScrollerTrackAlpha:-1];
		}
	}
	
	if ([view hasHorizontalScroller]) {
		NSScroller *hori = [view horizontalScroller];
		if (![hori isMemberOfClass: cls]) {
			NSLog(@"h-scrollbar: %@", [hori className]);
			object_setClass(hori, cls);
			[hori setOverlayScrollerKnobAlpha:-1];
			[hori setOverlayScrollerTrackAlpha:-1];
		}
	}
}

- (void) lsb_tile
{
	[NSScrollView lsb_takeoverScrollers:(NSScrollView *)self];
	[self orig_tile];
}

@end
