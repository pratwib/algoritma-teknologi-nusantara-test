from flask import Flask, request
import mysql.connector

app = Flask(__name__)

@app.route('/data', methods=['POST'])
def receive_data():
  data = request.get_json()

  temperature = data['temperature']
  humidity = data['humidity']

  db = mysql.connector.connect(
    host="localhost",
    user="MYSQL_USERNAME",
    password="MYSQL_PASSWORD",
    database="MYSQL_DATABASE_NAME"
  )

  cursor = db.cursor()

  sql = "INSERT INTO sensor_data (temperature, humidity) VALUES (%s, %s)"
  cursor.execute(sql, (temperature, humidity))
  db.commit()

  cursor.close()
  db.close()

  return "Data received successfully!"

if __name__ == '__main__':
  app.run(host='0.0.0.0', port=8080)
