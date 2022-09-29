from flask import Flask, render_template
import requests
import json

app = Flask(__name__)

@app.route("/")
def home():
    return render_template("index.html")

@app.route("/Lamp1")
def lamp1():
    return  {
        "lamp1": 0,
    }

if __name__ == '__main__':
    app.run(debug=True, port=8000, host="0.0.0.0")

