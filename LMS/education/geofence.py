from flask import Flask, flash,session, redirect, request, url_for
from flask.templating import render_template
from flask_mysqldb import MySQL
from markupsafe import escape
from MySQLdb.cursors import Cursor
from werkzeug.utils import secure_filename
from flask_socketio import SocketIO, emit, join_room, leave_room
from flask_session import Session
from flask_googlemaps import GoogleMaps
from flask_googlemaps import Map


app = Flask(__name__)
app.secret_key = "secret key"
app.config['MYSQL_HOST'] = 'localhost'
app.config['MYSQL_USER'] = 'symon'
app.config['MYSQL_PASSWORD'] = 'root'
app.config['MYSQL_DB'] = 'user_details' 
mysql = MySQL(app)
app.config['SECRET_KEY'] = 'vnkdjnfjknfl1232#'

Session(app)
socketio = SocketIO(app, manage_session=False)

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

@app.route("/home")
def home():
    return render_template("index.html")

@app.route("/about")
def about():
    return render_template("about.html")

@app.route("/course")
def course():
    return render_template("course.html")

@app.route("/detail")
def detail():
    return render_template("detail.html")

@app.route("/feature")
def feature():
    return render_template("feature.html")

@app.route("/team")
def team():
    return render_template("team.html")

@app.route("/testimonial")
def testimonial():
    return render_template("testimonial.html")

@app.route("/contact")
def contact():
    return render_template("contact.html")

@app.route('/startsession', methods=['GET', 'POST'])
def startsession():
    return render_template('session.html')

@app.route('/chat', methods=['GET', 'POST'])
def chat():
    if(request.method=='POST'):
        username = request.form['username']
        room = request.form['room']
        #Store the data in session
        session['username'] = username
        session['room'] = room
        return render_template('chat.html', session = session)
    else:
        if(session.__get__('username') is not None):
            return render_template('chat.html', session = session)
        else:
            return redirect(url_for('index'))

@socketio.on('join', namespace='/chat')
def join(message):
    room = session.get('room')
    join_room(room)
    emit('status', {'msg':  session.get('username') + ' has entered the room.'}, room=room)


@socketio.on('text', namespace='/chat')
def text(message):
    room = session.get('room')
    emit('message', {'msg': session.get('username') + ' : ' + message['msg']}, room=room)


@socketio.on('left', namespace='/chat')
def left(message):
    room = session.get('room')
    username = session.get('username')
    leave_room(room)
    session.clear()
    emit('status', {'msg': username + ' has left the room.'}, room=room)

@app.route('/map', methods=["GET"])
def my_map():
    mymap = Map(

                identifier="view-side",

                varname="mymap",

                style="height:720px;width:1100px;margin:0;", # hardcoded!

                lat=37.4419, # hardcoded!

                lng=-122.1419, # hardcoded!

                zoom=15,

                markers=[(37.4419, -122.1419)] # hardcoded!

            )

    return render_template('map.html', mymap=mymap)
if __name__ == "__main__":
    app.run(debug=True)
    
