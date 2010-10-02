'''
Created on Sep 21, 2010

@author: justin
'''

import math

divisions=32 # Needs to be a power of 2

tableSize = (divisions + 1)
sineTable = []

def generateSineTable():
    incSize = (math.pi/2)/divisions
    radians = 0.0

    for i in range(tableSize+1):
        sineTable.append(math.trunc(round(math.sin(radians) * 255)))
        radians = radians+incSize

# 0 <= div < (tableSize-1)*4        
def mySine(div):
    if div <= divisions:
        return sineTable[div]
    elif div <= (divisions*2):
        return sineTable[(divisions*2)-div]
    elif div <= (divisions*3):
        return -sineTable[div-(divisions*2)]
    else:
        return -sineTable[(divisions*4)-div]

if __name__ == '__main__':
    generateSineTable()
 
    print "static const uint8_t sineTableLength = %s;" % tableSize
    print "static const uint8_t sineWavetableLength = %s;" % ((tableSize-1)*4)
    print "static const unsigned char sineTable[] = {"
    
    for i in range(tableSize-1):
        print "%s, " % sineTable[i]
    
    print "%s};" % sineTable[tableSize-1]
    
#    print "i, table value"
#    for i in range(divisions*4):
#        tableVal = mySine(i)
#        # calcVal = math.trunc(round(math.sin(math.radians(i)) * 255))
#        
#        print "%s, %s" % (i, tableVal) #, calcVal, tableVal-calcVal)
        
    
        