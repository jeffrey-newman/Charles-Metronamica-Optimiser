'''                         Clumpiness module                         '''  
#Calculate the clumpiness for a given input map
#Modules
import numpy as np

#Function
def clumpiness_index(map1,mask):
    '''Input_data_processing-------------------------------------------------'''
    mapshape=np.shape(map1)
    row=mapshape[0]
    column=mapshape[1]
    luc=np.amax(map1)+1
    '''Populate_adjacency_matrix---------------------------------------------'''
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
    '''Calculate_composition_and_proportion----------------------------------'''
    #Calculate the proportion of different land use classes in a landscape
    prop=[0]*luc
    for i in range(0,luc):
        prop[i]=prop[i]+float(count_luc[i])/sum(count_luc)
    '''Calculate_background--------------------------------------------------'''
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
    '''Clumpiness_processing-------------------------------------------------'''
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
            
    '''Return_result---------------------------------------------------------'''
    return CLUMPY