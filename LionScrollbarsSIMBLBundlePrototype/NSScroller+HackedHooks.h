//
//  NSScroller+HackedHooks.h
//  LionScrollbarsSIMBLBundle
//
//  Created by Dain Kaplan on 1/24/12.
//  Copyright 2012 Dain's place. All rights reserved.
//

#import <AppKit/AppKit.h>

@interface NSScroller (HackedHooks)
+ (void) lsb_initialize;
- (void) lsb_setOverlayScrollerKnobAlpha:(CGFloat)alpha;
- (void) lsb_setOverlayScrollerTrackAlpha:(CGFloat)alpha;
@end
