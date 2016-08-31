'''clumpines_cmd.exe---------------------------------------------------------'''
'''Returns the average absolute class level clumpiness error between 2 maps '''
import sys
import os
import numpy as np

'''Take inputs from the command line that must be specified for the calcualtion
of clumpiness
Format:
sys.argv[0]: Python program name (implicit, can't be skipped)
sys.argv[1]: Map 1 path
sys.argv[2]: Map 2 path
sys.argv[3]: Mask path
sys.argv[4]: Number of passive classes
sys.argv[5]: Number of feature classes
''' 

#map1_path=str(sys.argv[1])
#map2_path=str(sys.argv[2])
#mask_path=str(sys.argv[3])

#map1_path = "/home/a1091793/Documents/Modelling/RunMetroCal/individual_2/replicate_0/Data2/lu1989.asc" 
#map2_path = "/home/a1091793/Documents/Modelling/RunMetroCal/individual_2/replicate_0/Data2/lu2000.asc" 
#mask_path = "/home/a1091793/Documents/Modelling/RunMetroCal/individual_2/replicate_0/Data2/region.asc" 

map2_path = r"/home/a1091793/Documents/Modelling/Run/individual_0/replicate_0/Data2/lu2000.asc"
map1_path = r"home/a1091793/Documents/Modelling/Run/individual_0/replicate_0/Log/Land_use/Land use map_2000-Jan-01 00_00_00.rst"
mask_path = r"/home/a1091793/Documents/Modelling/Run/individual_0/replicate_0/Data2/region.asc"


from read_map import read_map
import numpy as np
from clumpy_module import clumpiness_index
'''Maps----------------------------------------------------------------------'''
map1=read_map(map1_path)
map2=read_map(map2_path)
mask=read_map(mask_path)
'''Clumpiness_indices--------------------------------------------------------'''
CLUMPY1=clumpiness_index(map1,mask)
CLUMPY2=clumpiness_index(map2,mask)
'''Average_absolute_clumpiness_error-----------------------------------------'''
luc=np.amax(map1)+1
#pas=int(sys.argv[4])
#fea=int(sys.argv[5])
pas = 3 
fea = 3
act=luc-(fea+pas)
ACE=[0]*act
for i in range(pas,luc-fea):
    ACE[i-pas]=abs(CLUMPY1[i]-CLUMPY2[i])
AACE=sum(ACE)/len(ACE)
print AACE