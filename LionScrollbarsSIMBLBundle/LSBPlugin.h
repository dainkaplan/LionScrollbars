//
//  LSBPlugin.h
//  LionScrollbarsSIMBLBundle
//
//  Created by Dain Kaplan on 1/22/12.
//  Copyright 2012 Dain's place. All rights reserved.
//

// TODO: Think about using NSDistributedNotificationCenter to update settings real-time.
@interface LSBPlugin : NSObject

- (void) initializeScrollbarHacks:(BOOL)force;
- (void) redrawScrollers:(BOOL)force;
- (void) install;
+ (void) load;
+ (LSBPlugin*) sharedInstance;

@end
