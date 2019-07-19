#!/usr/bin/env python3
import os, shutil

os.mkdir('LEPL1503')

dir = os.scandir('.')

for item in dir:
    if item.name != 'LEPL1503' and (item.is_dir() or item.name == 'course.yaml'):
        try:
            os.mkdir(os.path.join(item.name,'test'))
        except:
            pass  # test directory already existing
        shutil.move('./' + item.name, 'LEPL1503/' + item.name)
        
print("travis_setup done") 
