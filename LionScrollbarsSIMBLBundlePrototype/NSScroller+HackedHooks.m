//
//  NSScroller+HackedHooks.m
//  LionScrollbarsSIMBLBundle
//
//  Created by Dain Kaplan on 1/24/12.
//  Copyright 2012 Dain's place. All rights reserved.
//

#import "HackedScroller.h"
#import "NSScroller+HackedHooks.h"
#import "NSScrollView+HackedAdditions.h"
#import "Hacking.h"

@interface NSScroller (PrivateAPI)
- (void) orig_setOverlayScrollerKnobAlpha:(CGFloat)alpha;
- (void) orig_setOverlayScrollerTrackAlpha:(CGFloat)alpha;
@end

@implementation NSScroller (HackedHooks)

+ (void) lsb_initialize
{
	Hacking_ShouldLogStatus(YES);
	// setOverlayScrollerKnobAlpha
	Hacking_CopyMethod([self class], @selector(setOverlayScrollerKnobAlpha:), @selector(orig_setOverlayScrollerKnobAlpha:), YES);
	Hacking_CopyMethod([self class], @selector(lsb_setOverlayScrollerKnobAlpha:), @selector(setOverlayScrollerKnobAlpha:), NO);
	
	// setOverlayScrollerTrackAlpha
	Hacking_CopyMethod([self class], @selector(setOverlayScrollerTrackAlpha:), @selector(orig_setOverlayScrollerTrackAlpha:), YES);
	Hacking_CopyMethod([self class], @selector(lsb_setOverlayScrollerTrackAlpha:), @selector(setOverlayScrollerTrackAlpha:), NO);
}

- (void)lsb_setOverlayScrollerKnobAlpha:(CGFloat)alpha 
{
	[HackedScroller takeoverInstance:self];
	[self orig_setOverlayScrollerKnobAlpha: alpha];
}

- (void)lsb_setOverlayScrollerTrackAlpha:(CGFloat)alpha 
{
	[HackedScroller takeoverInstance:self];
	[self orig_setOverlayScrollerTrackAlpha: alpha];
}

@end
