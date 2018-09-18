#!python
import subprocess
import os
import sys
import re  # for regular expression
import shutil
import os.path

#
# convert map file
#
args = sys.argv
if(len(args) != 3):
    quit()

inputfile = open(args[1])
outputfile = open(args[2], 'w')

r1 = re.compile("^\s+(_\w+)")
r2 = re.compile("^\s+([0-9a-f]+)\s+")
line = inputfile.readline() 
while line:
    line = line.replace('\r\n','')   #delete newline
    m1 = r1.search(line)
    if m1:
        line = inputfile.readline() 
        line = line.replace('\r\n','')   #delete newline
        m2 = r2.search(line)
        outputfile.write("0x" + m2.group(1) + " T " + m1.group(1) + "\n")
    line = inputfile.readline()

inputfile.close()
outputfile.close()
