//
//  LSBPlugin.h
//  LionScrollbarsSIMBLBundle
//
//  Created by Dain Kaplan on 1/22/12.
//  Copyright 2012 Dain's place. All rights reserved.
//

// TODO: Think about using NSDistributedNotificationCenter to update settings real-time.
@interface LSBPlugin : NSObject {
	NSInteger logLevel;
	BOOL aggressiveScrollerHacking;
}

- (void) initializeScrollbarHacks:(BOOL)force;
- (void) redrawScrollers:(BOOL)force;
- (void) install;
+ (void) load;
+ (LSBPlugin*) sharedInstance;

@property (readwrite, assign) NSInteger logLevel;
@property (readwrite, assign) BOOL aggressiveScrollerHacking;

@end
