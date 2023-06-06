import sys
import os
import yarp
from yarpGPT.api import yarpGPT

print("Hi and welcome to yarpGPT")
yarp.Network.init()
if not yarp.Network.checkNetwork():
    print("Yarp server is not running")
    quit(-1)

dir_path = os.path.dirname(os.path.realpath(__file__))
rf = yarp.ResourceFinder()
rf.setVerbose(True)
rf.setDefaultConfigFile(os.path.join(dir_path,'../app/conf/yarpGPT.ini'))
rf.configure(sys.argv)

manager = yarpGPT()
manager.runModule(rf)
