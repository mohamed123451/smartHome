from flask import Flask, render_template, redirect, url_for


lamp_lastState = 33

app = Flask(__name__)

@app.route("/")
def home():
    global lamp_lastState
    if lamp_lastState == 33:
        return render_template("index.html", state="OFF")
    elif lamp_lastState == 88:
        return render_template("index.html", state="ON")

@app.route('/Lamp1/<int:lamp_curState>')
def lamp1(lamp_curState):
    global lamp_lastState
    if lamp_lastState != lamp_curState:
        lamp_lastState = lamp_curState
        """return have to be json"""
        return {1: "Ok will update the site"}
    else:
        return {2: "no changes"}

@app.route('/updateNode')
def update_node():
    return {1: lamp_lastState}

@app.route('/on')
def on():
    global lamp_lastState
    lamp_lastState = 88
    return redirect(url_for('home'))


@app.route('/off')
def off():
    global lamp_lastState
    lamp_lastState = 33
    return redirect(url_for('home'))



if __name__ == '__main__':
    app.run(debug=True, port=8000, host="0.0.0.0")

