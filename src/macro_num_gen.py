
fname = "macro_extensions.h"
start = 2**8
stop = 2**16-1

with open(fname, 'w') as file:
    string = "#ifndef MACRO_EXTENSIONS_H\n#define MACRO_EXTENSIONS_H\n"
    file.write(string)
    for i in range(start, stop):
        temp = hex(i)[2:].zfill(len(hex(stop)[2:]))
        string = "#define _B_" + str(i) + " " + "".join([n+',' for n in temp[:-1]]) + temp[-1] + '\n'
        file.write(string)
        if i%(int((start-stop)/40*4))==0:
            p = (i - start)/(stop-start)
            print('['+'*'*int(p*40)+' '*(40-int(p*40))+'] '+str(i-start)+'/'+str(stop-start))
    for i in range(start, stop):
        
    string = "#endif\n"
    file.write(string)
    print('['+'*'*40+'] '+str(stop-start)+'/'+str(stop-start))
