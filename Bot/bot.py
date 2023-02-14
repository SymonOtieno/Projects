from MySQLdb.cursors import Cursor
from flask import Flask,redirect,url_for, request,url_for,flash
from flaskext.mysql import MySQL
from flask_mysqldb import MySQL
from flask.templating import render_template
from logging import exception
from time import sleep

app = Flask(__name__)
app.secret_key = "secret key"
app.config['MYSQL_HOST'] = 'localhost'
app.config['MYSQL_USER'] = 'symon'
app.config['MYSQL_PASSWORD'] = 'root'
app.config['MYSQL_DB'] = 'user_details' 
mysql = MySQL(app)
@app.route("/")
def index():
    return render_template("login.html")
@app.route("/", methods=['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        username = request.form['username']
        passwd = request.form['passwd']
        cursor = mysql.connection.cursor()
        cursor.execute("SELECT * FROM Accounts WHERE username='" + username + "' and passwd='" + passwd + "'")
        data = cursor.fetchone()
        if data is None:
            return "Username or Password wrong"
        else:
            return render_template("index.html")

@app.route("/login")
def view():
    return render_template("login.html")

@app.route('/register/', methods=['GET', 'POST'])
def register():
    adduser()
    return render_template('forms.html')

@app.route("/vehicles")
def vehicles():
    return render_template("notdash.html")

@app.route('/adduser/', methods=['GET', 'POST'])
def adduser():
    print("Entered")

    try:
        fname = request.form['firstname']
        age = request.form['age']
        return fname,age
        cursor = mysql.connection.cursor()
        cursor.execute("INSERT INTO 'login'('fname','age') VALUES (%s,%s)")
        Cursor.commit()       
        return "Registered"
    except Exception as e:
       return(str(e))
@app.route('/display/<filename>')
def display_image(filename):
    return redirect(url_for('static', filename='static/' + filename), code=301)

@app.route("/Items1", methods=['GET', 'POST'])
def show():
    error = None
    if request.method == 'POST':
        descr = request.form['descr']
        item_name = request.form['item_name']
        cursor = mysql.connection.cursor()
        cursor.execute("SELECT * FROM Accounts")
        data = cursor.fetchall()
        return render_template("products.html")

if __name__ == "__main__":
    app.run(debug=True)
    
