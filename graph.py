#!/usr/bin/python

import numpy as np
import matplotlib.pyplot as plt
import os

#####################################################################
#####################################################################
##################         GRAPHS            ########################
#####################################################################
#####################################################################


#-----------------------------------------------

dataFile = open("output","r")

n_insert    = []
n_search    = []

BST_ID_Insert_time = []
BST_NAME_Insert_time = []
OPENED_HASH_ID_Insert_time = []
OPENED_HASH_NAME_Insert_time = []
CLOSED_HASH_ID_Insert_time = []
CLOSED_HASH_NAME_Insert_time = []

BST_ID_Search_time = []
BST_NAME_Search_time = []
OPENED_HASH_ID_Search_time = []
OPENED_HASH_NAME_Search_time = []
CLOSED_HASH_ID_Search_time = []
CLOSED_HASH_NAME_Search_time = []

NAN_BST_ID_Search_time = []
NAN_BST_NAME_Search_time = []
NAN_OPENED_HASH_ID_Search_time = []
NAN_OPENED_HASH_NAME_Search_time = []
NAN_CLOSED_HASH_ID_Search_time = []
NAN_CLOSED_HASH_NAME_Search_time = []

ctr1 = 0
ctr2 = 0

for line in dataFile:
  
  pair = line.split(':')
  temp = pair[1]
  
  if (pair[0]=="BST ID Insert Time"):
    BST_ID_Insert_time.append(float(temp))
    ctr1 += 1
    n_insert.append(100*ctr1)
  elif (pair[0]=="BST NAME Insert Time"):
    BST_NAME_Insert_time.append(float(temp))
  elif (pair[0]=="BST ID Search Time"):
    BST_ID_Search_time.append(float(temp))
    ctr2 += 1
    n_search.append(1000*ctr2)
  elif (pair[0]=="BST NAME Search Time"):
    BST_NAME_Search_time.append(float(temp))
  elif (pair[0]=="OPENED_HASH ID Insert Time"):
    OPENED_HASH_ID_Insert_time.append(float(temp))
  elif (pair[0]=="OPENED_HASH NAME Insert Time"):
    OPENED_HASH_NAME_Insert_time.append(float(temp))
  elif (pair[0]=="OPENED_HASH ID Search Time"):
    OPENED_HASH_ID_Search_time.append(float(temp))
  elif (pair[0]=="OPENED_HASH NAME Search Time"):
    OPENED_HASH_NAME_Search_time.append(float(temp))
  elif (pair[0]=="CLOSED_HASH ID Insert Time"):
    CLOSED_HASH_ID_Insert_time.append(float(temp))
  elif (pair[0]=="CLOSED_HASH NAME Insert Time"):
    CLOSED_HASH_NAME_Insert_time.append(float(temp))
  elif (pair[0]=="CLOSED_HASH ID Search Time"):
    CLOSED_HASH_ID_Search_time.append(float(temp))
  elif (pair[0]=="CLOSED_HASH NAME Search Time"):
    CLOSED_HASH_NAME_Search_time.append(float(temp))
  elif (pair[0]=="~ BST ID Search Time"):
    NAN_BST_ID_Search_time.append(float(temp))
  elif (pair[0]=="~ BST NAME Search Time"):
    NAN_BST_NAME_Search_time.append(float(temp))
  elif (pair[0]=="~ OPENED_HASH ID Search Time"):
    NAN_OPENED_HASH_ID_Search_time.append(float(temp))
  elif (pair[0]=="~ OPENED_HASH NAME Search Time"):
    NAN_OPENED_HASH_NAME_Search_time.append(float(temp))
  elif (pair[0]=="~ CLOSED_HASH ID Search Time"):
    NAN_CLOSED_HASH_ID_Search_time.append(float(temp))
  elif (pair[0]=="~ CLOSED_HASH NAME Search Time"):
    NAN_CLOSED_HASH_NAME_Search_time.append(float(temp))

dataFile.close()

#-----------------------------------------------

# figura 1
fig1 = plt.figure(1)
plt.title("Tiempos de Insercion con ID")
plt.xlabel("N")
plt.ylabel("tiempo [s]")

plt.plot(n_insert,BST_ID_Insert_time,'-r', label='BST')
plt.plot(n_insert,OPENED_HASH_ID_Insert_time,'-g', label='Hash Abierto')
plt.plot(n_insert,CLOSED_HASH_ID_Insert_time,'-b', label='Hash Cerrado')

plt.legend()
#plt.show()
fig1.savefig("imgs/0001")

#-----------------------------------------------

# figura 2
fig2 = plt.figure(2)
plt.title("Tiempos de Insercion con Nombre")
plt.xlabel("N")
plt.ylabel("tiempo [s]")

plt.plot(n_insert,BST_NAME_Insert_time,'-r', label='BST')
plt.plot(n_insert,OPENED_HASH_NAME_Insert_time,'-g', label='Hash Abierto')
plt.plot(n_insert,CLOSED_HASH_NAME_Insert_time,'-b', label='Hash Cerrado')

plt.legend()
#plt.show()
fig2.savefig("imgs/0002")

#-----------------------------------------------

# figura 3
fig3 = plt.figure(3)
plt.title("Tiempos de Busqueda con ID")
plt.xlabel("N")
plt.ylabel("tiempo [s]")

plt.plot(n_search,BST_ID_Search_time,'-r', label='BST')
plt.plot(n_search,OPENED_HASH_ID_Search_time,'-g', label='Hash Abierto')
plt.plot(n_search,CLOSED_HASH_ID_Search_time,'-b', label='Hash Cerrado')

plt.legend()
#plt.show()
fig3.savefig("imgs/0003")

#-----------------------------------------------

# figura 4
fig4 = plt.figure(4)
plt.title("Tiempos de Busqueda con Nombre")
plt.xlabel("N")
plt.ylabel("tiempo [s]")

plt.plot(n_search,BST_NAME_Search_time,'-r', label='BST')
plt.plot(n_search,OPENED_HASH_NAME_Search_time,'-g', label='Hash Abierto')
plt.plot(n_search,CLOSED_HASH_NAME_Search_time,'-b', label='Hash Cerrado')

plt.legend()
#plt.show()
fig4.savefig("imgs/0004")

#-----------------------------------------------

# figura 5
fig5 = plt.figure(5)
plt.title("Tiempos de Busqueda de elementos no existentes con ID")
plt.xlabel("N")
plt.ylabel("tiempo [s]")

plt.plot(n_search,NAN_BST_ID_Search_time,'-r', label='BST')
plt.plot(n_search,NAN_OPENED_HASH_ID_Search_time,'-g', label='Hash Abierto')
plt.plot(n_search,NAN_CLOSED_HASH_ID_Search_time,'-b', label='Hash Cerrado')

plt.legend()
#plt.show()
fig5.savefig("imgs/0005")

#-----------------------------------------------

# figura 6
fig6 = plt.figure(6)
plt.title("Tiempos de Busqueda de elementos no existentes con Nombre")
plt.xlabel("N")
plt.ylabel("tiempo [s]")

plt.plot(n_search,NAN_BST_NAME_Search_time,'-r', label='BST')
plt.plot(n_search,NAN_OPENED_HASH_NAME_Search_time,'-g', label='Hash Abierto')
plt.plot(n_search,NAN_CLOSED_HASH_NAME_Search_time,'-b', label='Hash Cerrado')

plt.legend()
#plt.show()
fig6.savefig("imgs/0006")

#-----------------------------------------------

# figura 7
fig7 = plt.figure(7)
plt.title("Tiempos de insercion")
plt.xlabel("N")
plt.ylabel("tiempo [s]")

plt.plot(n_insert,BST_ID_Insert_time,'-r', label='BST con ID')
plt.plot(n_insert,OPENED_HASH_ID_Insert_time,'-g', label='Hash Abierto con ID')
plt.plot(n_insert,CLOSED_HASH_ID_Insert_time,'-b', label='Hash Cerrado con ID')
plt.plot(n_insert,BST_NAME_Insert_time,'-y', label='BST con Nombre')
plt.plot(n_insert,OPENED_HASH_NAME_Insert_time,'-c', label='Hash Abierto con Nombre')
plt.plot(n_insert,CLOSED_HASH_NAME_Insert_time,'-m', label='Hash Cerrado con Nombre')

plt.legend()
#plt.show()
fig7.savefig("imgs/0007")

#-----------------------------------------------

# figura 8
fig8 = plt.figure(8)
plt.title("Tiempos de Busqueda")
plt.xlabel("N")
plt.ylabel("tiempo [s]")

plt.plot(n_search,BST_ID_Search_time,'-r', label='BST con ID')
plt.plot(n_search,OPENED_HASH_ID_Search_time,'-g', label='Hash Abierto con ID')
plt.plot(n_search,CLOSED_HASH_ID_Search_time,'-b', label='Hash Cerrado con ID')
plt.plot(n_search,BST_NAME_Search_time,'-y', label='BST con Nombre')
plt.plot(n_search,OPENED_HASH_NAME_Search_time,'-c', label='Hash Abierto con Nombre')
plt.plot(n_search,CLOSED_HASH_NAME_Search_time,'-m', label='Hash Cerrado con Nombre')

plt.legend()
#plt.show()
fig8.savefig("imgs/0008")

#-----------------------------------------------

# figura 9
fig9 = plt.figure(9)
plt.title("Tiempos de Busqueda de elementos no existentes")
plt.xlabel("N")
plt.ylabel("tiempo [s]")

plt.plot(n_search,NAN_BST_ID_Search_time,'-r', label='BST con ID')
plt.plot(n_search,NAN_OPENED_HASH_ID_Search_time,'-g', label='Hash Abierto con ID')
plt.plot(n_search,NAN_CLOSED_HASH_ID_Search_time,'-b', label='Hash Cerrado con ID')
plt.plot(n_search,NAN_BST_NAME_Search_time,'-y', label='BST con Nombre')
plt.plot(n_search,NAN_OPENED_HASH_NAME_Search_time,'-c', label='Hash Abierto con Nombre')
plt.plot(n_search,NAN_CLOSED_HASH_NAME_Search_time,'-m', label='Hash Cerrado con Nombre')

plt.legend()
#plt.show()
fig9.savefig("imgs/0009")

#-----------------------------------------------

# figura 10
fig10 = plt.figure(10)
plt.title("Tiempos de Busqueda BST")
plt.xlabel("N")
plt.ylabel("tiempo [s]")

plt.plot(n_search,BST_ID_Search_time,'-r', label='BST con ID')
plt.plot(n_search,BST_NAME_Search_time,'-g', label='BST con Nombre')
plt.plot(n_search,NAN_BST_ID_Search_time,'-b', label='BST con ID no existente')
plt.plot(n_search,NAN_BST_NAME_Search_time,'-c', label='BST con Nombre no existente')


plt.legend()
#plt.show()
fig10.savefig("imgs/0010")

#-----------------------------------------------

# figura 11
fig11 = plt.figure(11)
plt.title("Tiempos de Busqueda Hash Abierto")
plt.xlabel("N")
plt.ylabel("tiempo [s]")

plt.plot(n_search,OPENED_HASH_ID_Search_time,'-r', label='Hash Abierto con ID')
plt.plot(n_search,OPENED_HASH_NAME_Search_time,'-g', label='Hash Abierto con Nombre')
plt.plot(n_search,NAN_OPENED_HASH_ID_Search_time,'-b', label='Hash Abierto con ID no existente')
plt.plot(n_search,NAN_OPENED_HASH_NAME_Search_time,'-c', label='Hash Abierto con Nombre no existente')


plt.legend()
#plt.show()
fig11.savefig("imgs/0011")

#-----------------------------------------------

# figura 12
fig12 = plt.figure(12)
plt.title("Tiempos de Busqueda Hash Cerrado")
plt.xlabel("N")
plt.ylabel("tiempo [s]")

plt.plot(n_search,CLOSED_HASH_ID_Search_time,'-r', label='Hash Cerrado con ID')
plt.plot(n_search,CLOSED_HASH_NAME_Search_time,'-g', label='Hash Cerrado con Nombre')
plt.plot(n_search,NAN_CLOSED_HASH_ID_Search_time,'-b', label='Hash Cerrado con ID no existente')
plt.plot(n_search,NAN_CLOSED_HASH_NAME_Search_time,'-c', label='Hash Cerrado con Nombre no existente')


plt.legend()
#plt.show()
fig12.savefig("imgs/0012")

#-----------------------------------------------





