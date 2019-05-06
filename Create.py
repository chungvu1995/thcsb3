import pymysql
db = pymysql.connect("localhost","mangcambien-user","123456","mydb")
cursor = db.cursor()
cursor.execute("DROP TABLE IF EXISTS Sensor")
sql = """CREATE TABLE Sensor(
		ID INT(10) PRIMARY KEY AUTO_INCREMENT,
		Temperature INT(10) NOT NULL,
		Humidity INT(10) NOT NULL,
		Date_and_Time CHAR(30) NOT NULL

	)"""
cursor.execute(sql)

db.close()


