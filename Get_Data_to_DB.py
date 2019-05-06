import pymysql
import json
from datetime import datetime
#json_Dict
def Sensor(jsonData):
  x = json.loads(jsonData.decode('utf-8')) # load du lieu tu blocker
  Temperature = x['Temperature']
  Humidity = x['Humidity']
  Date_and_Time = (datetime.today()).strftime("%d-%b-%Y %H:%M:%S")
  # MO ket noi den Database
  db = pymysql.connect("localhost","mangcambien-user","123456","mydb")
  cursor = db.cursor()
  sql = """INSERT INTO Sensor(Temperature,Humidity,Date_and_Time) VALUES (%s,%s,%s)"""
  val = (Temperature,Humidity,Date_and_Time)
  cursor.execute(sql,val)
  db.commit()
  print ("Insert complete values topic to database")
  print (".....................................")
  db.close()
