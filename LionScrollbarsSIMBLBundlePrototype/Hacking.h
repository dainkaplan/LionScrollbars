//
//  Hacking.h
//  ScrollbarInject
//

#import <Cocoa/Cocoa.h>
#import <objc/objc-class.h>

#ifndef ScrollbarInject_Hacking_h
#define ScrollbarInject_Hacking_h

BOOL Hacking_CopyMethod(Class _class, SEL _fromSelector, SEL _toSelector, BOOL create_if_needed);
void Hacking_ShouldLogStatus(BOOL shouldLog);

#endif
