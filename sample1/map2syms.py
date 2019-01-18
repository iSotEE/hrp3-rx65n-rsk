#!python
import subprocess
import os
import sys
import re  # for regular expression
import shutil
import os.path
import csv

#
# convert map file
#
args = sys.argv
if len(args) != 3 and len(args) != 4:
    quit()

inputfile = open(args[1])
outputfile = open(args[2], 'w')

#
# generate symbols for args[3] (section.csv)
#
if len(args) == 4:
    sections = {}
    while not inputfile.readline().startswith('SECTION'):
        pass
    while True:
        section = inputfile.readline().strip()
        if section == '':
            break
        start, end, _, _ = re.split(' +', inputfile.readline().strip())
        sections[section] = {'start': int(start, 16), 'end': int(end, 16) + 1}
    with open(args[3], 'r') as f:
        reader = csv.DictReader(f)
        for line in reader:
            section = sections[line['section']]
            if line['is_end'] == '0':
                address = section['start']
            else:
                address = (section['end'] + int(line['end_align']) - 1) & ~(int(line['end_align']) - 1)
            outputfile.write("0x{:08x} T {}\n".format(address, line['label']))
        
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
