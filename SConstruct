import os,glob

env = Environment()
cwd = os.getcwd()

def lib(path):
	return File(cwd + "/lib/" + env["LIBPREFIX"] + path + env["LIBSUFFIX"])

src = glob.glob("src/*.cc")
libs = [lib("assimp"),lib("boost_system"),lib("boost_date_time"),lib("boost_filesystem")]
obj = env.Object(source=src)

env.Program(target="3dtoblb",source=obj,LIBPATH=["../libs/"],LIBS=libs)
