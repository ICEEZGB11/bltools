import os
import sys
import glob

env = Environment(ENV=os.environ)
cwd = os.getcwd()

def lib(path):
	return File(cwd + "/lib/" + env["LIBPREFIX"] + path + env["LIBSUFFIX"])
	
if sys.platform == "win32":
	cxxflags = ["/EHsc"]
	linkflags = []
	libs = [lib("libboost_system-vc90-mt-s-1_47"),lib("libboost_date_time-vc90-mt-s-1_47"),lib("assimp")]
else:
	cxxflags = []
	linkflags = []
	libs = [lib("assimp"),lib("boost_system"),lib("boost_date_time")]
	
env["CXXFLAGS"] = cxxflags
env["LINKFLAGS"] = linkflags

src = glob.glob("src/*.cc")
obj = env.Object(source=src)

env.Program(target="3dtoblb",source=obj,LIBPATH=["../libs/"],LIBS=libs)
