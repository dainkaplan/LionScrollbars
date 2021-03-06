# Welcome to LionScrollbars v0.5.4!

## What does it do?

LionScrollbars is a program that enables fine-grained control over how scrollbars are displayed in OS X Lion (10.7). It also has (experimental) support for customizing the appearance of scrollbars, such as preventing overlays from fading out, or replacing the "legacy" scrollers with something better looking (this only works on some apps...).

## Why do we need it?

The default behavior for scrollbars in Lion only allows for three settings in System Preferences (always show, always hide, mouse-device specific); these settings apply to ALL applications. However, for some application you might find yourself wishing you could see a scrollbar (such as if you're editing text or code, etc.); with this program you can do that!

Further, if you want to customize the scrollers (prevent the overlay scrollers from fading out, or change how the legacy style scrollers look) now with the SIMBL-plugin, you can!

## How does it work?

Application preferences are stored in `.plist`  files for each application. These preference files allow for overriding system defaults, so we write to these files for any  application for which you wish to override the system default. Unfortunately in OS X Lion a sandboxing mechanism was introduced, which drastically complicates where and how preferences are handled. 

The customized scrollers work via a plugin framework called SIMBL, that allows for loading code into running programs (such as for the Safari PithHelmet extension up to 5.0). The LionScrollbars SIMBL-plugin, when loaded, overrides the extisting scrollbar rendering methods to make the scrollbars look different in some apps.

## Troubleshooting/Q & A

1. **I tried it with App X but it isn't working...**: First, make sure you've __quit and restarted__ the application you want to change scrollbar settings for, as this is necessary for changes to take effect. If it still does not seem to be working, please report an issue (select from top navigation) with the name of the application.
2. **I want to remove all my per-app settings...**: Just click the "reset all" button on the bottom right of the LionScrollbars application window; this will remove the setting from all applications that have it set.
3. **I installed the SIMBL plugin to customize legacy scrollers, but not all apps are being customized...**: Most native OS X apps should work, but some (such as Safari and Xcode) don't. Feel free to report any apps that aren't working. Remember, the customization feature is experimental...
4. **Customized legacy scrollers take a second to initialize in some apps...**: This is a limitation of the technique used to override the scrollbars. Sorry.

## Revision History ##

### v0.5.4 ###

* App now broadcasts scrollbar settings changed notification so most (?) apps don't need restart.

### v0.5.3 ###

* Backed off behavior to not override non-stock NSScrollers (subsclasses are left alone).
* Added link to online help wiki.

### v0.5.2 ###

* BUG #7: Regression that broke the system default setting popup (fixed).

### v0.5.1 ###

* Switched selectors on "Appearance" tab to use an iOS-style toggle switch intead of SegmentedControl.

### v0.5 ###

* Added appearance tab for installing SIMBL/configuring SIMBL plugin for customizing scroller appearance across apps.

### v0.4 ###

* Added filter textfield for quickly finding the app whose settings you want to change.
* SIMBL plugin code has been added, but is not linked to UI (only available in source).

### v0.3 ###

* Added prompt for restarting target app from within LionScrollbars.
* Localized Popup Dialogs.

### v0.2.1 ###

* Fixed embarrasing typo.
* Added credits for Japanese localization.

# Disclaimer/Licensing (BSD 3-clause license)

	Copyright (c) 2011-2012, Dain Kaplan
	All rights reserved.

	Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

	  - Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
	  - Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
	  - Neither the name of Dain Kaplan nor the names of contributors may be used to endorse or promote products derived from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


# The nitty-gritty on Scrollbar overriding (via SIMBL)

This is complicated, and already explained in the following post of mine: http://rants.tempura.org/2012/01/22/hacking-scrollbars.html

# The nitty-gritty on Scrollbar preferences

The information below is intended to be for informational purposes only (not fine examples of excellently written code).

Basically it boils down to changing the value for a setting called `AppleShowScrollBars`. The three possible values for this setting are:

- "Automatic" ("Automatically based on input device", the default)
- "WhenScrolling" ("When scrolling")
- "Always" ("Always")

Setting this setting alone affects the entire system, where setting it for a specific application (using the appropriate identifier) sets it for that application. There are a number of ways to get at this setting, either via the command line or in code through use of APIs. Each method is explained below.

## How to change scrollbar behavior on a per-app basis:

(Examples for toggling scrollbars for TextMate)

    defaults write com.macromates.TextMate AppleShowScrollBars Always
    defaults delete com.macromates.TextMate AppleShowScrollBars
    defaults read com.macromates.TextMate AppleShowScrollBars

## Or Globally:

    defaults write -g AppleShowScrollBars Always

## OS X Lion (10.7) 

Lion has sandboxing of certain apps (if an application declares itself as "sandboxed"), which we need to account for since this means the settings are written within the sandbox rather than the old place.

To check if an app will be sandboxed, we can look for a `Contents/_CodeSignature` directory within the `AppName.app` package. This is not foolproof (?), but maybe good enough. If an app is sandboxed, then instead of writing to `~/Library/Preferences/com.company.AppName.plist` (which would be where `[NSUerDefaults persistentDomainForName:]` would read from), you must look in `~/Library/Containers/Data/Library/Preferences/com.company.AppName.plist`. This has to be done manually by reading in and writing out the file, using `[NSDictionary readFile:]`. It has to be done manually because the new sandboxing mechanism is designed not to let applications interfere with each other.

The older way using CoreFoundation to read/write settings therefore does not work for sandboxed apps (code snippet below).

    CFPreferencesSetAppValue((CFStringRef)kAppleShowScrollBarsKey, (CFStringRef)value, (CFStringRef)identifier);
    CFPreferencesAppSynchronize((CFStringRef)identifier);

Again, it does not work because it is not looking in the sandboxed locations.

The terminal command `defaults` seems to know about the sandboxed location for some apps, however, but not all.
Some preferences it finds properly within the sandbox, but not all (for example, TextEdit it does not seem to find). 
So, one workaround idea of simple using `/usr/bin/defaults` for reading/writing preferences will not work in all cases. 

There does not seem to be consistency for settings at all. Even if apps should not be able to write to the sandbox for other apps, there should be a programmatic way to access them without trying to read/write `.plist` files yourself. C'mon, Apple! :)

## Reading/Writing preferences via NSUserDefaults

The `NSUserDefaults` class has methods for accessing settings. These don't work for sandboxed preferences.

	- (NSString *)settingForIdentifier:(NSString *)identifier 
	{
		NSString *setting = nil;
		NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
		if (identifier == nil) {
			identifier = NSGlobalDomain;
		}
		NSDictionary *appDefaults = [defaults persistentDomainForName:identifier];
		if (appDefaults != nil) {
			setting = [appDefaults valueForKey:kAppleShowScrollBarsKey];
		}
		return setting;
	}
	- (void)setSettingValue:(NSString *)value forIdentifier:(NSString *)identifier 
	{
		NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
		NSMutableDictionary *appDefaults = nil;
		if (identifier == nil) {
			identifier = NSGlobalDomain;
		}
		appDefaults = [[defaults persistentDomainForName:identifier] mutableCopy];
		if (appDefaults == nil) {
			appDefaults = [NSMutableDictionary dictionary];
		}
		[appDefaults setValue:value forKey:kAppleShowScrollBarsKey];
		[defaults setPersistentDomain:appDefaults forName:identifier];
		[defaults synchronize];
	}
	
## Reading/Writing preferences via CoreFoundation

CoreFoundation (CF) has a C API for reading/writing preferences (does not work for sandboxed applications).

	CFPreferencesSetAppValue((CFStringRef)kAppleShowScrollBarsKey, (CFStringRef)value, (CFStringRef)identifier);
	CFPreferencesAppSynchronize((CFStringRef)identifier);

## Reading/Writing via `NSTask` and `/usr/bin/defaults`

You can also programmatic run `/usr/bin/defaults` for changing preferences with an `NSTask`, but this fails for select apps (such as TextEdit)...

	- (NSString *)askSystemGetSettingWithIdentifier:(NSString*)identifier
	{
		if (identifier == nil) {
			identifier = @"-g";
		}
		NSArray *arguments;
		arguments = [NSArray arrayWithObjects:@"read", identifier, kAppleShowScrollBarsKey, nil];
		NSString *ret = [self runSystemDefaultsWithArguments:arguments];
		ret = [self settingFromDisplayString:[self displayStringFromSetting:ret]];
		return ret;
	}
    
	- (NSString *)askSystemSetSettingForIdentifier:(NSString*)identifier withValue:(NSString *)value 
	{
		if (identifier == nil) {
			identifier = @"-g";
		}
		NSArray *arguments;
		if (value == nil) {
			arguments = [NSArray arrayWithObjects:@"remove", identifier, kAppleShowScrollBarsKey, nil];
		} else {
			arguments = [NSArray arrayWithObjects:@"write", identifier, kAppleShowScrollBarsKey, value, nil];
		}
		return [self runSystemDefaultsWithArguments:arguments];	
	}
    
	// See: http://stackoverflow.com/questions/412562/execute-a-terminal-command-from-a-cocoa-app
	-(NSString *)runSystemDefaultsWithArguments:(NSArray *)arguments
	{
		NSTask *task;
		task = [[NSTask alloc] init];
		[task setLaunchPath: @"/usr/bin/defaults"];
		[task setArguments: arguments];
    
		NSPipe *pipe;
		pipe = [NSPipe pipe];
		[task setStandardOutput: pipe];
		//The magic line that keeps your log where it belongs
		[task setStandardInput:[NSPipe pipe]];
    
		NSFileHandle *file;
		file = [pipe fileHandleForReading];
    
		[task launch];
    
		NSData *data;
		data = [file readDataToEndOfFile];
	
		NSString *string;
		string = [[NSString alloc] initWithData: data encoding: NSUTF8StringEncoding];
		string = [string stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
		NSLog (@"defaults reports: %@", string);
		return string;
	}


## Reading/Writing plist files directly:

You can opt to read/write `.plist` files directly, though you still need to know where to find them (which is what LionScrollbars tries to do, so look at the source if you want to know).

    // From: [http://www.ifans.com/forums/showthread.php?t=64679]
    - (void)readPlist
    {
        NSString *filePath = @"/System/Library/CoreServices/SystemVersion.plist";
	        NSMutableDictionary* plistDict = [[NSMutableDictionary alloc] initWithContentsOfFile:filePath];
        
	        NSString *value;
	        value = [plistDict objectForKey:@"ProductVersion"];
      
	        /* You could now call the string "value" from somewhere to return the 
			   value of the string in the .plist specified, for the specified key. */
	}
    
	- (void)writeToPlist
	{
	    NSString *filePath = @"/System/Library/CoreServices/SystemVersion.plist";
	        NSMutableDictionary* plistDict = [[NSMutableDictionary alloc] initWithContentsOfFile:filePath];
        
	        [plistDict setValue:@"1.1.1" forKey:@"ProductVersion"];
	        [plistDict writeToFile:filePath atomically: YES];
    
	/* This would change the firmware version in the plist to 1.1.1 by initing the 
	   NSDictionary with the plist, then changing the value of the string in the key 
	   "ProductVersion" to what you specified */
	}