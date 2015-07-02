
Google Play Services wrapper for Marmalade Quick
================================================

This is a 1:1 wrapper for the s3eGooglePlayServices C extension so that you
can use it from Marmalade Quick Lua code. Functionality and usage is the
same as the C++ version.

It's supported on whatever the C++ version supports: Android and iOS as of
Marmalade 7.5.1.

Notes:

- All the paths here are relative to the root folder of your installed
  Marmalade SDK.

- I've started just naming these Quick wrapper projects Qxxxx rather than
  MarmaladeQuickXXX - less typing and easier to include as subprojects if
  folder and mkf have the same name :)


Prerequisites
-------------

1. Marmalade SDK 7.7 or newer for
   
   - The C Google services extension (major update was in 7.5.1)
   - Quick tooling upgrades (in 7.7)

2. Put this project on Marmalade search paths:

  Easiest option is to keep the project in you main github folder. Then, if you
  haven't already, add your github root to the global search by putting the
  following in < Marmalade >/s3e/s3e-default.mkf:

        options { module_path="path/to/my/github/projects/root" }

  Multiple Marmalade installs can pick up your project then.
  
  If you dont have a main github folder, you can add just this project:
  
        options { module_path="path/to/QGooglePlayServices" }


Setup: Add and build this wrapper into Quick
--------------------------------------------

1. Edit quick/quickuser_tolua.pkg and add this new line:

        $cfile "path/to/QGooglePlayServices/QGooglePlayServices.h"

2. Edit quick/quickuser.mkf and add the following to the 'subprojects' block:

        subprojects
        {
            QGooglePlayServices
        }
   
3. Run quick/quickuser_tolua.bat to generate Lua bindings.

4. Rebuild the Quick binaries by running the script(s):
   quick/build_quick_prebuilt.bat etc.

   
Using Google Play Services in your app
--------------------------------------

1. Add the C++ extension to the 'subprojects' block in your app's .mkb file:

        subproject s3eGooglePlayServices

   This bundles platform specific extension libraries (jar, lib etc) in your app
   at deploy time. Forgetting this means all calls will quietly fail!

2. Use the Lua APIs in your app!
   
   The Lua functions match the C++ ones in s3eGooglePlayServices.h.
   
   Make sure you use googlePlayServices.xxx() and not googlePlayServices:xxx()!

The functions are all pretty simple. They either submit score/achievements,
load data asynchronously, or display a GUI.

Typically you would sign in, make a call to load a leaderboard/achievements,
then show the relevant GUI once loaded.

The API does not (currently) provide a way to get scores programmatically but
I'll add that to the leaderboard and achievement callback/events soon.
   
## Events

Quick events are provided to match the C callbacks from s3eGooglePlayServices.
Quick GPS uses a single event, also called "googlePlayServices", which
is registered with the usual system:addEventListener function. The "type" value
of the table passed to your listener indicates which of the callbacks is being.

The types are:

- "status" - shows if user logged in/out. Has these other params:
  - "signedIn": boolean, true for logged in, false for logged out
- TODO: other types!


Example:
        
        function gpsListener(event)
            if event.type == "status" then
                if event.signedIn then
                    dbg.print("user logged in")
                else
                    dbg.print("user logged out or failed to log in")
                end
            elseif event.type == "???" then
                -- do stuff
            end
        end

        if googlePlayServices.isAvailable() then
            if googlePlayServices.init() then
                system:addEventListener("googlePlayServices", gpsListener)
            end
        end
        
        function pressedLoginButton()
            googlePlayServices.signIn()
        end
        
        
See ????? for further
info inc signing-up for and setting up the service online. Check the C++
docs for any known issues or gotchas!


Excluding Google Play services on iOS
-------------------------------------

If you *dont* want it to work on iOS (e.g. you want to use Game Center instead),
you should comment out the following lines (using #) in
< Marmalade >/extensions/s3eGooglePlayServices/s3eGooglePlayServices.mkf:

        subproject google-play-services-iphone
        
        iphone-link-lib="s3eGooglePlayServices"

No need to rebuild anything after that. Calls to the functions on iOS will
then simply do nothing, plus your app wont be bloated with unused libs.


------------------------------------------------------------------------------------------
(C) 2015 Nick Smith.

All code is provided under the MIT license unless stated otherwise:

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
