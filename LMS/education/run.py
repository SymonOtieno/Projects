from flask import Flask, render_template

from flask_googlemaps import GoogleMaps

from flask_googlemaps import Map


app = Flask(__name__)


GoogleMaps(app, key="my-key")




@app.route('/', methods=["GET"])
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

    return render_template('locate.html', mymap=mymap)
import os
duration = 1  # seconds
freq = 440  # Hz
os.system('play -nq -t alsa synth {} sine {}'.format(duration, freq))





if __name__ == "__main__":

    app.run(debug=True, use_reloader=True)