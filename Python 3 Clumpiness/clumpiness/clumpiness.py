'''Clumpiness----------------------------------------------------------------'''
'''Calculates the class level clumpiness for the active classes in a landscape
used to evaluate calibration performance of raster based land use models'''

#Modules
from read_map import read_map
import numpy as np

#Program
'''Import_map_data-----------------------------------------------------------'''

map1_path="C:\\Users\\\Charles\\OneDrive\\Clumpiness\\Example_complex_Randstad\\lu2000.asc"
mask_path="C:\\Users\\\Charles\\OneDrive\\Clumpiness\\Example_complex_Randstad\\region.asc"
map1=read_map(map1_path)

'''Input_data_processing-----------------------------------------------------'''

mapshape=np.shape(map1)
row=mapshape[0]
column=mapshape[1]
luc=np.amax(map1)+1
#luc_names=["Nature","Agriculture","Urban"]

'''Specified_parameters------------------------------------------------------'''
#THESE MUST BE SPECIFIED PRIOR TO RUNNING THE OPTIMISATION

pas=3
fea=3
act=luc-(fea+pas)

'''Masking_maps--------------------------------------------------------------'''
#Checks for a masking maps, generates one if it does not exist.

try: 
    mask_path
except NameError:
    mask=np.zeros(shape=(row,column))
    mask=mask+1
else:
    mask=read_map(mask_path)

'''Populate_adjacency_matrix-------------------------------------------------'''
'''The adjacency matrix is a log of the land use classes along edges present in
a raster landscape. It is counted for all cells in the matrix, aiming to
preserve the links observed between raster cells (referred to as the 
'double-count' method by Mcgarigal et al. 2009; 2014 and similar references). 
The basic idea is such that 
------------
| 1  |  1  | 
------------
is counted as 2 (1,1) adjacencies, &
------------
| 1  |  2  | 
------------
is counted as a (1,2) adjancency and a (2,1) adjacency.      
Following a more complex example:
-----------------------
| 1  |  1  |  2  |  2  |
-----------------------
| 1  |  1  |  2  |  2  |
-----------------------
| 1  |  1  |  2  |  2  |
-----------------------
| 1  |  1  |  2  |  2  |
-----------------------

There are 20 (1,1) edges, 4 (1,2) edges, 4 (2,1) edges, and 20 (2,2) edges. '''

#Composition of adjacencies
adjacency_table=np.zeros(shape=(luc,luc))
count_luc=[0]*luc
for i in range(0,row):
    for j in range(0,column):
        if mask[i,j]>0:
            central=map1[i,j]
            count_luc[central]=count_luc[central]+1
            k=i-1
            if k<0:
                next
            elif mask[k,j]>0:
                link=map1[k,j]
                adjacency_table[central,link]=adjacency_table[central,link]+1
            l=i+1
            if l>=row:
                next
            elif mask[l,j]>0:
                link=map1[l,j]
                adjacency_table[central,link]=adjacency_table[central,link]+1
            m=j-1
            if m<0:
                next
            elif mask[i,m]>0:
                link=map1[i,m]
                adjacency_table[central,link]=adjacency_table[central,link]+1
            n=j+1
            if n>=column:
                next
            elif mask[i,n]>0:
                link=map1[i,n]
                adjacency_table[central,link]=adjacency_table[central,link]+1

'''Calculate_composition_and_proportion--------------------------------------'''

#Calculate the proportion of different land use classes in a landscape
prop=[0]*luc
for i in range(0,luc):
    prop[i]=prop[i]+float(count_luc[i])/sum(count_luc)


'''Calculate_background------------------------------------------------------'''
'''Background is a count of the composition of map edges. It is used for 
calculating clumpiness. It is based on the edge segment matrix, which, based
on the border contained in the region, defines the number of edge segments '''

background=[0]*luc
edge_segment_matrix=np.zeros(shape=(row,column))
for i in range(0,row):
    for j in range(0,column):
        if mask[i,j]==0:
            next
        else:
            if i-1<0:
                edge_segment_matrix[i,j]=edge_segment_matrix[i,j]+1
            else:
                k=mask[i-1,j]
                if k==0:
                    edge_segment_matrix[i,j]=edge_segment_matrix[i,j]+1
            if i+1>=row:
                edge_segment_matrix[i,j]=edge_segment_matrix[i,j]+1
            else:
                l=mask[i+1,j]
                if l==0:
                    edge_segment_matrix[i,j]=edge_segment_matrix[i,j]+1
            if j-1<0:
                edge_segment_matrix[i,j]=edge_segment_matrix[i,j]+1
            else:
                m=mask[i,j-1]
                if m==0:
                    edge_segment_matrix[i,j]=edge_segment_matrix[i,j]+1
            if j+1>=column:
                edge_segment_matrix[i,j]=edge_segment_matrix[i,j]+1
            else:
                n=mask[i,j+1]
                if n==0:
                    edge_segment_matrix[i,j]=edge_segment_matrix[i,j]+1    
for i in range(0,row):
    for j in range(0,column):
        x=map1[i,j]
        background[x]=background[x]+edge_segment_matrix[i,j]

'''Clumpiness_processing-----------------------------------------------------'''
#Calculate components for calculating clumpines (gii, gik, min-ei, etc.)

clump=np.zeros(shape=(luc,8))
for i in range(0,luc):
    clump[i,1]=clump[i,1]+background[i]
    clump[i,2]=count_luc[i]
    clump[i,3]=(clump[i,2])**0.5
    clump[i,4]=int(clump[i,3])
    clump[i,5]=clump[i,2]-(clump[i,4])**2
    if clump[i,5]==0:
        clump[i,6]=4*clump[i,4]
    elif (clump[i,4])**2 <= clump[i,2] <= clump[i,4]*(1+clump[i,4]):
        clump[i,6]=4*clump[i,4]+2
    else:
        clump[i,6]=4*clump[i,4]+4
    for j in range(0,luc):
        if i==j:
            clump[i,0]=adjacency_table[i,j]
        clump[i,1]=clump[i,1]+adjacency_table[i,j]
for i in range(0,luc):
    clump[i,7]=clump[i,0]/(clump[i,1]-clump[i,6])

CLUMPY=[0]*luc
for i in range(0,luc):
    if clump[i,7]<prop[i] and prop[i]<0.5:
        CLUMPY[i]=(clump[i,7]-prop[i])/prop[i]
    else:
        CLUMPY[i]=(clump[i,7]-prop[i])/(1-prop[i])
        
print CLUMPY

'''Old_code------------------------------------------------------------------'''
#Adjacency table population
'''
for i in range(0,row):
    for j in range(0,column):
        if mask[i,j]>0:
            central=map1[i,j]
            counter[central]=counter[central]+1
            k=i-1
            if k<0:
                next
            elif mask[k,j]>0:
                link=map1[k,j]
                adjacency_table[central,link]=adjacency_table[central,link]+1
            l=i+1
            if l>=row:
                next
            elif mask[l,j]>0:
                link=map1[l,j]
                adjacency_table[central,link]=adjacency_table[central,link]+1
            m=j-1
            if m<0:
                next
            elif mask[i,m]>0:
                link=map1[i,m]
                adjacency_table[central,link]=adjacency_table[central,link]+1
            n=j+1
            if n>=column:
                next
            elif mask[i,n]>0:
                link=map1[i,n]
                adjacency_table[central,link]=adjacency_table[central,link]+1
'''
#Adjacency check code
'''
for p in range(0,luc):
    for i in range(0,row):
        for j in range(0,column):
            if map1[i,j]==p and mask[i,j]>0:
                k=i-1
                if k<0:
                    next
                elif mask[k,j]==0:
                    next
                else:
                    x=map1[k,j]
                    adjacency_count[p*luc+x,i,j]=adjacency_count[p*luc+x,i,j]+1
                k=i+1
                if k>=row:
                    next
                elif mask[k,j]==0:
                    next
                else:
                    x=map1[k,j]
                    adjacency_count[p*luc+x,i,j]=adjacency_count[p*luc+x,i,j]+1
                l=j-1
                if l<0:
                    next
                elif mask[i,l]==0:
                    next
                else:
                    x=map1[i,l]
                    adjacency_count[p*luc+x,i,j]=adjacency_count[p*luc+x,i,j]+1
                l=j+1
                if l>=column:
                    next
                elif mask[i,l]==0:
                    next
                else:
                    x=map1[i,l]
                    adjacency_count[p*luc+x,i,j]=adjacency_count[p*luc+x,i,j]+1

adjacency_table=np.zeros(shape=(luc,luc))
for p in range(0,luc):
    for q in range(0,luc):
        for i in range(0,row):
            for j in range(0,column):
                x=adjacency_count[p*luc+q,i,j]
                adjacency_table[p,q]=adjacency_table[p,q]+x

from write_3d_array import write_3d_array
path="C:\\Users\\Charles\\OneDrive\\Clumpiness\\Example_simple_Randstad\\adjacency_count.txt"
f=open(path)
write_3d_array(path,adjacency_count)
f.close()
'''
#Composition counter

'''
#Count the presence of land use classes in a landscape
count_luc=[0]*luc
for i in range(0,row):
    for j in range(0,column):
        if mask[i,j]>0:
            x=map1[i,j]
            count_luc[x]=count_luc[x]+1
'''