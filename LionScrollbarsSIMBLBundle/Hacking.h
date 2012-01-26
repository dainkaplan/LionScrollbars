//
//  Hacking.h
//  ScrollbarInject
//

#import <Cocoa/Cocoa.h>
#import <objc/objc-class.h>

#ifndef ScrollbarInject_Hacking_h
#define ScrollbarInject_Hacking_h

void Hacking_SwapMethods(Class _srcClass, Class _destClass, SEL _newSel, SEL _oldSel);
void Hacking_SwapClassMethods(Class _srcClass, Class _destClass, SEL _newSel, SEL _oldSel);

BOOL Hacking_CopyMethod(Class _class, SEL _fromSelector, SEL _toSelector, BOOL create_if_needed);
void Hacking_ShouldLogStatus(BOOL shouldLog);

#endif
