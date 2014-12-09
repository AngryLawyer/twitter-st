import sys
import os
env = Environment(tools=['default'])

#output executable name
OUTPUT_EXE='TWITTER.PRG'

#we will be building everything in the same directory, where the sources are
OUTPUT_DIR='./bin'

#here we set our tools names 
env["CC"] = 'm68k-atari-mint-gcc'
env["CXX"] = 'm68k-atari-mint-g++'
env["AS"] = 'm68k-atari-mint-as'
env['AR'] = 'm68k-atari-mint-ar'
env['OBJCOPY'] = 'm68k-atari-mint-objcopy'
env['STRIP'] = 'm68k-atari-mint-strip -s'
env['STACK'] = 'm68k-atari-mint-stack'

# here we set default paths to headers and libraries
env["CPPPATH"] = '/usr/m68k-atari-mint/include'
env["LIBPATH"] = '/usr/m68k-atari-mint/lib'


#if we want to add extra defines for C compiler we can specify them here. 'TOS' will show up as '-DTOS' during compilation. This is an example, so you can add anything you like.
env["CDEFINES"] = 'TOS'   

# as above but for C++ compiler
env["CXXDEFINES"] = 'TOSCPP' 

################## Setting flags example
ST_CFLAGS='-s -Os -std=c99 -fomit-frame-pointer -m68000'
ST_CXXFLAGS='-Os -fno-rtti -fno-exceptions -fomit-frame-pointer -m68000' 
ST_LDFLAGS='-s -Os -fomit-frame-pointer -m68000 -Wl,--traditional-format '
ST_ASM_FLAGS = '-m68000'

env["CFLAGS"] = ST_CFLAGS
env["CXXFLAGS"] = ST_CXXFLAGS
env["LDFLAGS"] = ST_LDFLAGS
env["ASFLAGS"] = ST_ASM_FLAGS

########################### main program entry, sources list 
source_files= ["./src/main.c"]
env.Append(LIBS=['gem'])

program = env.Program(target = OUTPUT_EXE,source = source_files)
env.Alias("install", env.Install(OUTPUT_DIR, program))
