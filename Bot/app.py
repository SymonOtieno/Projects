from flask import Flask
from flask.templating import render_template
import urllib.request, json
import os

app = Flask(__name__)

@app.route("/hello")
def hello_world():
    return "<p>Hello, World!</p>"

@app.route("/")
def get_movies():
    url = "https://api.themoviedb.org/3/movie/550?api_key=86bb9316d39a85498840695528fa112c".format(os.environ.get("TMDB_API_KEY"))

    response = urllib.request.urlopen(url)
    movies = json.loads(response.read())

    return render_template ("movies.html", data=movies)


if __name__ == '__main__':
    app.run(debug=True)