# -*- coding: utf-8 -*-
from __future__ import print_function
import RPi.GPIO as GPIO
import time
import sys
import thread
import serial
import binascii
import MySQLdb

teplota = []
vlhkost = []
pirsens = []
svetlo = []
svetlopwm = []
kureni = []
kurenitep = []

rain = 0xff
dayl = 0xff

ligh = [0,0,0,0,0,0,0,0]
lpwm = [0,0,0,0,0,0,0,0]
heat = [0,0,0,0,0,0,0,0]
htmp = [0,0,0,0,0,0,0,0]

constRS232Baud = 19200
constRS232Timeout = 2

constPIC_Input_Cnt = 20
constPIC_Output_Cnt = 5
PIC_Input_On = False
PIC_Output_On = False

def Refresh():
 global PIC_Input_On
 global PIC_Output_On
 PIC_Input_Cnt=constPIC_Input_Cnt
 PIC_Output_Cnt=constPIC_Output_Cnt
 while 1:
  time.sleep(1)
  PIC_Input_Cnt=PIC_Input_Cnt-1
  PIC_Output_Cnt=PIC_Output_Cnt-1;
  if PIC_Output_Cnt == 0:
   PIC_Output_Cnt=constPIC_Output_Cnt
   while (PIC_Input_On == True):
    pass
   PIC_Output_On = True;
  if PIC_Input_Cnt == 0:
   PIC_Input_Cnt=constPIC_Input_Cnt
   while (PIC_Output_On == True):
    pass
   PIC_Input_On = True
 
### PIC_Output ###  
def PIC_Output():
 global PIC_Input_On
 global PIC_Output_On
 while 1:
  while PIC_Output_On == False:
   pass
  db=MySQLdb.connect(host="localhost", user="root", passwd="raspberry", db="IBH")
  cursor=db.cursor()
  cursors=db.cursor()
  cursor.execute("SELECT `room_index`,`light_on`,`light_pwm`,`heat_on`,`heat_temp` FROM `ovladanie` ORDER BY room_index")
  
  cursors.execute("SELECT `temp0`,`temp1`,`temp2`,`temp3`,`temp4`,`temp5`,`temp6`,`temp7` FROM `statistiky` ORDER BY timestamp DESC LIMIT 1")
  row=cursors.fetchone()
  
  kurit=0
  svietit=0
  for col in cursor:
   svetlo[col[0]]=col[1]
   svetlopwm[col[0]]=col[2]
   kureni[col[0]]=col[3]
   kurenitep[col[0]]=col[4]

   if (col[3]==1) and (col[4]>row[col[0]]):
    kurit=kurit|(1<<(col[0]))
    #print("Kurenie [",col[0],"] zapinam, nastavena teplota [",col[4],"], teplota v izbe [",row[col[0]],"], stav vypinaca [",(col[3] and 1),"]")
  # else: 
    #print("Kurenie [",col[0],"] vypinam, nastavena teplota [",col[4],"], teplota v izbe [",row[col[0]],"], stav vypinaca [",(col[3] and 1),"]")
   svietit=svietit|((col[1]and 1)<<(col[0]))
   rs232.write("L")
   rs232.write(chr(col[0]))
   if svetlo[col[0]] == 0:
    rs232.write(chr(0))
   else:
    rs232.write(chr(col[2]))
  db.close()
  kurit=~kurit&255
 # print(kurit, bin(int(hex(kurit), base=16)).lstrip('0b'))
  rs232.write("H")
  rs232.write(chr(kurit))
  time.sleep(0.5)
  PIC_Output_On = False
### PIC_Output ###  

### PIC_Input ###  
def PIC_Input():
 global PIC_Input_On
 global PIC_Output_On
 while 1:
  while PIC_Input_On == False:
   pass
  del teplota[:]
  del vlhkost[:]
  del pirsens[:]
  isok=0
  while (isok<5):
   rs232.write("d") # kod pre citanie DHT je 'd'
   dht = rs232.read(32)
   if (dht.__len__() < 32):
    print("'DHT data' nemozno citat",time.asctime())
    isok = isok + 1;
    time.sleep(0.1)
   else:
    isok = 99   
  
  if (dht.__len__() < 32):
   for i in range (0,32):
    dht=dht+chr(0xff)
  ddht=map(ord,dht)

  rs232.write("p") # kod pre citanie PIR je 'p'
  pir = rs232.read(1)
  if (pir.__len__() < 1):
   print("'PIR data' nemozno citat")
   pir=chr(0xff)
  dpir=map(ord,pir)

  rs232.write("i") # kod pre citanie senzora zotmenia je 'i', ak sa zotmelo pod nastavenu hodnotu, hodnota 1, inac 0
  daylread = ord(rs232.read(1))
  if daylread>1:
   dayl=0
  else:
   dayl=daylread

  rs232.write("r") # kod pre citanie rain senzora je 'r', ak prsi alebo vlhko nad nastavenu uroven, hodnota 1, inac 0
  rainread=ord(rs232.read(1))
  if rainread>1:
   rain=0
  else:
   rain=rainread

  for i in range(0,8):
   pirsens.append((dpir[0]>>i)&1)
   if i==2:
    if ddht[i*4]<0xf0:
     teplota.append(((ddht[i*4+1]<<8)+ddht[i*4+0])/10.)
    else:
     teplota.append(ddht[i*4])
    if ddht[i*4+2]<0xf0:
     vlhkost.append(((ddht[i*4+3]<<8)+ddht[i*4+2])/10.)
    else:
     vlhkost.append(ddht[i*4+2])
   else:
    teplota.append(((ddht[i*4+1]<<8)+ddht[i*4+0])>>8)
    vlhkost.append(((ddht[i*4+3]<<8)+ddht[i*4+2])>>8)

  db=MySQLdb.connect(host="localhost", user="root", passwd="raspberry", db="IBH")
  cursor=db.cursor()
  cursor.execute("INSERT INTO statistiky (`temp0`,`temp1`,`temp2`,`temp3`,`temp4`,`temp5`,`temp6`,`temp7`,`humi0`,`humi1`,`humi2`,`humi3`,`humi4`,`humi5`,`humi6`,`humi7`,`pirs0`,`pirs1`,`pirs2`,`pirs3`,`pirs4`,`pirs5`,`pirs6`,`pirs7`,`rain0`,`dayl0`,`ligh0`,`ligh1`,`ligh2`,`ligh3`,`ligh4`,`ligh5`,`ligh6`,`ligh7`,`lpwm0`,`lpwm1`,`lpwm2`,`lpwm3`,`lpwm4`,`lpwm5`,`lpwm6`,`lpwm7`,`heat0`,`heat1`,`heat2`,`heat3`,`heat4`,`heat5`,`heat6`,`heat7`,`htmp0`,`htmp1`,`htmp2`,`htmp3`,`htmp4`,`htmp5`,`htmp6`,`htmp7`) VALUES ('"+str(teplota[0])+"','"+str(teplota[1])+"','"+str(teplota[2])+"','"+str(teplota[3])+"','"+str(teplota[4])+"','"+str(teplota[5])+"','"+str(teplota[6])+"','"+str(teplota[7])+"','"+str(vlhkost[0])+"','"+str(vlhkost[1])+"','"+str(vlhkost[2])+"','"+str(vlhkost[3])+"','"+str(vlhkost[4])+"','"+str(vlhkost[5])+"','"+str(vlhkost[6])+"','"+str(vlhkost[7])+"','"+str(pirsens[0])+"','"+str(pirsens[1])+"','"+str(pirsens[2])+"','"+str(pirsens[3])+"','"+str(pirsens[4])+"','"+str(pirsens[5])+"','"+str(pirsens[6])+"','"+str(pirsens[7])+"','"+str(rain)+"','"+str(dayl)+"','"+str(ligh[0])+"','"+str(ligh[1])+"','"+str(ligh[2])+"','"+str(ligh[3])+"','"+str(ligh[4])+"','"+str(ligh[5])+"','"+str(ligh[6])+"','"+str(ligh[7])+"','"+str(lpwm[0])+"','"+str(lpwm[1])+"','"+str(lpwm[2])+"','"+str(lpwm[3])+"','"+str(lpwm[4])+"','"+str(lpwm[5])+"','"+str(lpwm[6])+"','"+str(lpwm[7])+"','"+str(heat[0])+"','"+str(heat[1])+"','"+str(heat[2])+"','"+str(heat[3])+"','"+str(heat[4])+"','"+str(heat[5])+"','"+str(heat[6])+"','"+str(heat[7])+"','"+str(htmp[0])+"','"+str(htmp[1])+"','"+str(htmp[2])+"','"+str(htmp[3])+"','"+str(htmp[4])+"','"+str(htmp[5])+"','"+str(htmp[6])+"','"+str(htmp[7])+"')")

  db.commit()
  db.close()
  time.sleep(0.5)
  PIC_Input_On = False
### PIC_Input ###  

### Hlavny program ###
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

for i in range (0,8):
 teplota.append(0xff)
 vlhkost.append(0xff)
 pirsens.append(0xff)
 svetlo.append(0)
 svetlopwm.append(0)
 kureni.append(0)
 kurenitep.append(0)

rs232=serial.Serial(port="/dev/ttyS0", baudrate=constRS232Baud, timeout=constRS232Timeout)
rs232.flushInput()
rs232.flushOutput()

thread.start_new_thread(Refresh, ())
thread.start_new_thread(PIC_Input, ())
thread.start_new_thread(PIC_Output, ())

# hlavny loop programu
while 1:
 pass

### Hlavny program ###
